#include "server.hpp"

#include <fstream>
#include <math.h>

/*
 * Compile with:
 * g++ -std=c++11 -O3 -I uWebSockets/src uWebSockets/src/Extensions.cpp uWebSockets/src/HTTPSocket.cpp uWebSockets/src/Network.cpp uWebSockets/src/Server.cpp uWebSockets/src/UTF8.cpp uWebSockets/src/WebSocket.cpp server.cpp map.cpp -o uWS -luv -lcrypto -lssl -lz
 **/

void cursorsio::server::run(const std::string &mapfile, uint8_t threads){
	std::ifstream ifs;
	ifs.open(mapfile);
	{
	std::string mapdata((std::istreambuf_iterator<char>(ifs)),
			    (std::istreambuf_iterator<char>()));
	cursorsio::map::parse(this, mapdata, maps);
	}
	ifs.close();
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
		try {
			if(clients[socket].ontile != 0 && maps[mapid].bytes.at(clients[socket].ontile+4) == 3){
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
							std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + door.pos;
							std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + door.pos + 17;
							std::vector<uint8_t> n(f, l);
							maps[mapid].objupd_q.push_back({n});
						}
					}
					{
						std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + clients[socket].ontile;
						std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + clients[socket].ontile + 19;
						std::vector<uint8_t> n(f, l);
						maps[mapid].objupd_q.push_back({n});
					}
				}
			}
		} catch(const std::out_of_range) { }
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

void cursorsio::server::teleport_client(uWS::WebSocket socket, uint16_t x, uint16_t y, uint32_t G){
	//if(clients[hdl].stats.tps < 15){
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
	if(x > 400 || y > 300 || o == 1){
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

	try {
		try {
			/* Need to re-do this */
			if(o != clients[socket].ontile && maps[mapid].bytes.at(clients[socket].ontile+4) == 3){
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
							std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + door.pos;
							std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + door.pos + 17;
							std::vector<uint8_t> n(f, l);
							maps[mapid].objupd_q.push_back({n});
						}
					}
					{
						std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + clients[socket].ontile;
						std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + clients[socket].ontile + 19;
						std::vector<uint8_t> n(f, l);
						maps[mapid].objupd_q.push_back({n});
					}
					bypass = true;
				}
			}
		} catch(const std::out_of_range) { }
		if(o == 0) {
			clients[socket].ontile = 0;
			clients[socket].x = x;
			clients[socket].y = y;
			if(click)
				maps[mapid].click_q.push_back({x, y});
			process_updates(mapid);
			return true;
		}
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
						{
							std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + o;
							std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + o + 19;
							std::vector<uint8_t> n(f, l);
							maps[mapid].objupd_q.push_back({n});
						}
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
						{
							std::vector<uint8_t>::const_iterator f = maps[mapid].bytes.begin() + o;
							std::vector<uint8_t>::const_iterator l = maps[mapid].bytes.begin() + o + 19;
							std::vector<uint8_t> n(f, l);
							maps[mapid].objupd_q.push_back({n});
						}
						bypass = true;
					}
					activebuttons[o] = {std::chrono::steady_clock::now(), mapid};
				}
				break;
			}
		}
		clients[socket].ontile = o;
	} catch(const std::out_of_range) { }
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
	uint16_t pos[2];
	memcpy(&pos, &maps[mapid].bytes[1], 4);
	clients[socket].x = pos[0];
	clients[socket].y = pos[1];
	clients[socket].mapid = mapid;
	
	socket.send((char*)(&maps[mapid].bytes[0]), maps[mapid].bytes.size(), uWS::BINARY);
	sendmapstate(socket);
	process_updates(mapid, mapid!=0);
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
	/* TODO: Fix this so it sends all button updates in one process_updates per map? */
        /* Also make it less horrible */
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
					std::vector<uint8_t>::const_iterator f = s->maps[(*b).second.second].bytes.begin() + door.pos;
					std::vector<uint8_t>::const_iterator l = s->maps[(*b).second.second].bytes.begin() + door.pos + 17;
					std::vector<uint8_t> n(f, l);
					s->maps[(*b).second.second].objupd_q.push_back({n});
				}
			}
			count++;
			s->maps[(*b).second.second].bytes[o+13] = count;
			{
				std::vector<uint8_t>::const_iterator f = s->maps[(*b).second.second].bytes.begin() + o;
				std::vector<uint8_t>::const_iterator l = s->maps[(*b).second.second].bytes.begin() + o + 19;
				std::vector<uint8_t> n(f, l);
				s->maps[(*b).second.second].objupd_q.push_back({n});
			}
			s->process_updates((*b).second.second, true);
			if(count >= (maxcount & 0xFFFF)){
				s->activebuttons.erase(b++);
				continue;
			}
		}
		b++;
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
