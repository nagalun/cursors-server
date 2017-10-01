#pragma once
#include <cstdint>

#include "../../types.hpp"
#include "../LevelObject.hpp"

class ObjVirus : public LevelObject {
public:
	/* incomplete */

	ObjVirus(std::uint16_t x, std::uint16_t y);

	// bool tick() override;

	void serialize(std::uint8_t * arr) override;
	std::size_t netsize() override; /* 9 */
};
