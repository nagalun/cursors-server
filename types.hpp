#pragma once
#include <stdint.h>

enum class ClientMsg : uint8_t {
	MOVE = 1,
	CLICK = 2,
	DRAW = 3
};

enum class ServerMsg : uint8_t {
	SET_CLIENT_ID = 0,
	MAP_UPDATE = 1,
	NEW_MAP = 4,
	TELEPORT_CLIENT = 5
};

enum class ObjectType : uint8_t {
	TEXT,
	WALL,
	TELEPORTER,
	AREACOUNTER,
	BUTTON,
	VIRUS
};

struct point_t {
	uint16_t x;
	uint16_t y;
};

struct line_t {
	uint16_t x;
	uint16_t y;
	uint16_t x2;
	uint16_t y2;
};

struct packet_player_t {
	uint32_t id;
	point_t pos;
};

struct box_t {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
};

union two_t {
	uint32_t sync;
	point_t pos;
};

struct packet_t {
	//ClientMsg type;
	point_t pos;
	two_t other;
};
