#pragma once
#include <cstdint>

#include "../LevelObject.hpp"
#include "../../types.hpp"

class Level;
class Cursor;

class ObjTeleport : public LevelObject {
	enum class Color : std::uint8_t { GREEN, RED, BLUE };
public:
	Level * target_lvl;
	point_t target_pos;

	ObjTeleport::Color appearance;

	ObjTeleport(std::uint16_t x, std::uint16_t y, /* Respawn (red area) */
	            std::uint16_t w, std::uint16_t h);

	ObjTeleport(Level * target, std::uint16_t x, std::uint16_t y, /* Change level (green area) */
	            std::uint16_t w, std::uint16_t h);

	ObjTeleport(point_t target, std::uint16_t x, std::uint16_t y, /* Teleport to pos (blue area) */
	            std::uint16_t w, std::uint16_t h);

	bool hover(Cursor * const) override;

	void serialize(std::uint8_t * arr) override;
	std::size_t netsize() override; /* 7 */
};
