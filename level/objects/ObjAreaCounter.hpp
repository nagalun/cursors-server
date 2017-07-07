#pragma once
#include <stdint.h>
#include <unordered_set>
#include <vector>

#include "../LevelObject.hpp"

class Cursor;

class ObjAreaCounter : public LevelObject {
public:
	uint16_t count;
	uint16_t maxcount;
	uint32_t color;
	std::unordered_set<Cursor *> onarea;
	std::vector<LevelObject *> links;

	ObjAreaCounter(std::vector<LevelObject *>&,
	               uint16_t x, uint16_t y,
	               uint16_t w, uint16_t h,
	               uint16_t count, uint32_t color);

	bool recount();

	bool hover(Cursor * const) override;
	bool player_left(Cursor * const) override;
	
	bool tick() override;
	void reset() override;

	void serialize(uint8_t * arr) override;
	size_t netsize() override; /* 19 */
};
