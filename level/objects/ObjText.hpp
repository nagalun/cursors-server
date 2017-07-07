#pragma once
#include <stdint.h>
#include <string>

#include "../LevelObject.hpp"

class ObjText : public LevelObject {
public:
	std::string string;
	bool centered;
	uint8_t textsize;

	ObjText(uint16_t x, uint16_t y, uint8_t textsize,
	        bool centered, const std::string& str);

	void serialize(uint8_t * arr) override;
	size_t netsize() override; /* 6 + str.size() */
};
