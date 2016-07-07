#include <fstream>

#include "server.hpp"
#include "map.hpp"

/* Compile with:
 * g++ -std=gnu++0x -DASIO_STANDALONE server.cpp map.cpp -I./websocketpp/ -I./asio/asio/include/ -lrt -lpthread -O2
 ***/

/* TODO:
 * Classify walls per color instead of id so i don't have to loop through all of them and compare the color?
 * More error checking
 * Clean my code more
 * Check for wallhack
 * Add more comments
 * Limit how much data a client can send, and kick if too much
 * Remove unused variables
 * Clean way of shutting down the server
 * Fix instant area -> exit move
 * Use asio timers instead of threads?
 ***/

long int js_date_now(){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return ms;
}

void cursorsio::server::settimer(){
	buttontimer = s.set_timer(1000, websocketpp::lib::bind(&cursorsio::server::button_thread,
					this, websocketpp::lib::placeholders::_1));
}

void cursorsio::server::start(uint16_t port, const std::string & file){
	mapfile = file;
	std::ifstream ifs(mapfile);
	std::string mapdata( (std::istreambuf_iterator<char>(ifs) ),
				(std::istreambuf_iterator<char>()));
	cursorsio::map::parse(this, mapdata, maps);
	
	//websocketpp::lib::thread thr1([&](){cursorsio::server::cmd_thread();});
	//thr1.detach();
	s.clear_access_channels(websocketpp::log::alevel::all);
	s.set_access_channels(websocketpp::log::alevel::connect);
	s.set_access_channels(websocketpp::log::alevel::disconnect);
	s.set_access_channels(websocketpp::log::alevel::app);
	
	s.set_reuse_addr(true);
	
	s.listen(asio::ip::tcp::v4(), port);
	s.start_accept();
	cursorsio::server::settimer();
	s.run();
}

void cursorsio::server::reload(){
	if(reloadstate != 0)
		return;
	std::cout << "Reloading the server..." << std::endl;
	reloadstate = 1;
	while(reloadstate == 1){
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::ifstream ifs(mapfile);
	std::string mapdata( (std::istreambuf_iterator<char>(ifs) ),
				(std::istreambuf_iterator<char>()));
	maps.clear();
	std::queue<uint32_t> empty;
	std::swap(freed_ids, empty);
	used_ids = 0;
	cursorsio::map::parse(this, mapdata, maps);
	for(auto& client : clients){
		std::vector<uint8_t> bytes = {STYPE_SET_CLIENT_ID};
		client.second.id = cursorsio::server::get_id();
		addtoarr(client.second.id, bytes);
		s.send(client.first, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
	}
	reloadstate = 0;
}

void cursorsio::server::on_open(wsserver* s, websocketpp::connection_hdl hdl) {
	std::vector<uint8_t> bytes = {STYPE_SET_CLIENT_ID};
	uint32_t newid = cursorsio::server::get_id();
	addtoarr(newid, bytes);
	clients[hdl] = { newid, maps[defaultmap].startpoint[0], maps[defaultmap].startpoint[1], defaultmap };
	s->send(hdl, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
	cursorsio::server::updateplayercount();
	cursorsio::server::nextmap(defaultmap, hdl);
}

void cursorsio::server::on_fail(wsserver* s, websocketpp::connection_hdl hdl) {
	try {
		clients.at(hdl);
		s->get_alog().write(websocketpp::log::alevel::app,
			"Connection fail in client id: " + std::to_string(clients[hdl].id));
		cursorsio::server::kick(hdl);
	} catch(const std::out_of_range) { }
}

void cursorsio::server::on_close(wsserver* s, websocketpp::connection_hdl hdl) {
	cursorsio::server::kick(hdl, false);
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
				uint16_t x = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t y = bitsToInt<uint16_t>(u16, bytes, o);
				if(cursorsio::server::checkpos(x, y, clients[hdl].mapid, hdl, false))
					break;
				clients[hdl].x = x;
				clients[hdl].y = y;
				//uint32_t G = bitsToInt<uint32_t>(u32, bytes, o);
				break;
			}
			case CTYPE_CLICK: {
				uint16_t x = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t y = bitsToInt<uint16_t>(u16, bytes, o);
				// clients[hdl].x != x && clients[hdl].y != y  <- Is this a good idea?
				if(cursorsio::server::checkpos(x, y, clients[hdl].mapid, hdl, true))
					break;
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
				cursorsio::server::kick(hdl);
				break;
		}
		cursorsio::server::process_updates(s, &maps[clients[hdl].mapid], clients[hdl].mapid);
	} else {
		s->get_alog().write(websocketpp::log::alevel::app,
			"Unknown msg received, closing connection for client id: " + std::to_string(clients[hdl].id));
		cursorsio::server::kick(hdl);
	}
}

void cursorsio::server::process_updates(wsserver* s, mapprop_t *map, uint32_t mapid, bool bypass){
	uint32_t now = js_date_now();
	if(now - map->updatetime > 70 || bypass){
		map->updatetime = now;
		std::vector<uint8_t> bytes = {STYPE_MAP_UPDATE};

		uint16_t inThisMap = 0;
		std::vector<uint8_t> clickpos;
		std::vector<websocketpp::connection_hdl> clhdl;
		for(auto& client : clients){
			if(client.second.mapid == mapid && inThisMap < 100){
				addtoarr(client.second.id, clickpos);
				addtoarr(client.second.x, clickpos);
				addtoarr(client.second.y, clickpos);
				clhdl.push_back({client.first});
				inThisMap++;
			}
		}
		addtoarr(inThisMap, bytes);
		bytes.insert(bytes.end(), &clickpos[0], &clickpos[clickpos.size()]);
		
		uint16_t clickTimes = map->click_q.size();
		addtoarr(clickTimes, bytes);
		for(auto& click : map->click_q){
			addtoarr(click.x, bytes);
			addtoarr(click.y, bytes);
		}
		map->click_q.clear();

		uint16_t wallsRemoved = map->removed_q.size();
		addtoarr(wallsRemoved, bytes);
		for(auto& id : map->removed_q){
			addtoarr(id, bytes);
		}
		map->removed_q.clear();

		uint16_t objectsUpdated = map->objupd_q.size();
		addtoarr(objectsUpdated, bytes);
		for(auto& object : map->objupd_q){
			bytes.insert(bytes.end(), &object[0], &object[object.size()]);
		}
		map->objupd_q.clear();

		uint16_t linesDrawed = map->draw_q.size();
		addtoarr(linesDrawed, bytes);
		for(auto& line : map->draw_q){
			addtoarr(line.x, bytes);
			addtoarr(line.y, bytes);
			addtoarr(line.x2, bytes);
			addtoarr(line.y2, bytes);
		}
		map->draw_q.clear();

		if(map->updplayercount){
			uint32_t playercount = clients.size();
			addtoarr(playercount, bytes); // Player count is uint32_t
			map->updplayercount = false;
		}

		for(auto& client : clhdl){
			s->send(client, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
		}
		map->lastcwasupdate = true;
		return;
	}
	map->lastcwasupdate = false;
}

void cursorsio::server::teleport_client(wsserver* s, websocketpp::connection_hdl hdl, uint16_t x, uint16_t y, uint32_t G){
	std::vector<uint8_t> bytes = {STYPE_TELEPORT_CLIENT};
	clients[hdl].x = x;
	clients[hdl].y = y;
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
	s.send(hdl, &maps[mapid].bytes[0], maps[mapid].bytes.size(), websocketpp::frame::opcode::binary);
	cursorsio::server::sendmapstate(clients[hdl].mapid, hdl);
	cursorsio::server::process_updates(&s, &(maps[mapid]), mapid);
}

bool cursorsio::server::checkpos(uint16_t x, uint16_t y, uint32_t mapid, websocketpp::connection_hdl hdl, bool click){
	try {
		maps.at(mapid);
		clients.at(hdl);
	} catch(const std::out_of_range) { return true; }
	uint32_t m = mapid;
	if(!click){
		for(auto& exit : maps[mapid].exits){
			if(x >= exit.second.x && x <= exit.second.x + exit.second.w
				&& y >= exit.second.y && y <= exit.second.y + exit.second.h){
				if(exit.second.isbad){
					teleport_client(&s, hdl, maps[mapid].startpoint[0], maps[mapid].startpoint[1], mapid);
				} else {
					cursorsio::server::nextmap(exit.second.linked, hdl);
				}
				return true;
			}
		}
		for(auto& area : maps[mapid].areas){
			if(x >= area.second.first.x && x <= area.second.first.x + area.second.first.w
				&& y >= area.second.first.y && y <= area.second.first.y + area.second.first.h){
				if(area.second.second.find(hdl) == area.second.second.end()){
					if(area.second.first.count > 0){
						area.second.first.count--;
						area.second.second.emplace(hdl);
						maps[mapid].objupd_q.push_back({
							cursorsio::map::create_area(area.second.first.x, area.second.first.y,
											area.second.first.w, area.second.first.h,
											area.second.first.count, area.second.first.color,
											area.first, true)
						});
						if(area.second.first.count == 0){
							for(auto& wall : maps[mapid].walls){
								if(wall.second.color == area.second.first.color && !wall.second.removed){
									maps[mapid].removed_q.push_back({wall.first});
									wall.second.removed = true;
								}
							}
						}
					}
					cursorsio::server::process_updates(&s, &(maps[mapid]), m, true);
				}
			} else if(area.second.second.find(hdl) != area.second.second.end()){
				if(area.second.first.count < area.second.first.maxcount){
					if(area.second.first.count == 0){
						for(auto& wall : maps[mapid].walls){
							if(wall.second.color == area.second.first.color && wall.second.removed){
								wall.second.removed = false;
								maps[mapid].objupd_q.push_back({
									cursorsio::map::create_wall(
										wall.second.x, wall.second.y,
										wall.second.w, wall.second.h,
										wall.second.color,
										wall.first, true)
								});
							}
						}
					}
					area.second.first.count++;
					maps[mapid].objupd_q.push_back({
						cursorsio::map::create_area(area.second.first.x, area.second.first.y,
										area.second.first.w, area.second.first.h,
										area.second.first.count, area.second.first.color,
										area.first, true)
					});
				}
				area.second.second.erase(hdl);
				cursorsio::server::process_updates(&s, &(maps[mapid]), m, true);
			}
		}
	} else {
		for(auto& button : maps[mapid].buttons){
			if(x >= button.second.first.x && x <= button.second.first.x + button.second.first.w
				&& y >= button.second.first.y && y <= button.second.first.y + button.second.first.h){
				if(button.second.first.count > 0){
					button.second.first.count--;
					//TODO: optimize this for fast clickers
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
					cursorsio::server::process_updates(&s, &(maps[mapid]), m);
				}
				button.second.second = js_date_now();
				return false;
			}
		}
	}
	return false;
}

void cursorsio::server::cmd_thread(){
	while(1){
		std::string cmd;
		std::cin >> cmd;
		if(cmd == "reload")
			cursorsio::server::reload();
	}
}

void cursorsio::server::button_thread(websocketpp::lib::error_code const& e){
	if(e){
		s.get_alog().write(websocketpp::log::alevel::app,
		"Button timer error!: " + e.message());
		return;
	}
	long int now = js_date_now();
	uint16_t updatedbuttons;
	for(auto it = maps.begin(); it != maps.end(); ++it){
		updatedbuttons = 0;
		for(auto& button : (*it).buttons){
			if(button.second.first.count < button.second.first.maxcount &&
				now - button.second.second > 2000){
				if(button.second.first.count == 0){
					for(auto& wall : (*it).walls){
						if(wall.second.color == button.second.first.color && wall.second.removed){
							wall.second.removed = false;
							(*it).objupd_q.push_back({
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
				(*it).objupd_q.push_back({
					cursorsio::map::create_button(button.second.first.x, button.second.first.y,
							      button.second.first.w, button.second.first.h,
								button.second.first.count, button.second.first.color,
								button.first, true)
				});
				updatedbuttons++;
			}
		}
		if(updatedbuttons > 0 || !(*it).lastcwasupdate)
			cursorsio::server::process_updates(&s, &(*it), std::distance(maps.begin(), it));
	}
	cursorsio::server::settimer();
}

void cursorsio::server::sendmapstate(uint32_t mapid, websocketpp::connection_hdl hdl){
	std::vector<uint8_t> bytes = {STYPE_MAP_UPDATE};

	uint16_t updates = 0;

	std::vector<uint8_t> updatedata;
	for(auto& client : clients){
		if(client.second.mapid == mapid && updates < 100){
			addtoarr(client.second.id, updatedata);
			addtoarr(client.second.x, updatedata);
			addtoarr(client.second.y, updatedata);
			updates++;
		}
	}
	addtoarr(updates, bytes);
	bytes.insert(bytes.end(), &updatedata[0], &updatedata[updatedata.size()]);
	updatedata.clear();
	updates = 0;

	addtoarr(updates, bytes); // Skip clicks
	
	for(auto& wall : maps[mapid].walls){
		if(wall.second.removed){
			addtoarr(wall.first, updatedata);
			updates++;
		}
	}
	addtoarr(updates, bytes);
	bytes.insert(bytes.end(), &updatedata[0], &updatedata[updatedata.size()]);
	updatedata.clear();
	updates = 0;

	for(auto& button : maps[mapid].buttons){
		if(button.second.first.count < button.second.first.maxcount){
			std::vector<uint8_t> buttondata =
				cursorsio::map::create_button(button.second.first.x, button.second.first.y,
								button.second.first.w, button.second.first.h,
								button.second.first.count, button.second.first.color,
								button.first, true);
			updatedata.insert(updatedata.end(), &buttondata[0], &buttondata[buttondata.size()]);
			updates++;
		}
	}
	for(auto& area : maps[mapid].areas){
		if(area.second.first.count < area.second.first.maxcount){
			std::vector<uint8_t> areadata =
				cursorsio::map::create_area(area.second.first.x, area.second.first.y,
								area.second.first.w, area.second.first.h,
								area.second.first.count, area.second.first.color,
								area.first, true);
			updatedata.insert(updatedata.end(), &areadata[0], &areadata[areadata.size()]);
			updates++;
		}
	}
	addtoarr(updates, bytes);
	bytes.insert(bytes.end(), &updatedata[0], &updatedata[updatedata.size()]);
	updatedata.clear();
	updates = 0;
	
	addtoarr(updates, bytes); // Skip drawings
	
	s.send(hdl, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
}

void cursorsio::server::updateplayercount(){
	for(auto& map : maps){
		map.updplayercount = true;
	}
}

void cursorsio::server::kick(websocketpp::connection_hdl hdl, bool close){
	cursorsio::server::free_id(clients[hdl].id);
	clients.erase(hdl);
	for(auto& map : maps){
		for(auto& area : map.areas){
			if(area.second.second.find(hdl) != area.second.second.end()){
				area.second.second.erase(hdl);
				if(area.second.first.count < area.second.first.maxcount){
					if(area.second.first.count == 0){
						for(auto& wall : map.walls){
							if(wall.second.color == area.second.first.color && wall.second.removed){
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
					area.second.first.count++;
					map.objupd_q.push_back({
						cursorsio::map::create_area(
							area.second.first.x, area.second.first.y,
							area.second.first.w, area.second.first.h,
							area.second.first.count, area.second.first.color,
							area.first, true)
					});
				}
			}
		}
	}
	if(close)
		s.close(hdl, 0, "");
	cursorsio::server::updateplayercount();
}

int main(int argc, char *argv[]) {
	if(argc > 1){
		cursorsio::server s;
		
		s.start(9003, argv[1]);
	} else {
		std::cout << "Usage: " << argv[0] << " MAP_FILE" << std::endl;
	}
}
