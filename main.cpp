#include "Server.hpp"

int main(int argc, char *argv[]){
	uint16_t port = 1235;
	std::string addr("0.0.0.0");
	if (argc >= 2) addr = argv[1];
	if (argc >= 3) port = std::stoul(argv[2]);

	Server s(addr, port);
	s.run();

	//std::cout << "Usage: " << argv[0] << " [LISTEN_ADDR{0.0.0.0}] [PORT {1235}]" << std::endl;

	return 1;
}
