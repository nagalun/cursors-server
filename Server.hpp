#pragma once
#include <cstdint>
#include <string>

#include <uWS.h>

#include "types.hpp"
#include "misc/IdSys.hpp"

extern std::uint32_t playercount;

class Server {
	uWS::Hub h;
	IdSys idsys;
	const std::string addr;
	const std::uint16_t port;

public:
	Server(std::string addr, const std::uint16_t port);
	void run();
};

