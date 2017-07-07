#include "Cursor.hpp"

#include "level/Level.hpp"
#include "misc/Util.hpp"

#include <cstring>

Cursor::Cursor(const uint32_t id, uWS::WebSocket<uWS::SERVER> * ws)
: id(id),
  pos({0, 0}),
  sync(0),
  lvl(nullptr),
  ws(ws) {
	uint8_t msg[5] = {(uint8_t) ServerMsg::SET_CLIENT_ID};
	std::memcpy(&msg[1], (char *)&id, sizeof(uint32_t));
	ws->send((const char *)&msg[0], sizeof(msg), uWS::BINARY);
}

point_t Cursor::get_pos() const {
	return pos;
}

Level * const Cursor::get_lvl() const {
	return lvl;
}

void Cursor::set_lvl(Level * nlvl) {
	if (lvl != nullptr) {
		lvl->del_player(this);
	}
	lvl = nlvl;
	if (lvl != nullptr) {
		lvl->add_player(this);
		lvl->send_map(ws, ++sync);
	}
}

uWS::WebSocket<uWS::SERVER> * Cursor::get_ws() const {
	return ws;
};

void Cursor::resync() {
	++sync;
	uint8_t msg[9] = {(uint8_t) ServerMsg::TELEPORT_CLIENT};
	std::memcpy(&msg[1], (char *)&pos, sizeof(point_t));
	std::memcpy(&msg[5], (char *)&sync, sizeof(uint32_t));
	ws->send((const char *)&msg[0], sizeof(msg), uWS::BINARY);
}

void Cursor::tp(const point_t p) {
	move(p, false);
}

bool Cursor::move(const packet_t p) {
	if (p.other.sync >= sync && lvl != nullptr) {
		/* Collision checking goes here */
		const point_t new_pos = lvl->check_movement(pos, p.pos);

		pos = new_pos;
		lvl->moved(this);
		if (equal(&new_pos, &p.pos)) {
			return true;
		} else {
			resync();
		}
	}
	return false;
}

bool Cursor::move(const point_t p, bool check, bool syncpos) {
	if (check) {
		return move({p, sync});
	} else if (lvl) {
		pos = p;
		if (syncpos) {
			resync();
		}
		lvl->moved(this);
	}
	return false;
}

void Cursor::click(const packet_t p) {
	if (move(p)) {
		/* Queue the click for processing */
		lvl->click(p.pos);
	}
}

void Cursor::draw(const packet_t p) {
	if (!equal(&p.pos, &p.other.pos) && move(p.pos) && move(p.other.pos)) {
		lvl->draw({p.pos.x, p.pos.y, p.other.pos.x, p.other.pos.y});
	}
}

void Cursor::serialize(uint8_t * arr) {
	packet_player_t * str = (packet_player_t *)arr;
	str->id = id;
	str->pos = pos;
}

size_t Cursor::netsize() {
	/* ID, X, and Y. */
	return sizeof(uint32_t) + sizeof(uint16_t) * 2;
}
