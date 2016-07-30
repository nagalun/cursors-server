#include <fstream>
#include <math.h>

#include "server.hpp"

/* Compile with:
 * g++ -std=gnu++0x -DASIO_STANDALONE server.cpp map.cpp -I./websocketpp/ -I./asio/asio/include/ -lrt -lpthread -O2
 ***/

/* TODO:
 * More error checking (complete?)
 * Clean my code more
 * Add more comments
 * Remove unused variables
 * Clean way of shutting down the server
 * Get rid of sendmapstate
 * Make cursors not get stuck inside walls
 * Add admin commands?
 ***/

long int js_date_now(){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return ms;
}

void cursorsio::server::settimer(){
	watchtimer = s.set_timer(1000, websocketpp::lib::bind(&cursorsio::server::watch_timer,
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

/*void cursorsio::server::reload(){
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
}*/

void cursorsio::server::on_open(wsserver* s, websocketpp::connection_hdl hdl) {
	std::vector<uint8_t> bytes = {STYPE_SET_CLIENT_ID};
	uint32_t newid = cursorsio::server::get_id();
	addtoarr(newid, bytes);
	uint16_t pos[2];
	memcpy(&pos, &maps[defaultmap].bytes[1], 4);
	clients[hdl] = { newid, pos[0], pos[1], defaultmap, 0 };
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
		clients[hdl].stats.bps += 9;
		/* Limit is 4,6 KB/s */
		if(clients[hdl].stats.bps > 4600){
			cursorsio::server::kick(hdl);
			return;
		}
		unsigned int o = 1;
		switch((uint8_t)msg->get_payload()[0]){
			case CTYPE_MOVE: {
				uint16_t pos[2];
				memcpy(&pos, &(msg->get_payload().c_str()[o]), 4);
				if(cursorsio::server::checkpos(pos[0], pos[1], clients[hdl].mapid, hdl, false))
					return;
				clients[hdl].x = pos[0];
				clients[hdl].y = pos[1];
				break;
			}
			case CTYPE_CLICK: {
				if(maps[clients[hdl].mapid].click_q.size() < 50){
					uint16_t pos[2];
					memcpy(&pos, &(msg->get_payload().c_str()[o]), 4);
					if(cursorsio::server::checkpos(pos[0], pos[1], clients[hdl].mapid, hdl, true))
						break;
					clients[hdl].x = pos[0];
					clients[hdl].y = pos[1];
					maps[clients[hdl].mapid].click_q.push_back({pos[0], pos[1]});
				} else { return; }
				break;
			}
			case CTYPE_DRAW: {
				if(maps[clients[hdl].mapid].draw_q.size() < 80){
					uint16_t pos[4];
					memcpy(&pos, &(msg->get_payload().c_str()[o]), 8);
					if(pos[0] > 400 || pos[1] > 300 || cursorsio::server::checkpos(pos[2], pos[3], clients[hdl].mapid, hdl, false))
						return;
					clients[hdl].x = pos[2];
					clients[hdl].y = pos[3];
					maps[clients[hdl].mapid].draw_q.push_back({pos[0], pos[1], pos[2], pos[3]});
				} else { return; }
				break;
			}
			default:
				s->get_alog().write(websocketpp::log::alevel::app,
					"Unknown msg received, closing connection for client id: " + std::to_string(clients[hdl].id));
				cursorsio::server::kick(hdl);
				break;
		}
		cursorsio::server::process_updates(s, &maps[clients[hdl].mapid], clients[hdl].mapid);
	} else if(msg->get_opcode() == websocketpp::frame::opcode::text && msg->get_payload().length() <= 80 && '\13' == msg->get_payload().back()) {
		/* Why would you want to send more than 1 message per second? */
		if(clients[hdl].stats.msgps == 0){
			std::string str = std::to_string(clients[hdl].id) + std::string(": ") + msg->get_payload();
			for(auto& client : clients){
				s->send(client.first, str.c_str(), websocketpp::frame::opcode::text);
			}
		} else if(clients[hdl].stats.msgps > 6){
			cursorsio::server::kick(hdl);
			return;
		}
		clients[hdl].stats.msgps++;
	} else {
		s->get_alog().write(websocketpp::log::alevel::app,
			"Unknown msg received, closing connection for client id: " + std::to_string(clients[hdl].id));
		cursorsio::server::kick(hdl);
	}
}

void cursorsio::server::process_updates(wsserver* s, mapprop_t *map, uint32_t mapid, bool bypass){
	uint32_t now = js_date_now();
	if(now - map->updatetime > 80 || bypass){
		map->updatetime = now;
		std::vector<uint8_t> bytes = {STYPE_MAP_UPDATE};

		uint16_t inThisMap = 0;
		std::vector<uint8_t> clickpos;
		std::vector<websocketpp::connection_hdl> clhdl;
		for(auto& client : clients){
			if(client.second.mapid == mapid){
				if(inThisMap <= 100){
					addtoarr(client.second.id, clickpos);
					addtoarr(client.second.x, clickpos);
					addtoarr(client.second.y, clickpos);
					inThisMap++;
				}
				clhdl.push_back({client.first});
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
		
		uint16_t linesDrawed = inThisMap <= 30 ? map->draw_q.size() : 0;
		addtoarr(linesDrawed, bytes);
		if(inThisMap <= 30){
			for(auto& line : map->draw_q){
				addtoarr(line.x, bytes);
				addtoarr(line.y, bytes);
				addtoarr(line.x2, bytes);
				addtoarr(line.y2, bytes);
			}
			map->draw_q.clear(); /* test */
		}

		if(map->updplayercount){
			uint32_t playercount = clients.size();
			addtoarr(playercount, bytes); // Player count is uint32_t
			map->updplayercount = false;
		}

		for(auto& client : clhdl){
			s->send(client, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
		}
		//map->lastcwasupdate = true; // not needed for now
		return;
	}
	//map->lastcwasupdate = false;
}

void cursorsio::server::teleport_client(wsserver* s, websocketpp::connection_hdl hdl, uint16_t x, uint16_t y, uint32_t G){
	if(clients[hdl].stats.tps < 15){
		std::vector<uint8_t> bytes = {STYPE_TELEPORT_CLIENT};
		clients[hdl].x = x;
		clients[hdl].y = y;
		addtoarr(x, bytes);
		addtoarr(y, bytes);
		addtoarr(G, bytes);
		s->send(hdl, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
	}
	clients[hdl].stats.tps++;
}

void cursorsio::server::nextmap(uint32_t mapid, websocketpp::connection_hdl hdl){
	try {
		maps.at(mapid);
		clients.at(hdl);
	} catch(const std::out_of_range) { return; }
	uint16_t pos[2];
	memcpy(&pos, &maps[mapid].bytes[1], 4);
	clients[hdl].x = pos[0];
	clients[hdl].y = pos[1];
	clients[hdl].mapid = mapid;
	
	s.send(hdl, &maps[mapid].bytes[0], maps[mapid].bytes.size(), websocketpp::frame::opcode::binary);
	cursorsio::server::sendmapstate(clients[hdl].mapid, hdl);
	cursorsio::server::process_updates(&s, &(maps[mapid]), mapid);
}

bool cursorsio::server::checkpos(uint16_t x, uint16_t y, uint32_t mapid, websocketpp::connection_hdl hdl, bool click){
	if(clients[hdl].x == x && clients[hdl].y == y && !click){
		return false;
	}
	uint32_t o = 1;
	try {
		o = maps[mapid].map.at(x + 400 * y);
	} catch(const std::out_of_range) { /* oh shit */ }
	if(x > 400 || y > 300 || o == 1){
		teleport_client(&s, hdl, clients[hdl].x, clients[hdl].y, mapid);
		return true;
	}
	int dX = x - clients[hdl].x;
	int dY = y - clients[hdl].y;
	float dist = sqrt((dX * dX) + (dY * dY));
	if(dist >= 10){
		float cX = clients[hdl].x;
		float cY = clients[hdl].y;
		for(;sqrt(pow(cX - clients[hdl].x,2) + pow(cY - clients[hdl].y,2)) < dist; cX += (10 / dist) * dX, cY += (10 / dist) * dY){
			uint16_t p = maps[mapid].map[floor(cX) + 400 * floor(cY)];
			switch(p){
				case 0:
					break;
				case 1:
					teleport_client(&s, hdl, clients[hdl].x, clients[hdl].y, mapid);
					return true;
					break;
				default:
					if(maps[mapid].bytes[p+4] == 1){
						uint32_t id;
						memcpy(&id, &maps[mapid].bytes.at(p), 4);
						if(maps[mapid].openeddoors.find(id) == maps[mapid].openeddoors.end()){
							teleport_client(&s, hdl, clients[hdl].x, clients[hdl].y, mapid);
							return true;
						}
					}
					break;
			}
		}
	}

	try {
		try {
		if(o != clients[hdl].ontile && maps[mapid].bytes.at(clients[hdl].ontile+4) == 3){
			uint32_t id;
			memcpy(&id, &maps[mapid].bytes[clients[hdl].ontile], 4);
			uint16_t count;
			memcpy(&count, &maps[mapid].bytes[clients[hdl].ontile+13], 2);
			if(maps[mapid].objectdata[id].second > 0){
				maps[mapid].objectdata[id].second--;
			}
			uint16_t newcount = maps[mapid].objectdata[id].second >= maps[mapid].objectdata[id].first ? 0 : maps[mapid].objectdata[id].first - maps[mapid].objectdata[id].second;
			if(newcount != count){
				maps[mapid].bytes[clients[hdl].ontile+13] = newcount;
				if(count == 0){
					uint32_t color;
					memcpy(&color, &maps[mapid].bytes[clients[hdl].ontile+15], 4);
					for(auto& door : maps[mapid].doors[color]){
						maps[mapid].openeddoors.erase(door.id);
						std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + door.pos;
						std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + door.pos + 17;
						std::vector<uint8_t> n(f, l);
						maps[mapid].objupd_q.push_back({n});
					}
				}
				{
					std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + clients[hdl].ontile;
					std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + clients[hdl].ontile + 19;
					std::vector<uint8_t> n(f, l);
					maps[mapid].objupd_q.push_back({n});
				}
				cursorsio::server::process_updates(&s, &(maps[mapid]), mapid, true);
			}
		}
		} catch(const std::out_of_range) { }
		if(o == 0) { clients[hdl].ontile = 0; return false; }
		uint32_t id;
		memcpy(&id, &maps[mapid].bytes.at(o), 4); /* Store the id for later */
		switch(maps[mapid].bytes[o+4]){ /* Switch on the object type */
			case 1: /* Wall/Door type, in this case, it must be a door, check if its open. */
				if(maps[mapid].openeddoors.find(id) == maps[mapid].openeddoors.end()){
					teleport_client(&s, hdl, clients[hdl].x, clients[hdl].y, mapid);
					return true;
				}
				break;
			case 2: { /* Exit point */
				if(maps[mapid].bytes.at(o+13) == 1){ /* Check if the exit point is bad */
					uint16_t pos[2];
					memcpy(&pos, &maps[mapid].bytes[1], 4);
					teleport_client(&s, hdl, pos[0], pos[1], mapid);
				} else {
					/* Teleport to linked map. */
					cursorsio::server::nextmap(maps[mapid].objectdata.at(id).first, hdl);
				}
				return true;
				break;
			}
			case 3: { /* Area trigger */
				if(clients[hdl].ontile != o){
					clients[hdl].ontile = o;
					uint16_t count;
					memcpy(&count, &maps[mapid].bytes[o+13], 2);
					maps[mapid].objectdata[id].second++;
					uint16_t newcount = maps[mapid].objectdata[id].second >= maps[mapid].objectdata[id].first ? 0 : maps[mapid].objectdata[id].first - maps[mapid].objectdata[id].second;
					if(newcount != count){
						maps[mapid].bytes[o+13] = newcount;
						if(newcount == 0){
							uint32_t color; /* Color of the area */
							memcpy(&color, &maps[mapid].bytes[o+15], 4);
							for(auto& door : maps[mapid].doors[color]){
								maps[mapid].openeddoors.emplace(door.id);
								maps[mapid].removed_q.push_back({door.id});
							}
						}
						{
							std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + o;
							std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + o + 19;
							std::vector<uint8_t> n(f, l);
							maps[mapid].objupd_q.push_back({n});
						}
						cursorsio::server::process_updates(&s, &(maps[mapid]), mapid, true);
					}
				}
				break;
			}
			case 4: { /* Button */
				if(click){
					uint32_t color; /* Color of the button */
					memcpy(&color, &maps[mapid].bytes[o+15], 4);
					if(color == 0){
						return false;
					}
					/* Button count */
					uint16_t count;
					memcpy(&count, &maps[mapid].bytes[o+13], 2);
					if(count > 0){
						/* Decrease counter and update button */
						count--;
						maps[mapid].bytes[o+13] = count; /* ... */
						if(count == 0){
							for(auto& door : maps[mapid].doors[color]){
								maps[mapid].openeddoors.emplace(door.id);
								maps[mapid].removed_q.push_back({door.id});
							}
						}
						{
							std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + o;
							std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + o + 19;
							std::vector<uint8_t> n(f, l);
							maps[mapid].objupd_q.push_back({n});
						}
						cursorsio::server::process_updates(&s, &(maps[mapid]), mapid, true);
					}
					activebuttons[o] = {js_date_now(), mapid};
				}
				break;
			}
		}
		clients[hdl].ontile = o;
	} catch(const std::out_of_range) { return true; }
	return false;
}

/*void cursorsio::server::cmd_thread(){
	while(1){
		std::string cmd;
		std::cin >> cmd;
		if(cmd == "reload")
			reloadstate = 1;
	}
}*/

void cursorsio::server::watch_timer(websocketpp::lib::error_code const& e){
	if(e){
		s.get_alog().write(websocketpp::log::alevel::app,
		"Button timer error!: " + e.message());
		return;
	}
	uint32_t now = js_date_now();
	for(auto b = activebuttons.cbegin(); b != activebuttons.cend();){
		if(now - (*b).second.first > 2000){
			uint16_t o = (*b).first;
			uint32_t id;
			memcpy(&id, &maps[(*b).second.second].bytes.at(o), 4);
			uint32_t maxcount = maps[(*b).second.second].objectdata[id].first;
			uint16_t count;
			memcpy(&count, &maps[(*b).second.second].bytes[o+13], 2);
			if(count == 0){
				uint32_t color;
				memcpy(&color, &maps[(*b).second.second].bytes[o+15], 4);
				for(auto& door : maps[(*b).second.second].doors[color]){
					maps[(*b).second.second].openeddoors.erase(door.id);
					std::vector<uint8_t>::const_iterator f = maps[(*b).second.second].bytes.begin() + door.pos;
					std::vector<uint8_t>::const_iterator l = maps[(*b).second.second].bytes.begin() + door.pos + 17;
					std::vector<uint8_t> n(f, l);
					maps[(*b).second.second].objupd_q.push_back({n});
				}
			}
			count++;
			maps[(*b).second.second].bytes[o+13] = count;
			{
				std::vector<uint8_t>::const_iterator f = maps[(*b).second.second].bytes.begin() + o;
				std::vector<uint8_t>::const_iterator l = maps[(*b).second.second].bytes.begin() + o + 19;
				std::vector<uint8_t> n(f, l);
				maps[(*b).second.second].objupd_q.push_back({n});
			}
			cursorsio::server::process_updates(&s, &maps[(*b).second.second], (*b).second.second, true);
			if(count >= (maxcount & 0xFFFF)){
				activebuttons.erase(b++);
				continue;
			}
		}
		b++;
	}
	
	for(auto& client : clients){
		client.second.stats.bps = 0;
		client.second.stats.msgps = 0;
		client.second.stats.tps = 0;
	}
	cursorsio::server::settimer();
}

void cursorsio::server::sendmapstate(uint32_t mapid, websocketpp::connection_hdl hdl){
	std::vector<uint8_t> bytes = {STYPE_MAP_UPDATE};

	uint16_t updates = 0;

	std::vector<uint8_t> updatedata;
	addtoarr(updates, bytes);

	addtoarr(updates, bytes); // Skip clicks
	
	for(auto& door : maps[mapid].openeddoors){
		addtoarr(door, updatedata);
		updates++;
	}
	addtoarr(updates, bytes);
	bytes.insert(bytes.end(), &updatedata[0], &updatedata[updatedata.size()]);
	updatedata.clear();
	updates = 0;

	addtoarr(updates, bytes);
	
	addtoarr(updates, bytes); // Skip drawings
	
	s.send(hdl, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
}

void cursorsio::server::updateplayercount(){
	for(auto& map : maps){
		map.updplayercount = true;
	}
}

void cursorsio::server::kick(websocketpp::connection_hdl hdl, bool close){
	//cursorsio::server::free_id(clients[hdl].id);
	try {
	if(clients[hdl].ontile != 0 && maps[clients[hdl].mapid].bytes.at(clients[hdl].ontile+4) == 3){
		uint32_t id;
		memcpy(&id, &maps[clients[hdl].mapid].bytes[clients[hdl].ontile], 4);
		uint16_t count;
		memcpy(&count, &maps[clients[hdl].mapid].bytes[clients[hdl].ontile+13], 2);
		if(maps[clients[hdl].mapid].objectdata[id].second > 0){
			maps[clients[hdl].mapid].objectdata[id].second--;
		}
		uint16_t newcount = maps[clients[hdl].mapid].objectdata[id].second >= maps[clients[hdl].mapid].objectdata[id].first ? 0 : maps[clients[hdl].mapid].objectdata[id].first - maps[clients[hdl].mapid].objectdata[id].second;
		if(newcount != count){
			maps[clients[hdl].mapid].bytes[clients[hdl].ontile+13] = newcount;
			if(count == 0){
				uint32_t color;
				memcpy(&color, &maps[clients[hdl].mapid].bytes[clients[hdl].ontile+15], 4);
				for(auto& door : maps[clients[hdl].mapid].doors[color]){
					maps[clients[hdl].mapid].openeddoors.erase(door.id);
					std::vector<uint8_t>::const_iterator f = maps[clients[hdl].mapid].bytes.begin() + door.pos;
					std::vector<uint8_t>::const_iterator l = maps[clients[hdl].mapid].bytes.begin() + door.pos + 17;
					std::vector<uint8_t> n(f, l);
					maps[clients[hdl].mapid].objupd_q.push_back({n});
				}
			}
			{
				std::vector<uint8_t>::const_iterator f = maps[clients[hdl].mapid].bytes.begin() + clients[hdl].ontile;
				std::vector<uint8_t>::const_iterator l = maps[clients[hdl].mapid].bytes.begin() + clients[hdl].ontile + 19;
				std::vector<uint8_t> n(f, l);
				maps[clients[hdl].mapid].objupd_q.push_back({n});
			}
		}
	}
	} catch(const std::out_of_range) { }
	clients.erase(hdl);
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
