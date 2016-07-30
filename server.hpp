#include <iostream>
#include <string>
#include <memory.h>
#include <unordered_map>
#include <set>
#include <chrono>

#include <uWS.h>

enum client_messages : uint8_t {
	CTYPE_MOVE = 1,
	CTYPE_CLICK,
	CTYPE_DRAW
};

enum server_messages : uint8_t {
	STYPE_SET_CLIENT_ID,
	STYPE_MAP_UPDATE,
	STYPE_MAP_CHANGE = 4,
	STYPE_TELEPORT_CLIENT
};

union uint16_converter {
	uint16_t i;
	uint8_t c[2];
};

union uint32_converter {
	uint32_t i;
	uint8_t c[4];
};

template <typename IntType>
void addtoarr(IntType& number, std::vector<uint8_t>& bytes){
	switch(sizeof(number)){
		case 1:
			bytes.emplace_back(number);
			break;
		case 2: {
			uint16_converter t;
			t.i = number;
			bytes.insert(bytes.end(), &t.c[0], &t.c[sizeof(t.i)]);
			break;
		}
		case 4: {
			uint32_converter t;
			t.i = number;
			bytes.insert(bytes.end(), &t.c[0], &t.c[sizeof(t.i)]);
		}
			
	}
}

struct cursor_t {
	uint32_t id;
	uint16_t x;
	uint16_t y;
	uint32_t mapid;
	uint32_t ontile;
};

struct click_t {
	uint16_t x;
	uint16_t y;
};

struct line_t {
	uint16_t x;
	uint16_t y;
	uint16_t x2;
	uint16_t y2;
};

struct map_door_t {
	uint32_t id;
	uint32_t pos;
};

struct mapprop_t {
	std::vector<line_t> draw_q;
	std::vector<click_t> click_q;
	std::vector<std::vector<uint8_t>> objupd_q;
	std::vector<uint32_t> removed_q;
	std::set<uint32_t> openeddoors;
	std::unordered_map<uint32_t, std::pair<uint32_t, uint16_t>> objectdata;
	std::unordered_map<uint32_t, std::vector<map_door_t>> doors;
	std::array<uint16_t, (400 * 300)> map;
	std::vector<uint8_t> bytes;
	std::chrono::high_resolution_clock::time_point updatetime;
	bool updplayercount;
	bool lastcwasupdate;
};

namespace cursorsio {
	class server {
		public:
			server(uint16_t p){
				port = p;
			}
			void register_events(uWS::Server &server);
			void run(const std::string &mapfile, uint8_t threads);
			void updateplayercount();
			static void watch_timer(uv_timer_t *t);
			
			void nextmap(uint32_t mapid, uWS::WebSocket socket);
			void teleport_client(uWS::WebSocket socket, uint16_t x, uint16_t y, uint32_t G);
			void process_updates(uint32_t mapid, bool bypass = false);
			void sendmapstate(uWS::WebSocket socket);
			bool checkpos(uint16_t &x, uint16_t &y, uWS::WebSocket &socket, bool click = false);
			void kick(uWS::WebSocket &socket, bool close = false);
			
			uint32_t getid(){ return usedids++; };
		private:
			uint16_t port;
			std::unordered_map<uWS::WebSocket, cursor_t> clients;
			std::vector<mapprop_t> maps;
			
			uint32_t usedids = 2;
			
			std::unordered_map<uint32_t, std::pair<std::chrono::steady_clock::time_point, uint32_t>> activebuttons;
			uv_timer_t w_hdl;
	};
	class map {
		enum object_types : uint8_t {
			TEXT,
			WALL,
			EXIT,
			AREA_TRIGGER,
			BUTTON
		};
		public: 
			static std::vector<uint8_t> create_text(uint16_t x, uint16_t y,
								uint8_t size, bool centered, std::string string);
			
			static std::vector<uint8_t> create_wall(uint16_t x, uint16_t y,
								uint16_t width, uint16_t height,
								uint32_t color, uint32_t id = 0, bool isupdate = false);
			
			static std::vector<uint8_t> create_exit(uint16_t x, uint16_t y,
								uint16_t width, uint16_t height,
								bool isBad, uint32_t id = 0, bool isupdate = false);
			
			static std::vector<uint8_t> create_area(uint16_t x, uint16_t y,
								uint16_t width, uint16_t height,
								uint16_t count, uint32_t color,
								uint32_t id = 0, bool isupdate = false);
			
			static std::vector<uint8_t> create_button(uint16_t x, uint16_t y,
								  uint16_t width, uint16_t height,
								  uint16_t count, uint32_t color,
								  uint32_t id = 0, bool isupdate = false);
			
			static void parse(cursorsio::server *s, const std::string &mapdata, std::vector<mapprop_t> &maps);
	};
	/*class chat {
		public:
			static std::string handle_cmd(const std::string &msg, uWS::WebSocket socket)
	};*/
}
