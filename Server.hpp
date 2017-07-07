#pragma once
#include <stdint.h>

#include <uWS.h>

#include "types.hpp"
#include "misc/IDSys.hpp"

extern uint32_t playercount;

class Server {
	uWS::Hub h;
	IDSys idsys;
	const uint16_t port;

public:
	Server(const uint16_t port);
	void run();
};

