#pragma once
#include <cstdint>
#include <vector>

#include "../LevelObject.hpp"

class ObjClickBox : public LevelObject {
public:
	std::uint16_t count;
	std::uint16_t maxcount;
	std::uint32_t count_speed_msec;
	std::uint32_t color;
	std::uint32_t lastclicktime;
	std::vector<LevelObject *> links;

	ObjClickBox(const std::vector<LevelObject *>&,
	            std::uint16_t x, std::uint16_t y,
	            std::uint16_t w, std::uint16_t h,
	            std::uint16_t count, std::uint32_t count_speed_msec,
	            std::uint32_t color);

	bool click() override;

	bool tick() override;
	void reset() override;

	void serialize(std::uint8_t * arr) override;
	std::size_t netsize() override; /* 19 */
};
