#pragma once
#include <cstdint>
#include <unordered_set>
#include <vector>

#include "../LevelObject.hpp"

class Cursor;

class ObjAreaCounter : public LevelObject {
public:
	std::uint16_t count;
	std::uint16_t maxcount;
	std::uint32_t color;
	std::unordered_set<Cursor *> onarea;
	std::vector<LevelObject *> links;

	ObjAreaCounter(std::vector<LevelObject *>&,
	               std::uint16_t x, std::uint16_t y,
	               std::uint16_t w, std::uint16_t h,
	               std::uint16_t count, std::uint32_t color);

	bool recount();

	bool hover(Cursor * const) override;
	bool player_left(Cursor * const) override;
	
	bool tick() override;
	void reset() override;

	void serialize(std::uint8_t * arr) override;
	std::size_t netsize() override; /* 19 */
};
