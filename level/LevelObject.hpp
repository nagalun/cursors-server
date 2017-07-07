#pragma once
#include <stdint.h>
#include <cstddef>

#include "../types.hpp"

class Level;
class Cursor;

class LevelObject {
public:
	Level * lvl;
	uint32_t id;
	/* To prevent the bug when multiple objects remove/add this object from the level. */
	uint32_t opened_counter;
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	ObjectType type;

	LevelObject(uint16_t x, uint16_t y, uint16_t w, uint16_t h, ObjectType type);
	virtual ~LevelObject();

	void set_lvl(Level * lvl);
	virtual void remove();
	virtual void insert();

	virtual bool click();
	virtual bool hover(Cursor * const);
	virtual bool player_left(Cursor * const);

	virtual bool tick();
	virtual void reset();

	virtual void serialize(uint8_t * arr);
	virtual size_t netsize(); /* 13 */
};
