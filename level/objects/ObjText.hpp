#pragma once
#include <cstdint>
#include <string>

#include "../LevelObject.hpp"

class ObjText : public LevelObject {
public:
	std::string string;
	bool centered;
	std::uint8_t textsize;

	ObjText(std::uint16_t x, std::uint16_t y, std::uint8_t textsize,
	        bool centered, const std::string& str);

	void serialize(std::uint8_t * arr) override;
	std::size_t netsize() override; /* 6 + str.size() */
};
