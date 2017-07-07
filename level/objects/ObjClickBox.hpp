#pragma once
#include <stdint.h>
#include <vector>

#include "../LevelObject.hpp"

class ObjClickBox : public LevelObject {
public:
	uint16_t count;
	uint16_t maxcount;
	uint32_t count_speed_msec;
	uint32_t color;
	uint32_t lastclicktime;
	std::vector<LevelObject *> links;

	ObjClickBox(const std::vector<LevelObject *>&,
	            uint16_t x, uint16_t y,
	            uint16_t w, uint16_t h,
	            uint16_t count, uint32_t count_speed_msec,
	            uint32_t color);

	bool click() override;

	bool tick() override;
	void reset() override;

	void serialize(uint8_t * arr) override;
	size_t netsize() override; /* 19 */
};
