#pragma once
#include <cstdint>
#include <vector>

#include "ObjClickBox.hpp"

class LevelObject;

class ObjRainbowClickBox : public ObjClickBox {
public:
	ObjRainbowClickBox(const std::vector<LevelObject *>&,
	                   std::uint16_t x, std::uint16_t y,
	                   std::uint16_t w, std::uint16_t h,
	                   std::uint16_t count, std::uint32_t count_speed_msec);
	
	bool tick() override;
};
