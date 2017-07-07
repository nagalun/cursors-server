#pragma once
#include <stdint.h>

#include <uWS.h>

#include "types.hpp"

class Level;

class Cursor {
public:
	const uint32_t id;

private:
	point_t pos;
	uint32_t sync;
	Level * lvl;
	uWS::WebSocket<uWS::SERVER> * ws;

public:
	Cursor(const uint32_t id, uWS::WebSocket<uWS::SERVER> *);
	
	point_t get_pos() const;
	uWS::WebSocket<uWS::SERVER> * get_ws() const;
	
	Level * const get_lvl() const;
	void set_lvl(Level *);
	
	void resync();
	void tp(const point_t);
	
	bool move(const packet_t);
	bool move(const point_t, bool check = true, bool syncpos = true);
	void click(const packet_t);
	void draw(const packet_t);
	
	void serialize(uint8_t * arr);
	size_t netsize(); /* 8 */
};
