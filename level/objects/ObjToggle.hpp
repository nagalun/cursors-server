#pragma once
#include <stdint.h>
#include <vector>

#include "ObjClickBox.hpp"

class LevelObject;

class ObjToggle : public ObjClickBox {
public:
	bool default_state;
	
	ObjToggle(const std::vector<LevelObject *>&,
	          uint16_t x, uint16_t y,
	          uint16_t w, uint16_t h,
	          bool state);
	
	void remove() override;
	
	bool click() override;
	
	bool tick() override;
	void reset() override;
};
