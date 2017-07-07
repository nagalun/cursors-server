#pragma once
#include <stdint.h>

#include "../LevelObject.hpp"

class ObjWall : public LevelObject {
public:
	uint32_t color;

	ObjWall(uint16_t x, uint16_t y,
	        uint16_t w, uint16_t h, uint32_t color);

	void serialize(uint8_t * arr) override;
	size_t netsize() override; /* 19 */
};
