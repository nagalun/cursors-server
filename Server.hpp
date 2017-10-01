#pragma once
#include <cstdint>

#include <uWS.h>

#include "types.hpp"
#include "misc/IdSys.hpp"

extern std::uint32_t playercount;

class Server {
	uWS::Hub h;
	IdSys idsys;
	const std::uint16_t port;

public:
	Server(const std::uint16_t port);
	void run();
};

