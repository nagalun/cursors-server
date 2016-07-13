#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <sys/time.h>

#include <websocketpp/common/asio.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> wsserver;

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

// map array contains position of the object in the bytes vector
// startpoint is fetched from the bytes vector
// exit data:
// [(linkedmap,linkedmap)]
// active buttons list, buttons below maxcount
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
	uint32_t updatetime;
	bool updplayercount;
	bool lastcwasupdate;
};

/* if player is in air, ontile will be 0.
 * if ontile changed, and it was not 0, update the tile if applicable.
 * TODO: add changedmap state?
 */
struct cursor_t {
	uint32_t id;
	uint16_t x;
	uint16_t y;
	uint32_t mapid;
	uint32_t ontile;
};

union uint16_converter {
	uint16_t i;
	uint8_t c[2];
};

union uint32_converter {
	uint32_t i;
	uint8_t c[4];
};

namespace cursorsio {
	class server {
		public:
			server(){
				s.init_asio();

				s.set_message_handler(bind(&cursorsio::server::on_message,this, &s,std::placeholders::_1,std::placeholders::_2));
				s.set_open_handler(bind(&cursorsio::server::on_open,this,&s,std::placeholders::_1));
				s.set_close_handler(bind(&cursorsio::server::on_close,this,&s,std::placeholders::_1));
				s.set_fail_handler(bind(&cursorsio::server::on_fail,this,&s,std::placeholders::_1));
			}
			
			void settimer();
			
			void start(uint16_t port, const std::string & mapdata);
			//void reload();
			
			void on_open(wsserver* s, websocketpp::connection_hdl hdl);
			void on_fail(wsserver* s, websocketpp::connection_hdl hdl);
			void on_close(wsserver* s, websocketpp::connection_hdl hdl);
			void on_message(wsserver* s, websocketpp::connection_hdl hdl, wsserver::message_ptr msg);
			
			void updateplayercount();
			void process_updates(wsserver* s, mapprop_t *map, uint32_t mapid, bool bypass = false);
			void watch_timer(websocketpp::lib::error_code const& ec);
			//void cmd_thread();
			
			void kick(websocketpp::connection_hdl hdl, bool close = true);
			void teleport_client(wsserver* s, websocketpp::connection_hdl hdl, uint16_t x, uint16_t y, uint32_t G);
			void nextmap(uint32_t mapid, websocketpp::connection_hdl hdl);
			void sendmapstate(uint32_t mapid, websocketpp::connection_hdl hdl);
			bool checkpos(uint16_t x, uint16_t y, uint32_t mapid, websocketpp::connection_hdl hdl, bool click);
			
			//void free_id(uint32_t id){ freed_ids.push(id); };
			uint32_t get_id(){
				/*if(!freed_ids.empty()){
					uint32_t id = freed_ids.front();
					freed_ids.pop();
					return id;
				}*/
				return used_ids++;
			};
		private:
			std::map<websocketpp::connection_hdl, cursor_t, std::owner_less<websocketpp::connection_hdl>> clients;
			wsserver s;
			wsserver::timer_ptr watchtimer;
			
			std::vector<mapprop_t> maps;
			std::string mapfile;
			
			std::unordered_map<uint32_t, std::pair<uint32_t, uint32_t>> activebuttons;
			
			// allocate internal id for air and normal wall
			uint32_t used_ids = 2;
			//std::queue<uint32_t> freed_ids;
			
			uint32_t defaultmap = 0;
	};
}

template <typename IntType>
IntType addtoarr(IntType& number, std::vector<uint8_t>& bytes){
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
