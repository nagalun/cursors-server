#include "Server.hpp"
#include "Cursor.hpp"

#include "level/LevelManager.hpp"

/* Damn */
uint32_t playercount = 0;

Server::Server(const std::uint16_t port)
	: h(uWS::NO_DELAY, true, 9),
	  idsys(),
	  port(port) {
	h.onConnection([this](uWS::WebSocket<uWS::SERVER> * socket, uWS::HttpRequest req) {
		const std::uint32_t id = idsys.getId();
		Cursor * const player = new Cursor(id, socket);
		socket->setUserData(player);
		if (player == nullptr) {
			std::cerr << "Couldn't allocate memory for new player" << std::endl;
			idsys.freeId(id);
			socket->close();
			return;
		}
		printf("Got ID: %i\n", id);
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
		if (oc == uWS::OpCode::BINARY && len == 9) {
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
}

void Server::run() {
	puts("Starting server...");
	LevelManager::initialize_levels(h.getLoop());
	if (!h.listen(port)) {
		std::cerr << "Couldn't listen on port: " << port << std::endl;
	}
	h.run();
}
