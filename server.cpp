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
 * Redo position checking
 * Check for wallhack
 * Add more comments
 * Limit how much data a client can send, and kick if too much
 * Remove unused variables
 * Clean way of shutting down the server
 * Fix instant area -> exit move
 * get rid of sendmapstate
 * add limit to how many teleports can the server send
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
	uint16_converter u16;
	u16.c[0] = maps[defaultmap].bytes[1];
	u16.c[1] = maps[defaultmap].bytes[2];
	uint16_t x = u16.i;
	u16.c[0] = maps[defaultmap].bytes[3];
	u16.c[1] = maps[defaultmap].bytes[4];
	clients[hdl] = { newid, x, u16.i /*y*/, defaultmap, 0 };
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
		unsigned int o = 1;
		uint16_converter u16;
		switch((uint8_t)msg->get_payload()[0]){
			case CTYPE_MOVE: {
				uint16_t pos[2];
				u16.c[0] = msg->get_payload().c_str()[o];
				u16.c[1] = msg->get_payload().c_str()[o+1];
				pos[0] = u16.i;
				o += 2;
				u16.c[0] = msg->get_payload().c_str()[o];
				u16.c[1] = msg->get_payload().c_str()[o+1];
				pos[1] = u16.i;
				if(cursorsio::server::checkpos(pos[0], pos[1], clients[hdl].mapid, hdl, false))
					return;
				clients[hdl].x = pos[0];
				clients[hdl].y = pos[1];
				break;
			}
			case CTYPE_CLICK: {
				if(maps[clients[hdl].mapid].click_q.size() < 50){
					uint16_t pos[2];
					u16.c[0] = msg->get_payload().c_str()[o];
					u16.c[1] = msg->get_payload().c_str()[o+1];
					pos[0] = u16.i;
					o += 2;
					u16.c[0] = msg->get_payload().c_str()[o];
					u16.c[1] = msg->get_payload().c_str()[o+1];
					pos[1] = u16.i;
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
					u16.c[0] = msg->get_payload().c_str()[o];
					u16.c[1] = msg->get_payload().c_str()[o+1];
					pos[0] = u16.i;
					if(u16.i > 400) return;
					o += 2;
					u16.c[0] = msg->get_payload().c_str()[o];
					u16.c[1] = msg->get_payload().c_str()[o+1];
					pos[1] = u16.i;
					if(u16.i > 300) return;
					o += 2;
					u16.c[0] = msg->get_payload().c_str()[o];
					u16.c[1] = msg->get_payload().c_str()[o+1];
					pos[2] = u16.i;
					if(u16.i > 400) return;
					o += 2;
					u16.c[0] = msg->get_payload().c_str()[o];
					u16.c[1] = msg->get_payload().c_str()[o+1];
					pos[3] = u16.i;
					if(u16.i > 300) return;
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
		std::string str = std::to_string(clients[hdl].id) + std::string(": ") + msg->get_payload();
		for(auto& client : clients){
			s->send(client.first, str.c_str(), websocketpp::frame::opcode::text);
		}
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
	uint16_converter u16;
	u16.c[0] = maps[mapid].bytes[1];
	u16.c[1] = maps[mapid].bytes[2];
	clients[hdl].x = u16.i;
	u16.c[0] = maps[mapid].bytes[3];
	u16.c[1] = maps[mapid].bytes[4];
	clients[hdl].y = u16.i;
	clients[hdl].mapid = mapid;
	
	s.send(hdl, &maps[mapid].bytes[0], maps[mapid].bytes.size(), websocketpp::frame::opcode::binary);
	cursorsio::server::sendmapstate(clients[hdl].mapid, hdl);
	cursorsio::server::process_updates(&s, &(maps[mapid]), mapid);
}

bool cursorsio::server::checkpos(uint16_t x, uint16_t y, uint32_t mapid, websocketpp::connection_hdl hdl, bool click){
	uint32_t o = 1;
	try {
		maps.at(mapid);
		clients.at(hdl);
		o = maps[mapid].map.at(x + 400 * y);
	} catch(const std::out_of_range) { /* oh shit */ }
	/* TODO: more wallhack checking here */
	if(x > 400 || y > 300 || o == 1){
		teleport_client(&s, hdl, clients[hdl].x, clients[hdl].y, mapid);
		return true;
	}
	try {
		uint16_converter u16;
		uint32_converter u32;
		try {
		if(o != clients[hdl].ontile && maps[mapid].bytes.at(clients[hdl].ontile+4) == 3){
			u32.c[0] = maps[mapid].bytes[clients[hdl].ontile];
			u32.c[1] = maps[mapid].bytes[clients[hdl].ontile+1];
			u32.c[2] = maps[mapid].bytes[clients[hdl].ontile+2];
			u32.c[3] = maps[mapid].bytes[clients[hdl].ontile+3];
			u16.c[0] = maps[mapid].bytes[clients[hdl].ontile+13];
			u16.c[1] = maps[mapid].bytes[clients[hdl].ontile+14];
			if(maps[mapid].objectdata[u32.i].second > 0){
				maps[mapid].objectdata[u32.i].second--;
			}
			uint16_t count = maps[mapid].objectdata[u32.i].second >= maps[mapid].objectdata[u32.i].first ? 0 : maps[mapid].objectdata[u32.i].first - maps[mapid].objectdata[u32.i].second;
			if(count != u16.i){
				maps[mapid].bytes[clients[hdl].ontile+13] = count;
				if(u16.i == 0){
					u32.c[0] = maps[mapid].bytes[clients[hdl].ontile+15]; /* Color of the area */
					u32.c[1] = maps[mapid].bytes[clients[hdl].ontile+16];
					u32.c[2] = maps[mapid].bytes[clients[hdl].ontile+17];
					u32.c[3] = maps[mapid].bytes[clients[hdl].ontile+18];
					for(auto& door : maps[mapid].doors[u32.i]){
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
		u32.c[0] = maps[mapid].bytes.at(o); /* Store the ID for later */
		u32.c[1] = maps[mapid].bytes[o+1];
		u32.c[2] = maps[mapid].bytes[o+2];
		u32.c[3] = maps[mapid].bytes[o+3];
		switch(maps[mapid].bytes[o+4]){ /* Switch on the object type */
			case 1: /* Wall/Door type, in this case, it must be a door, check if its open. */
				if(maps[mapid].openeddoors.find(u32.i) == maps[mapid].openeddoors.end()){
					teleport_client(&s, hdl, clients[hdl].x, clients[hdl].y, mapid);
					return true;
				}
				break;
			case 2: { /* Exit point */
				if(maps[mapid].bytes.at(o+13) == 1){ /* Check if the exit point is bad */
					u16.c[0] = maps[mapid].bytes[1];
					u16.c[1] = maps[mapid].bytes[2];
					uint16_t x = u16.i;
					u16.c[0] = maps[mapid].bytes[3];
					u16.c[1] = maps[mapid].bytes[4]; /* No need to copy y */
					teleport_client(&s, hdl, x, u16.i, mapid);
				} else {
					/* Teleport to linked map. */
					cursorsio::server::nextmap(maps[mapid].objectdata.at(u32.i).first, hdl);
				}
				break;
			}
			case 3: { /* Area trigger */
				if(clients[hdl].ontile != o){
					clients[hdl].ontile = o;
					u16.c[0] = maps[mapid].bytes.at(o+13);
					u16.c[1] = maps[mapid].bytes[o+14];
					maps[mapid].objectdata[u32.i].second++;
					uint16_t count = maps[mapid].objectdata[u32.i].second >= maps[mapid].objectdata[u32.i].first ? 0 : maps[mapid].objectdata[u32.i].first - maps[mapid].objectdata[u32.i].second;
					if(count != u16.i){
						maps[mapid].bytes[o+13] = count;
						if(count == 0){
							u32.c[0] = maps[mapid].bytes[o+15]; /* Color of the area */
							u32.c[1] = maps[mapid].bytes[o+16];
							u32.c[2] = maps[mapid].bytes[o+17];
							u32.c[3] = maps[mapid].bytes[o+18];
							for(auto& door : maps[mapid].doors[u32.i]){
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
					u32.c[0] = maps[mapid].bytes[o+15]; /* Color of the button */
					u32.c[1] = maps[mapid].bytes[o+16];
					u32.c[2] = maps[mapid].bytes[o+17];
					u32.c[3] = maps[mapid].bytes[o+18];
					if(u32.i == 0){
						return false;
					}
					/* Button count */
					u16.c[0] = maps[mapid].bytes.at(o+13);
					u16.c[1] = maps[mapid].bytes[o+14];
					if(u16.i > 0){
						/* Decrease counter and update button */
						u16.i--;
						maps[mapid].bytes[o+13] = u16.i; /* ... */
						if(u16.i == 0){
							u32.c[0] = maps[mapid].bytes[o+15]; /* Color of the button */
							u32.c[1] = maps[mapid].bytes[o+16];
							u32.c[2] = maps[mapid].bytes[o+17];
							u32.c[3] = maps[mapid].bytes[o+18];
							for(auto& door : maps[mapid].doors[u32.i]){
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
	uint32_converter u16;
	uint32_converter u32;
	for(auto b = activebuttons.cbegin(); b != activebuttons.cend();){
		if(now - (*b).second.first > 2000){
			uint16_t o = (*b).first;
			u32.c[0] = maps[(*b).second.second].bytes[o]; /* ID */
			u32.c[1] = maps[(*b).second.second].bytes[o+1];
			u32.c[2] = maps[(*b).second.second].bytes[o+2];
			u32.c[3] = maps[(*b).second.second].bytes[o+3];
			uint32_t id = u32.i;
			uint32_t maxcount = maps[(*b).second.second].objectdata[id].first;
			u16.c[0] = maps[(*b).second.second].bytes[o+13]; /* Count */
			u16.c[1] = maps[(*b).second.second].bytes[o+14];
			if(u16.i == 0){
				u32.c[0] = maps[(*b).second.second].bytes[o+15]; /* Color */
				u32.c[1] = maps[(*b).second.second].bytes[o+16];
				u32.c[2] = maps[(*b).second.second].bytes[o+17];
				u32.c[3] = maps[(*b).second.second].bytes[o+18];
				for(auto& door : maps[(*b).second.second].doors[u32.i]){
					maps[(*b).second.second].openeddoors.erase(door.id);
					std::vector<uint8_t>::const_iterator f = maps[(*b).second.second].bytes.begin() + door.pos;
					std::vector<uint8_t>::const_iterator l = maps[(*b).second.second].bytes.begin() + door.pos + 17;
					std::vector<uint8_t> n(f, l);
					maps[(*b).second.second].objupd_q.push_back({n});
				}
			}
			u16.i++;
			maps[(*b).second.second].bytes[o+13] = u16.i;
			{
				std::vector<uint8_t>::const_iterator f = maps[(*b).second.second].bytes.begin() + o;
				std::vector<uint8_t>::const_iterator l = maps[(*b).second.second].bytes.begin() + o + 19;
				std::vector<uint8_t> n(f, l);
				maps[(*b).second.second].objupd_q.push_back({n});
			}
			cursorsio::server::process_updates(&s, &maps[(*b).second.second], (*b).second.second, true);
			if(u16.i >= maxcount & 0xFFFF){
				activebuttons.erase(b++);
				continue;
			}
		}
		b++;
	}
	
		/*if(updatedbuttons > 0 || !(*it).lastcwasupdate)
			cursorsio::server::process_updates(&s, &(*it), std::distance(maps.begin(), it));*/
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
		uint32_converter u32;
		uint16_converter u16;
		u32.c[0] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile];
		u32.c[1] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+1];
		u32.c[2] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+2];
		u32.c[3] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+3];
		u16.c[0] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+13];
		u16.c[1] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+14];
		if(maps[clients[hdl].mapid].objectdata[u32.i].second > 0){
			maps[clients[hdl].mapid].objectdata[u32.i].second--;
		}
		uint16_t count = maps[clients[hdl].mapid].objectdata[u32.i].second >= maps[clients[hdl].mapid].objectdata[u32.i].first ? 0 : maps[clients[hdl].mapid].objectdata[u32.i].first - maps[clients[hdl].mapid].objectdata[u32.i].second;
		if(count != u16.i){
			maps[clients[hdl].mapid].bytes[clients[hdl].ontile+13] = count;
			if(u16.i == 0){
				u32.c[0] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+15]; /* Color of the area */
				u32.c[1] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+16];
				u32.c[2] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+17];
				u32.c[3] = maps[clients[hdl].mapid].bytes[clients[hdl].ontile+18];
				for(auto& door : maps[clients[hdl].mapid].doors[u32.i]){
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
