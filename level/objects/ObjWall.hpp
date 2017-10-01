#pragma once
#include <cstdint>

#include "../LevelObject.hpp"

class ObjWall : public LevelObject {
public:
	std::uint32_t color;

	ObjWall(std::uint16_t x, std::uint16_t y,
	        std::uint16_t w, std::uint16_t h, std::uint32_t color);

	void serialize(std::uint8_t * arr) override;
	std::size_t netsize() override; /* 19 */
};
