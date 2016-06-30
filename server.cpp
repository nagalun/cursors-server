#include <fstream>

#include "server.hpp"
#include "map.hpp"

/* Compile with:
 * g++ -std=gnu++0x server.cpp map.cpp -I./websocketpp/ -lboost_system -lboost_chrono -lboost_timer -lrt -lpthread -O2
 ***/

void cursorsio::server::start(uint16_t port, const std::string & mapdata){
	cursorsio::map::parse(this, mapdata, maps);
	uint32_t i = 0;
	for(auto& map : maps){
		std::cout << "Starting thread for map id: " << i << std::endl;
		websocketpp::lib::thread thr([this, i, &map]{cursorsio::server::process_updates(&s, &map, i);});
		thr.detach();
		i++;
	}
	s.clear_access_channels(websocketpp::log::alevel::all);
	s.set_access_channels(websocketpp::log::alevel::connect);
	s.set_access_channels(websocketpp::log::alevel::disconnect);
	s.set_access_channels(websocketpp::log::alevel::app);
	
	s.listen(boost::asio::ip::tcp::v4(), port);
	s.start_accept();
	s.run();
}

void cursorsio::server::on_open(wsserver* s, websocketpp::connection_hdl hdl) {
	std::vector<uint8_t> bytes = {STYPE_SET_CLIENT_ID};
	uint32_t newid = cursorsio::server::get_id();
	addtoarr(newid, bytes);
	conn_mmtx.lock();
	clients[hdl] = { newid, maps[0].startpoint[0], maps[0].startpoint[1], 0, true };
	playerCountChanged = true;
	conn_mmtx.unlock();
	s->send(hdl, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
	s->send(hdl, &maps[0].bytes[0], maps[0].bytes.size(), websocketpp::frame::opcode::binary);
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
		playerCountChanged = true;
	} catch(const std::out_of_range) { }
}

void cursorsio::server::on_close(wsserver* s, websocketpp::connection_hdl hdl) {
	conn_mmtx.lock();
	cursorsio::server::free_id(clients[hdl].id);
	clients.erase(hdl);
	conn_mmtx.unlock();
	playerCountChanged = true;
}

void cursorsio::server::on_message(wsserver* s, websocketpp::connection_hdl hdl, wsserver::message_ptr msg) {
	if (msg->get_opcode() == websocketpp::frame::opcode::binary && msg->get_payload().length() == 9) {
		try {
			clients.at(hdl);
		} catch(const std::out_of_range) {
			return;
		}
		const unsigned char *bytes = reinterpret_cast<const unsigned char *>(msg->get_payload().c_str());
		unsigned int o = 1;
		uint16_t u16;
		uint32_t u32;
		switch((uint8_t)msg->get_payload()[0]){
			case CTYPE_MOVE: {
				if(clients[hdl].correct){
					teleport_client(s, hdl, clients[hdl].x, clients[hdl].y, clients[hdl].mapid);
					clients[hdl].correct = false;
				} else {
					uint16_t x = bitsToInt<uint16_t>(u16, bytes, o);
					uint16_t y = bitsToInt<uint16_t>(u16, bytes, o);
					//TODO: detect_collisions(x, y, clients[hdl].mapid)
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
				//maps[clients[hdl].mapid].click_q.mtx.lock();
				maps[clients[hdl].mapid].click_q.queue.push_back({x, y});
				//maps[clients[hdl].mapid].click_q.mtx.unlock();
				//uint32_t G = bitsToInt<uint32_t>(u32, bytes, o);
				break;
			}
			case CTYPE_DRAW: {
				uint16_t x = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t y = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t x2 = bitsToInt<uint16_t>(u16, bytes, o);
				uint16_t y2 = bitsToInt<uint16_t>(u16, bytes, o);
				//maps[clients[hdl].mapid].draw_q.mtx.lock();
				maps[clients[hdl].mapid].draw_q.queue.push_back({x, y, x2, y2});
				//maps[clients[hdl].mapid].draw_q.mtx.unlock();
				// no locks, may be segfault prone?
				break;
			}
			default:
				s->get_alog().write(websocketpp::log::alevel::app,
					"Unknown msg received, closing connection for client id: " + std::to_string(clients[hdl].id));
				conn_mmtx.lock();
				cursorsio::server::free_id(clients[hdl].id);
				clients.erase(hdl);
				playerCountChanged = true;
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
		playerCountChanged = true;
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
			if(client.second.mapid == mapid && inThisMap < 100){
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
		uint16_t clickTimes = map->click_q.queue.size() & 0xFFFF;
		addtoarr((clickTimes < max_messages) ? clickTimes : max_messages, bytes);
		for(auto& click : map->click_q.queue){
			if(h < max_messages){
				addtoarr(click.x, bytes);
				addtoarr(click.y, bytes);
				h++;
			}
		}
		map->click_q.queue.clear();
		//map->click_q.mtx.unlock();

		h = 0;
		uint16_t wallsRemoved = 0;
		addtoarr(wallsRemoved, bytes); // Unimplemented

		uint16_t objectsUpdated = 0;
		addtoarr(objectsUpdated, bytes); // Unimplemented

		//map->draw_q.mtx.lock();
		uint16_t linesDrawed = map->draw_q.queue.size() & 0xFFFF;
		addtoarr((linesDrawed < max_messages) ? linesDrawed : max_messages, bytes);
		for(auto& line : map->draw_q.queue){
			if(h < max_messages){
				addtoarr(line.x, bytes);
				addtoarr(line.y, bytes);
				addtoarr(line.x2, bytes);
				addtoarr(line.y2, bytes);
				h++;
			}
		}
		map->draw_q.queue.clear();
		//map->draw_q.mtx.unlock();

		conn_mmtx.lock();
		if(playerCountChanged){
			uint32_t playerCount32 = clients.size();
			addtoarr(playerCount32, bytes); // Player count is uint32_t
		}

		if(linesDrawed > 0 || objectsUpdated > 0 || wallsRemoved > 0 || clickTimes > 0 || playerCountChanged || map->updated){
			for(auto& client : clhdl){
				s->send(client, &bytes[0], bytes.size(), websocketpp::frame::opcode::binary);
			}
		}
		if(playerCountChanged)
			playerCountChanged = false;
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


int main(int argc, char *argv[]) {
	cursorsio::server s;
	if(argc > 0){
		std::ifstream ifs(argv[1]);
		std::string mapdata( (std::istreambuf_iterator<char>(ifs) ),
				     (std::istreambuf_iterator<char>()    ) );
	s.start(9003, mapdata);
	}
}
