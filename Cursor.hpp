#pragma once
#include <cstdint>

#include <uWS.h>

#include "types.hpp"

class Level;

class Cursor {
public:
	const std::uint32_t id;

private:
	point_t pos;
	std::uint32_t sync;
	Level * lvl;
	uWS::WebSocket<uWS::SERVER> * ws;

public:
	Cursor(const std::uint32_t id, uWS::WebSocket<uWS::SERVER> *);
	
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
	
	void serialize(std::uint8_t * arr);
	std::size_t netsize(); /* 8 */
};
