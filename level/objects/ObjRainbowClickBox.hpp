#pragma once
#include <stdint.h>
#include <vector>

#include "ObjClickBox.hpp"

class LevelObject;

class ObjRainbowClickBox : public ObjClickBox {
public:
	ObjRainbowClickBox(const std::vector<LevelObject *>&,
	                   uint16_t x, uint16_t y,
	                   uint16_t w, uint16_t h,
	                   uint16_t count, uint32_t count_speed_msec);
	
	bool tick() override;
};
