#include "Server.hpp"
#include "Cursor.hpp"

#include <iostream>

#ifdef UWS_UDS
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include "level/LevelManager.hpp"

/* Damn */
uint32_t playercount = 0;

std::string getSocketIp(uS::Socket * s, uWS::HttpRequest req) {
	auto addr = s->getAddress();
	switch (addr.family[3]) {
		case '6':
		case '4':
			return addr.address;
			break;

#ifdef UWS_UDS
		case 'X': {
			uWS::Header h = req.getHeader("x-real-ip", 9);
			return h ? h.toString() : "";
		} break;
#endif
	}

	return "";
}

Server::Server(std::string addr, const std::uint16_t port)
	: h(uWS::NO_DELAY, true, 9),
	  addr(std::move(addr)),
	  port(port) {
	h.onConnection([this](uWS::WebSocket<uWS::SERVER> * socket, uWS::HttpRequest req) {
		const std::uint32_t id = idsys.getId();
		auto info = getSocketIp(socket, req);
		Cursor * const player = new Cursor(id, socket);
		socket->setUserData(player);
		if (player == nullptr) {
			std::cerr << "Couldn't allocate memory for new player" << std::endl;
			idsys.freeId(id);
			socket->close();
			return;
		}
		std::cout << "[" << id << "/" << info << "]: New client" << std::endl;
		++playercount;
		player->set_lvl(LevelManager::GetLevel(0));
	});
	
	h.onDisconnection([this](uWS::WebSocket<uWS::SERVER> * socket, int c, const char * msg, std::size_t len) {
		Cursor * const player = (Cursor *) socket->getUserData();
		if (player) {
			--playercount;
			idsys.freeId(player->id);
			player->set_lvl(nullptr);
			delete player;
		}
	});
	
	h.onMessage([this](uWS::WebSocket<uWS::SERVER> * socket, const char * msg, std::size_t len, uWS::OpCode oc) {
		Cursor * const player = (Cursor *) socket->getUserData();
		if (oc == uWS::OpCode::BINARY && len == 9 && player->canReceive()) {
			const packet_t data = *((packet_t *)(msg + 1));
			switch ((ClientMsg)msg[0]) {
			case ClientMsg::MOVE:
				player->move(data);
				break;
				
			case ClientMsg::CLICK:
				player->click(data);
				break;
				
			case ClientMsg::DRAW:
				player->draw(data);
				break;
			}
		} else {
			socket->close();
		}
	});

	h.getDefaultGroup<uWS::SERVER>().startAutoPing(2500);
}

void Server::run() {
	puts("Starting server...");
	LevelManager::initialize_levels(h.getLoop());

#ifdef UWS_UDS
	auto m = umask(0);
#endif

	if (!h.listen(addr.c_str(), port)) {
		std::cerr << "Couldn't listen on: " << addr << ':' << port << std::endl;
		return;
	}

#ifdef UWS_UDS
	umask(m);
#endif

	std::cout << "Listening on: " << addr << ':' << port << std::endl;
	h.run();
}
