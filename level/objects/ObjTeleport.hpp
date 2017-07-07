#pragma once
#include <stdint.h>

#include "../LevelObject.hpp"
#include "../../types.hpp"

class Level;
class Cursor;

class ObjTeleport : public LevelObject {
	enum class Color : uint8_t { GREEN, RED, BLUE };
public:
	Level * target_lvl;
	point_t target_pos;

	ObjTeleport::Color appearance;

	ObjTeleport(uint16_t x, uint16_t y, /* Respawn (red area) */
	            uint16_t w, uint16_t h);

	ObjTeleport(Level * target, uint16_t x, uint16_t y, /* Change level (green area) */
	            uint16_t w, uint16_t h);

	ObjTeleport(point_t target, uint16_t x, uint16_t y, /* Teleport to pos (blue area) */
	            uint16_t w, uint16_t h);

	bool hover(Cursor * const) override;

	void serialize(uint8_t * arr) override;
	size_t netsize() override; /* 7 */
};
