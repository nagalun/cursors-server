#include <fstream>

#include "server.hpp"
#include "map.hpp"

/* Compile with:
 * g++ -std=gnu++0x -DASIO_STANDALONE server.cpp map.cpp -I./websocketpp/ -I./asio/asio/include/ -lrt -lpthread -O2
 ***/

/* TODO:
 * Classify walls per color instead of id so i don't have to loop through all of them and compare the color?
 * More error checking
 * Clean my code
 * Make area triggers work
 * Check for wallhack
 * Add more comments
 ***/

long int js_date_now(){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return ms;
}

void cursorsio::server::start(uint16_t port, const std::string & mapdata){
	cursorsio::map::parse(this, mapdata, maps);
	uint32_t i = 0;
	for(auto& map : maps){
		std::cout << "Starting thread for map id: " << i << std::endl;
		websocketpp::lib::thread thr([this, i, &map]{cursorsio::server::process_updates(&s, &map, i);});
		thr.detach();
		i++;
	}
	websocketpp::lib::thread thr([&](){cursorsio::server::button_thread();});
	thr.detach();
	s.clear_access_channels(websocketpp::log::alevel::all);
	s.set_access_channels(websocketpp::log::alevel::connect);
	s.set_access_channels(websocketpp::log::alevel::disconnect);
	s.set_access_channels(websocketpp::log::alevel::app);
	
	s.listen(asio::ip::tcp::v4(), port);
	s.start_accept();
	s.run();
}

void cursorsio::server::on_open(wsserver* s, websocketpp::connection_hdl hdl) {
	std::vector<uint8_t> bytes = {STYPE_SET_CLIENT_ID};
	uint32_t newid = cursorsio::server::get_id();
	addtoarr(newid, bytes);
	conn_mmtx.lock();
	clients[hdl] = { newid, maps[defaultmap].startpoint[0], maps[defaultmap].startpoint[1], defaultmap, false, false };
	conn_mmtx.unlock();
	s->send(hdl, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
}

void cursorsio::server::on_fail(wsserver* s, websocketpp::connection_hdl hdl) {
	try {
		clients.at(hdl);
		s->get_alog().write(websocketpp::log::alevel::app,
			"Connection fail in client id: " + std::to_string(clients[hdl].id));
		conn_mmtx.lock();
		cursorsio::server::free_id(clients[hdl].id);
		clients.erase(hdl);
		s->close(hdl, 0, "");
		conn_mmtx.unlock();
		playerCountChanged = maps.size();
	} catch(const std::out_of_range) { }
}

void cursorsio::server::on_close(wsserver* s, websocketpp::connection_hdl hdl) {
	conn_mmtx.lock();
	cursorsio::server::free_id(clients[hdl].id);
	clients.erase(hdl);
	conn_mmtx.unlock();
	playerCountChanged = maps.size();
}

void cursorsio::server::on_message(wsserver* s, websocketpp::connection_hdl hdl, wsserver::message_ptr msg) {
	if (msg->get_opcode() == websocketpp::frame::opcode::binary && msg->get_payload().length() == 9) {
		try {
			clients.at(hdl);
			maps.at(clients[hdl].mapid);
		} catch(const std::out_of_range) {
			return;
		}
		const unsigned char *bytes = reinterpret_cast<const unsigned char *>(msg->get_payload().c_str());
		unsigned int o = 1;
		uint16_t u16;
		uint32_t u32;
		switch((uint8_t)msg->get_payload()[0]){
			case CTYPE_MOVE: {
				if(!clients[hdl].started){
					// Sending the map data while the client is still in the "Click to begin" screen is a bad idea
					cursorsio::server::nextmap(defaultmap, hdl);
					clients[hdl].started = true;
					playerCountChanged = maps.size();
					return;
				}
				if(clients[hdl].correct){
					teleport_client(s, hdl, clients[hdl].x, clients[hdl].y, clients[hdl].mapid);
					clients[hdl].correct = false;
				} else {
					uint16_t x = bitsToInt<uint16_t>(u16, bytes, o);
					uint16_t y = bitsToInt<uint16_t>(u16, bytes, o);
					if(cursorsio::server::checkpos(x, y, clients[hdl].mapid, hdl, false))
						return;
					clients[hdl].x = x;
					clients[hdl].y = y;
				}
				maps[clients[hdl].mapid].updated = true;
				//uint32_t G = bitsToInt<uint32_t>(u32, bytes, o);
				break;
			}
			case CTYPE_CLICK: {
				uint16_t x = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t y = bitsToInt<uint16_t>(u16, bytes, o);
				// clients[hdl].x != x && clients[hdl].y != y  <- Is this a good idea?
				if(cursorsio::server::checkpos(x, y, clients[hdl].mapid, hdl, true))
					return;
				maps[clients[hdl].mapid].click_q.push_back({x, y});
				//uint32_t G = bitsToInt<uint32_t>(u32, bytes, o);
				break;
			}
			case CTYPE_DRAW: {
				uint16_t x = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t y = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t x2 = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t y2 = bitsToInt<uint16_t>(u16, bytes, o);
				/*if(clients[hdl].x != x && clients[hdl].y != y*/
				maps[clients[hdl].mapid].draw_q.push_back({x, y, x2, y2});
				break;
			}
			default:
				s->get_alog().write(websocketpp::log::alevel::app,
					"Unknown msg received, closing connection for client id: " + std::to_string(clients[hdl].id));
				conn_mmtx.lock();
				cursorsio::server::free_id(clients[hdl].id);
				clients.erase(hdl);
				playerCountChanged = maps.size();
				s->close(hdl, 0, "");
				conn_mmtx.unlock();
				break;
		}
	} else {
		s->get_alog().write(websocketpp::log::alevel::app,
			"Unknown msg received, closing connection for client id: " + std::to_string(clients[hdl].id));
		conn_mmtx.lock();
		cursorsio::server::free_id(clients[hdl].id);
		clients.erase(hdl);
		playerCountChanged = maps.size();
		s->close(hdl, 0, "");
		conn_mmtx.unlock();
	}
}

void cursorsio::server::process_updates(wsserver* s, mapprop_t *map, uint32_t mapid){
	while(1){
		std::vector<uint8_t> bytes = {STYPE_MAP_UPDATE};
		int h;
		uint16_t max_messages = 300;

		conn_mmtx.lock();
		uint16_t inThisMap = 0;
		std::vector<uint8_t> clickpos;
		std::vector<websocketpp::connection_hdl> clhdl;
		for(auto& client : clients){
			if(client.second.mapid == mapid && inThisMap < 100 && client.second.started){
				addtoarr(client.second.id, clickpos);
				addtoarr(client.second.x, clickpos);
				addtoarr(client.second.y, clickpos);
				clhdl.push_back({client.first});
				inThisMap++;
			}
		}
		conn_mmtx.unlock();
		addtoarr(inThisMap, bytes);
		bytes.insert(bytes.end(), &clickpos[0], &clickpos[clickpos.size()]);
		
		//map->click_q.mtx.lock();
		uint16_t clickTimes = map->click_q.size() & 0xFFFF;
		addtoarr((clickTimes < max_messages) ? clickTimes : max_messages, bytes);
		for(auto& click : map->click_q){
			if(h < max_messages){ // TODO: fix this
				addtoarr(click.x, bytes);
				addtoarr(click.y, bytes);
				h++;
			}
		}
		map->click_q.clear();
		//map->click_q.mtx.unlock();

		h = 0;
		uint16_t wallsRemoved = map->removed_q.size() & 0xFFFF;
		addtoarr(wallsRemoved, bytes);
		for(auto& id : map->removed_q){
			addtoarr(id, bytes);
		}
		map->removed_q.clear();

		uint16_t objectsUpdated = map->objupd_q.size() & 0xFFFF;
		addtoarr(objectsUpdated, bytes);
		for(auto& object : map->objupd_q){
			bytes.insert(bytes.end(), &object[0], &object[object.size()]);
		}
		map->objupd_q.clear();

		//map->draw_q.mtx.lock();
		uint16_t linesDrawed = map->draw_q.size() & 0xFFFF;
		addtoarr((linesDrawed < max_messages) ? linesDrawed : max_messages, bytes);
		for(auto& line : map->draw_q){
			if(h < max_messages){
				addtoarr(line.x, bytes);
				addtoarr(line.y, bytes);
				addtoarr(line.x2, bytes);
				addtoarr(line.y2, bytes);
				h++;
			}
		}
		map->draw_q.clear();
		//map->draw_q.mtx.unlock();

		conn_mmtx.lock();
		
		if(playerCountChanged == mapid+1){ // very ugly way of doing this
			uint32_t playerCount32 = clients.size();
			addtoarr(playerCount32, bytes); // Player count is uint32_t
		}

		if(linesDrawed > 0 || objectsUpdated > 0 || wallsRemoved > 0 || clickTimes > 0 || playerCountChanged == mapid+1 || map->updated){
			for(auto& client : clhdl){
				s->send(client, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
			}
		}
		if(playerCountChanged == mapid+1)
			playerCountChanged--;
		if(map->updated)
			map->updated = false;
		conn_mmtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // there might be a better method than polling
	}
}

void cursorsio::server::teleport_client(wsserver* s, websocketpp::connection_hdl hdl, uint16_t x, uint16_t y, uint32_t G){
	std::vector<uint8_t> bytes = {STYPE_TELEPORT_CLIENT};
	addtoarr(x, bytes);
	addtoarr(y, bytes);
	addtoarr(G, bytes);
	s->send(hdl, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
}

void cursorsio::server::nextmap(uint32_t mapid, websocketpp::connection_hdl hdl){
	try {
		maps.at(mapid);
		clients.at(hdl);
	} catch(const std::out_of_range) { return; }
	clients[hdl].mapid = mapid;
	clients[hdl].x = maps[mapid].startpoint[0];
	clients[hdl].y = maps[mapid].startpoint[1];
	maps[mapid].updated = true;
	s.send(hdl, &maps[mapid].bytes[0], maps[mapid].bytes.size(), websocketpp::frame::opcode::binary);
}

bool cursorsio::server::checkpos(uint16_t x, uint16_t y, uint32_t mapid, websocketpp::connection_hdl hdl, bool click){
	try {
		maps.at(mapid);
		clients.at(hdl);
	} catch(const std::out_of_range) { return true; }
	if(!click){
		for(auto& exit : maps[mapid].exits){
			if(x >= exit.second.x && x <= exit.second.x + exit.second.w
				&& y >= exit.second.y && y <= exit.second.y + exit.second.h){
				if(exit.second.isbad){
					clients[hdl].x = maps[mapid].startpoint[0];
					clients[hdl].y = maps[mapid].startpoint[1];
					teleport_client(&s, hdl, maps[mapid].startpoint[0], maps[mapid].startpoint[1], mapid);
				} else {
					cursorsio::server::nextmap(mapid+1, hdl);
				}
				return true;
			}
		}
		for(auto& area : maps[mapid].areas){
			if(x >= area.second.x && x <= area.second.x + area.second.w
				&& y >= area.second.y && y <= area.second.y + area.second.h){
				if(area.second.count > 0){
					area.second.count--;
				} else {
					
				}
				return true;
			}
		}
	} else {
		for(auto& button : maps[mapid].buttons){
			if(x >= button.second.first.x && x <= button.second.first.x + button.second.first.w
				&& y >= button.second.first.y && y <= button.second.first.y + button.second.first.h){
				if(button.second.first.count > 0){
					button.second.first.count--;
					maps[mapid].objupd_q.push_back({
						cursorsio::map::create_button(button.second.first.x, button.second.first.y,
									      button.second.first.w, button.second.first.h,
									button.second.first.count, button.second.first.color,
									button.first, true)
					});
					if(button.second.first.count == 0) {
						for(auto& wall : maps[mapid].walls){
							if(wall.second.color == button.second.first.color && !wall.second.removed){
								maps[mapid].removed_q.push_back({wall.first});
								wall.second.removed = true;
							}
						}
					}
				}
				button.second.second = js_date_now();
				return false;
			}
		}
	}
	return false;
}

void cursorsio::server::button_thread(){
	while(1){
		long int now = js_date_now();
		for(auto& map : maps){
			for(auto& button : map.buttons){
				if(button.second.first.count < button.second.first.maxcount &&
					now - button.second.second > 2000){
					if(button.second.first.count == 0){
						for(auto& wall : map.walls){
							if(wall.second.color == button.second.first.color && wall.second.removed){
								wall.second.removed = false;
								map.objupd_q.push_back({
									cursorsio::map::create_wall(
										wall.second.x, wall.second.y,
										wall.second.w, wall.second.h,
										wall.second.color,
										wall.first, true)
								});
							}
						}
					}
					button.second.first.count++;
					map.objupd_q.push_back({
						cursorsio::map::create_button(button.second.first.x, button.second.first.y,
									      button.second.first.w, button.second.first.h,
									button.second.first.count, button.second.first.color,
									button.first, true)
					});
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main(int argc, char *argv[]) {
	cursorsio::server s;
	if(argc > 0){
		std::ifstream ifs(argv[1]);
		std::string mapdata( (std::istreambuf_iterator<char>(ifs) ),
				     (std::istreambuf_iterator<char>()    ) );
	s.start(9003, mapdata);
	}
}
