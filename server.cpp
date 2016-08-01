#include "server.hpp"

#include <fstream>
#include <math.h>

/*
 * Compile with:
 * g++ -std=c++11 -O3 -I uWebSockets/src uWebSockets/src/Extensions.cpp uWebSockets/src/HTTPSocket.cpp uWebSockets/src/Network.cpp uWebSockets/src/Server.cpp uWebSockets/src/UTF8.cpp uWebSockets/src/WebSocket.cpp server.cpp map.cpp -o uWS -luv -lcrypto -lssl -lz
 **/

void cursorsio::server::run(const std::string &mapfile, uint8_t threads){
	{
		std::ifstream ifs;
		ifs.open(mapfile);
		std::string mapdata((std::istreambuf_iterator<char>(ifs)),
				    (std::istreambuf_iterator<char>()));
		cursorsio::map::parse(this, mapdata, maps);
		ifs.close();
	}
	uv_timer_init(uv_default_loop(), &w_hdl);
	uv_timer_start(&w_hdl, (uv_timer_cb) &watch_timer, 1000, 1000);
	w_hdl.data = this;
	try {
		if(threads == 1){
			uWS::Server s(port, uWS::NO_DELAY);
			register_events(s);
			s.run();
		} else if(threads > 1){
			std::cout << "Threads are unimplemented at the moment." << std::endl;
		}
	} catch (...) {
		std::cout << "ERR_LISTEN" << std::endl;
	}
}

void cursorsio::server::kick(uWS::WebSocket &socket, bool close){
	uint32_t mapid = 0;
	try {
		mapid = clients.at(socket).mapid;
		if(clients[socket].ontile != 0)
			updatetile(socket);
		clients.erase(socket);
	} catch(std::out_of_range) {  }
	if(close)
		socket.close();
	updateplayercount();
	process_updates(mapid, true);
}

void cursorsio::server::register_events(uWS::Server &server){
	server.onConnection([this](uWS::WebSocket socket) {
		std::vector<uint8_t> bytes = {STYPE_SET_CLIENT_ID};
		uint32_t newid = getid();
		std::cout << "Client connected. (" << newid << ")" << std::endl;
		addtoarr(newid, bytes);
		uint16_t pos[2];
		memcpy(&pos, &maps[0].bytes[1], 4);
		clients[socket] = { newid, pos[0], pos[1], 0, 0 };
		socket.send((char *)(&bytes[0]), bytes.size(), uWS::BINARY);
		updateplayercount();
		nextmap(0, socket);
	});
	
	server.onDisconnection([this](uWS::WebSocket socket, int code, const char *message, size_t length) {
		uint32_t id = 0;
		try {
			id = clients.at(socket).id;
		} catch(std::out_of_range) { }
		std::cout << "Client disconnected. (" <<
			  (id == 0 ? std::string("???") : std::to_string(id))
			  << ")" << std::endl;
		if(id != 0) kick(socket);
	});
	
	server.onMessage([this, &server](uWS::WebSocket socket, const char *message, size_t length, uWS::OpCode opCode) {
		try {
			clients.at(socket);
		} catch(std::out_of_range) { socket.close(); return; }
		if(opCode == uWS::BINARY && length == 9){
			switch((uint8_t)message[0]){
				case CTYPE_MOVE: {
					uint16_t x = ((((uint16_t)message[2]) << 8) | (uint8_t)message[1]);
					uint16_t y = ((((uint16_t)message[4]) << 8) | (uint8_t)message[3]);
					checkpos(x, y, socket);
					break;
				}
				case CTYPE_CLICK: {
					if(maps[clients[socket].mapid].click_q.size() < 70){
						uint16_t x = ((((uint16_t)message[2]) << 8) | (uint8_t)message[1]);
						uint16_t y = ((((uint16_t)message[4]) << 8) | (uint8_t)message[3]);
						checkpos(x, y, socket, true);
					}
					break;
				}
				case CTYPE_DRAW: {
					if(maps[clients[socket].mapid].draw_q.size() < 80){
						uint16_t x = ((((uint16_t)message[2]) << 8) | (uint8_t)message[1]);
						uint16_t y = ((((uint16_t)message[4]) << 8) | (uint8_t)message[3]);
						uint16_t x2 = ((((uint16_t)message[6]) << 8) | (uint8_t)message[5]);
						uint16_t y2 = ((((uint16_t)message[8]) << 8) | (uint8_t)message[7]);
						if(x > 400 || y > 300 || !checkpos(x2, y2, socket))
							break;
						maps[clients[socket].mapid].draw_q.push_back({x, y, x2, y2});
					}
					break;
				}
				default:
					std::cout << "Unknown msg received, (Client id: " << clients[socket].id << ")" << std::endl;
					kick(socket, true);
					break;
			}
		} else if(opCode == uWS::TEXT && length <= 80 && message[length-1] == '\13'){
			std::string msg = std::to_string(clients[socket].id) + std::string(": ") + std::string(message, length-1);
			server.broadcast(&msg[0], msg.size(), uWS::TEXT);
		} else {
			std::cout << "Unknown msg received, (Client id: " << clients[socket].id << ")" << std::endl;
			kick(socket, true);
		}
	});
}

void cursorsio::server::process_updates(uint32_t mapid, bool bypass){
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	if(bypass || std::chrono::duration_cast<std::chrono::milliseconds>(now-maps[mapid].updatetime).count() > 80){
		maps[mapid].updatetime = now;
		std::vector<uint8_t> bytes = {STYPE_MAP_UPDATE};

		uint16_t inThisMap = 0;
		std::vector<uint8_t> clickpos;
		std::vector<uWS::WebSocket> clhdl;
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
		
		uint16_t clickTimes = maps[mapid].click_q.size();
		addtoarr(clickTimes, bytes);
		for(auto& click : maps[mapid].click_q){
			addtoarr(click.x, bytes);
			addtoarr(click.y, bytes);
		}
		maps[mapid].click_q.clear();

		uint16_t wallsRemoved = maps[mapid].removed_q.size();
		addtoarr(wallsRemoved, bytes);
		for(auto& id : maps[mapid].removed_q){
			addtoarr(id, bytes);
		}
		maps[mapid].removed_q.clear();

		uint16_t objectsUpdated = maps[mapid].objupd_q.size();
		addtoarr(objectsUpdated, bytes);
		for(auto& object : maps[mapid].objupd_q){
			bytes.insert(bytes.end(), &object[0], &object[object.size()]);
		}
		maps[mapid].objupd_q.clear();
		
		uint16_t linesDrawed = inThisMap <= 30 ? maps[mapid].draw_q.size() : 0;
		addtoarr(linesDrawed, bytes);
		if(inThisMap <= 30){
			for(auto& line : maps[mapid].draw_q){
				addtoarr(line.x, bytes);
				addtoarr(line.y, bytes);
				addtoarr(line.x2, bytes);
				addtoarr(line.y2, bytes);
			}
			maps[mapid].draw_q.clear(); /* test */
		}

		if(maps[mapid].updplayercount){
			uint32_t playercount = clients.size();
			addtoarr(playercount, bytes); // Player count is uint32_t
			maps[mapid].updplayercount = false;
		}

		for(auto& socket : clhdl){
			socket.send((char*)(&bytes[0]), bytes.size(), uWS::BINARY);
		}
		//maps[mapid].lastcwasupdate = true; // not needed for now
		return;
	}
	//maps[mapid].lastcwasupdate = false;
}

bool cursorsio::server::issolid(uint16_t pos, uint32_t mapid){
	if(pos < 2) return !!pos;
	try {
		switch((uint8_t)maps[mapid].bytes.at(pos+4)){
			case 1: {
				uint32_t id;
				memcpy(&id, &maps[mapid].bytes[pos], 4);
				if(maps[mapid].openeddoors.find(id) == maps[mapid].openeddoors.end()){
					return true;
				}
			}
		}
	} catch(std::out_of_range) { }
	return false;
}

std::array<uint16_t, 2> cursorsio::server::correctpos(uint16_t x, uint16_t y, uint32_t mapid){
	short int offsetx = 0;
	short int offsety = 0;
	for(uint16_t i = 0; i < 400; i++){
		if(x - i >= 0 && !issolid(maps[mapid].map[x - i + 400 * y], mapid)) offsetx = -i;
		if(x + i < 400 && !issolid(maps[mapid].map[x + i + 400 * y], mapid)) offsetx = i;
		if(offsetx != 0) break;
	}
	for(uint16_t i = 0; i < 300; i++){
		if(y - i >= 0 && !issolid(maps[mapid].map[x + 400 * (y - i)], mapid)) offsety = -i;
		if(y + i < 300 && !issolid(maps[mapid].map[x + 400 * (y + i)], mapid)) offsety = i;
		if(offsety != 0) break;
	}
	std::array<uint16_t, 2> pos = {x, y};
	if(offsetx != 0 && (offsetx < 0 ? -offsetx : offsetx) < (offsety < 0 ? -offsety : offsety)) pos[0] = x + offsetx;
	else if(offsety != 0) pos[1] = y + offsety;
	else memcpy(&pos, &maps[mapid].bytes[1], 4);
	return pos;
}

void cursorsio::server::teleport_client(uWS::WebSocket socket, uint16_t x, uint16_t y, uint32_t G){
	//if(clients[hdl].stats.tps < 15){
	uint16_t atpos = maps[G].map.at(x + 400 * y);
	/* There is no need to check if the door is open */
	if(atpos == 1 || atpos != 0 && (uint8_t)maps[G].bytes.at(atpos+4) == 1){
		std::array<uint16_t, 2> pos = correctpos(x, y, G);
		x = pos[0];
		y = pos[1];
	}
	std::vector<uint8_t> bytes = {STYPE_TELEPORT_CLIENT};
	clients[socket].x = x;
	clients[socket].y = y;
	addtoarr(x, bytes);
	addtoarr(y, bytes);
	addtoarr(G, bytes);
	socket.send((char*)(&bytes[0]), bytes.size(), uWS::BINARY);
	//}
	//clients[hdl].stats.tps++;
}

bool cursorsio::server::checkpos(uint16_t &x, uint16_t &y, uWS::WebSocket &socket, bool click){
	if(clients[socket].x == x && clients[socket].y == y && !click){
		return true;
	}
	uint32_t o = 1;
	bool bypass = false;
	const uint32_t mapid = clients[socket].mapid;
	try {
		o = maps[mapid].map.at(x + 400 * y);
	} catch(const std::out_of_range) { /* oh shit */ }
	if(x >= 400 || y >= 300 || o == 1){
		teleport_client(socket, clients[socket].x, clients[socket].y, mapid);
		return false;
	}
	int dX = x - clients[socket].x;
	int dY = y - clients[socket].y;
	float dist = sqrt((dX * dX) + (dY * dY));
	if(dist >= 10){
		float cX = clients[socket].x;
		float cY = clients[socket].y;
		for(;sqrt(pow(cX - clients[socket].x,2) + pow(cY - clients[socket].y,2)) < dist; cX += (10 / dist) * dX, cY += (10 / dist) * dY){
			uint16_t p = maps[mapid].map[floor(cX) + 400 * floor(cY)];
			switch(p){
				case 0:
					break;
				case 1:
					teleport_client(socket, clients[socket].x, clients[socket].y, mapid);
					return false;
					break;
				default:
					if(maps[mapid].bytes[p+4] == 1){
						uint32_t id;
						memcpy(&id, &maps[mapid].bytes.at(p), 4);
						if(maps[mapid].openeddoors.find(id) == maps[mapid].openeddoors.end()){
							teleport_client(socket, clients[socket].x, clients[socket].y, mapid);
							return false;
						}
					}
					break;
			}
		}
	}

	if(o != 0) try {
		uint32_t id;
		memcpy(&id, &maps[mapid].bytes.at(o), 4); /* Store the id for later */
		switch(maps[mapid].bytes[o+4]){ /* Switch on the object type */
			case 1: /* Wall/Door type, in this case, it must be a door, check if its open. */
				if(maps[mapid].openeddoors.find(id) == maps[mapid].openeddoors.end()){
					teleport_client(socket, clients[socket].x, clients[socket].y, mapid);
					return false;
				}
				break;
			case 2: { /* Exit point */
				if(maps[mapid].bytes.at(o+13) == 1){ /* Check if the exit point is bad */
					uint16_t pos[2];
					memcpy(&pos, &maps[mapid].bytes[1], 4);
					teleport_client(socket, pos[0], pos[1], mapid);
				} else {
					/* Teleport to linked map. */
					nextmap(maps[mapid].objectdata.at(id).first, socket);
					process_updates(mapid, true);
				}
				return false;
				break;
			}
			case 3: { /* Area trigger */
				if(clients[socket].ontile != o){
					clients[socket].ontile = o;
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
						std::vector<uint8_t> updatedata(&maps[mapid].bytes[o], &maps[mapid].bytes[o+19]);
						maps[mapid].objupd_q.push_back({updatedata});
						bypass = true;
					}
				}
				break;
			}
			case 4: { /* Button */
				if(click){
					uint32_t color; /* Color of the button */
					memcpy(&color, &maps[mapid].bytes[o+15], 4);
					if(color == 0)
						break;
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
						std::vector<uint8_t> updatedata(&maps[mapid].bytes[o], &maps[mapid].bytes[o+19]);
						maps[mapid].objupd_q.push_back({updatedata});
						bypass = true;
					}
					activebuttons[o] = {std::chrono::steady_clock::now(), mapid};
				}
				break;
			}
		}
	} catch(const std::out_of_range) { }
	/* If bypass was already set to true, don't set it to false */
	if(o != clients[socket].ontile)
		bypass = updatetile(socket/*, o*/) ? true : bypass ? true : false;
	clients[socket].ontile = o;
	clients[socket].x = x;
	clients[socket].y = y;
	if(click)
		maps[mapid].click_q.push_back({x, y});
	process_updates(mapid, bypass);
	return true;
}

void cursorsio::server::updateplayercount(){
	for(auto& map : maps){
		map.updplayercount = true;
	}
}

void cursorsio::server::nextmap(uint32_t mapid, uWS::WebSocket socket){
	try {
		maps.at(mapid);
		clients.at(socket);
	} catch(const std::out_of_range) { return; }
	if(clients[socket].ontile != 0 && updatetile(socket))
			process_updates(clients[socket].mapid, true);
	uint16_t pos[2];
	memcpy(&pos, &maps[mapid].bytes[1], 4);
	clients[socket].x = pos[0];
	clients[socket].y = pos[1];
	clients[socket].mapid = mapid;
	
	socket.send((char*)(&maps[mapid].bytes[0]), maps[mapid].bytes.size(), uWS::BINARY);
	sendmapstate(socket);
	process_updates(mapid, mapid!=0);
}

bool cursorsio::server::updatetile(uWS::WebSocket socket/*, uint16_t newtile*/){
	const uint8_t mapid = clients[socket].mapid;
	try {
		switch((uint8_t)maps[mapid].bytes.at(clients[socket].ontile+4)){
			/*case 1: {
				if(maps[mapid].objectdata[clients[socket].ontile].second != 0){
					
				}
			}*/
			case 3: {
				/*if(newtile > 1 && (uint8_t)maps[mapid].bytes.at(newtile+4) == 1 && maps[mapid].objectdata[newtile].second == clients[socket].ontile){
					std::cout << "overlap" << std::endl;
					return false;
				}*/
				uint32_t id;
				memcpy(&id, &maps[mapid].bytes[clients[socket].ontile], 4);
				uint16_t count;
				memcpy(&count, &maps[mapid].bytes[clients[socket].ontile+13], 2);
				if(maps[mapid].objectdata[id].second > 0){
					maps[mapid].objectdata[id].second--;
				}
				uint16_t newcount = maps[mapid].objectdata[id].second >= maps[mapid].objectdata[id].first ? 0 : maps[mapid].objectdata[id].first - maps[mapid].objectdata[id].second;
				if(newcount != count){
					maps[mapid].bytes[clients[socket].ontile+13] = newcount;
					if(count == 0){
						uint32_t color;
						memcpy(&color, &maps[mapid].bytes[clients[socket].ontile+15], 4);
						for(auto& door : maps[mapid].doors[color]){
							maps[mapid].openeddoors.erase(door.id);
							std::vector<uint8_t> updatedata(&maps[mapid].bytes[door.pos], &maps[mapid].bytes[door.pos+17]);
							maps[mapid].objupd_q.push_back({updatedata});
						}
					}
					std::vector<uint8_t> updatedata(&maps[mapid].bytes[clients[socket].ontile], &maps[mapid].bytes[clients[socket].ontile+19]);
					maps[mapid].objupd_q.push_back({updatedata});
				}
				return true;
			}
		}
	} catch(const std::out_of_range) { }
	return false;
}

void cursorsio::server::sendmapstate(uWS::WebSocket socket){
	const uint32_t mapid = clients[socket].mapid;
	std::vector<uint8_t> bytes = {STYPE_MAP_UPDATE};

	uint16_t updates = 0;
	std::vector<uint8_t> updatedata;
	addtoarr(updates, bytes);
	addtoarr(updates, bytes);
	
	for(auto& door : maps[mapid].openeddoors){
		addtoarr(door, updatedata);
		updates++;
	}
	addtoarr(updates, bytes);
	bytes.insert(bytes.end(), &updatedata[0], &updatedata[updatedata.size()]);
	updatedata.clear();
	updates = 0;

	addtoarr(updates, bytes);
	addtoarr(updates, bytes); // Skip everything but removed walls
	
	socket.send((char*)(&bytes[0]), bytes.size(), uWS::BINARY);
}


void cursorsio::server::watch_timer(uv_timer_t *t){
	cursorsio::server *s = (cursorsio::server *) t->data;
	auto now = std::chrono::steady_clock::now();
        /* TODO: Make it less horrible, and fix the buttons getting stuck */
	std::set<uint32_t> mapstoupdate;
	for(auto b = s->activebuttons.cbegin(); b != s->activebuttons.cend();){
		if(std::chrono::duration_cast<std::chrono::milliseconds>(now - (*b).second.first).count() > 2000){
			uint16_t o = (*b).first;
			uint32_t id;
			memcpy(&id, &s->maps[(*b).second.second].bytes.at(o), 4);
			uint32_t maxcount = s->maps[(*b).second.second].objectdata[id].first;
			uint16_t count;
			memcpy(&count, &s->maps[(*b).second.second].bytes[o+13], 2);
			if(count == 0){
				uint32_t color;
				memcpy(&color, &s->maps[(*b).second.second].bytes[o+15], 4);
				for(auto& door : s->maps[(*b).second.second].doors[color]){
					s->maps[(*b).second.second].openeddoors.erase(door.id);
					std::vector<uint8_t> n(&s->maps[(*b).second.second].bytes[door.pos], &s->maps[(*b).second.second].bytes[door.pos+17]);
					s->maps[(*b).second.second].objupd_q.push_back({n});
				}
			}
			count++;
			s->maps[(*b).second.second].bytes[o+13] = count;
			std::vector<uint8_t> n(&s->maps[(*b).second.second].bytes[o], &s->maps[(*b).second.second].bytes[o+19]);
			s->maps[(*b).second.second].objupd_q.push_back({n});
			mapstoupdate.emplace((*b).second.second);
			if(count >= (maxcount & 0xFFFF)){
				s->activebuttons.erase(b++);
				continue;
			}
		}
		b++;
	}
	for(auto& mapid : mapstoupdate){
		s->process_updates(mapid, true);
	}
}

int main(int argc, char *argv[]){
	if(argc > 2){
		cursorsio::server sv(std::stoul(argv[2]));
		sv.run(argv[1], argc>3?std::stoul(argv[3]):1);
	} else {
		std::cout << "Usage: " << argv[0] << " MAP_FILE PORT [THREADS 1-255]" << std::endl;
	}
	return 0;
}
