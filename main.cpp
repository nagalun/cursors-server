#include "Server.hpp"

int main() {
	Server srv(8080);
	srv.run();
	return 1;
}
