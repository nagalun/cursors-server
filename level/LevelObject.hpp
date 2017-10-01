#pragma once
#include <cstdint>
#include <cstddef>

#include "../types.hpp"

class Level;
class Cursor;

class LevelObject {
public:
	Level * lvl;
	std::uint32_t id;
	/* To prevent the bug when multiple objects remove/add this object from the level. */
	std::uint32_t opened_counter;
	std::uint16_t x;
	std::uint16_t y;
	std::uint16_t w;
	std::uint16_t h;
	ObjectType type;

	LevelObject(std::uint16_t x, std::uint16_t y, std::uint16_t w, std::uint16_t h, ObjectType type);
	virtual ~LevelObject();

	void set_lvl(Level * lvl);
	virtual void remove();
	virtual void insert();

	virtual bool click();
	virtual bool hover(Cursor * const);
	virtual bool player_left(Cursor * const);

	virtual bool tick();
	virtual void reset();

	virtual void serialize(std::uint8_t * arr);
	virtual std::size_t netsize(); /* 13 */
};
