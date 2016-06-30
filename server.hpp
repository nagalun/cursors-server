#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include <unordered_map>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> wsserver;

using websocketpp::lib::bind;

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

struct line_t {
	uint16_t x;
	uint16_t y;
	uint16_t x2;
	uint16_t y2;
};

struct click_t {
	uint16_t x;
	uint16_t y;
};

struct clqueue_t {
	std::vector<click_t> queue;
};

struct drqueue_t {
	std::vector<line_t> queue;
};

struct mapobj_active_t {
	uint16_t count;
	uint16_t maxcount;
	uint32_t linkedid;
};

struct mapobj_wall_t {
	uint16_t x;
	uint16_t y;
	uint16_t w; // width
	uint16_t h; // height
	uint32_t color;
	bool removed;
};

struct mapprop_t {
	drqueue_t draw_q;
	clqueue_t click_q;
	std::unordered_map<uint32_t, mapobj_wall_t> walls;
	std::unordered_map<uint32_t, mapobj_active_t> buttons;
	std::unordered_map<uint32_t, mapobj_active_t> areas;
	std::array<uint16_t, 2> startpoint;
	std::vector<uint8_t> bytes;
	bool updated;
};

struct cursor_t {
	uint32_t id;
	uint16_t x;
	uint16_t y;
	uint32_t mapid;
	bool correct;
};

union uint16_converter {
	uint16_t i;
	uint8_t  c[2];
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
			
			void start(uint16_t port, const std::string & mapdata);
			
			void on_open(wsserver* s, websocketpp::connection_hdl hdl);
			void on_fail(wsserver* s, websocketpp::connection_hdl hdl);
			void on_close(wsserver* s, websocketpp::connection_hdl hdl);
			void on_message(wsserver* s, websocketpp::connection_hdl hdl, wsserver::message_ptr msg);
			
			void process_updates(wsserver* s, mapprop_t *map, uint32_t mapid);
			
			void teleport_client(wsserver* s, websocketpp::connection_hdl hdl, uint16_t x, uint16_t y, uint32_t G);
			
			void free_id(uint32_t id){ freed_ids.push(id); };
			uint32_t get_id(){
				if(!freed_ids.empty()){
					uint32_t id = freed_ids.front();
					freed_ids.pop();
					return id;
				}
				return used_ids++;
			};
		private:
			std::map<websocketpp::connection_hdl, cursor_t, std::owner_less<websocketpp::connection_hdl>> clients;
			wsserver s;
			
			std::vector<mapprop_t> maps;
			std::mutex conn_mmtx;
			
			bool playerCountChanged = false;
			
			uint32_t used_ids = 0;
			std::queue<uint32_t> freed_ids;
	};
}

template <typename IntType>
IntType bitsToInt(IntType& result, const unsigned char* bits, unsigned int& offset, bool little_endian = true){
	result = 0;
	if (little_endian)
		for (int n = sizeof(result) + offset; n >= offset; n--)
			result = (result << 8) +bits[n];
	else
		for (unsigned n = offset; n < sizeof(result) + offset; n++)
			result = (result << 8) +bits[n];
	offset += sizeof(result);
	return result;
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
