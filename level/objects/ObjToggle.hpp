#pragma once
#include <cstdint>
#include <vector>

#include "ObjClickBox.hpp"

class LevelObject;

class ObjToggle : public ObjClickBox {
public:
	bool default_state;
	
	ObjToggle(const std::vector<LevelObject *>&,
	          std::uint16_t x, std::uint16_t y,
	          std::uint16_t w, std::uint16_t h,
	          bool state);
	
	void remove() override;
	
	bool click() override;
	
	bool tick() override;
	void reset() override;
};
