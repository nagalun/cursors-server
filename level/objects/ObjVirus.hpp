#pragma once
#include <stdint.h>

#include "../../types.hpp"
#include "../LevelObject.hpp"

class ObjVirus : public LevelObject {
public:
	/* incomplete */

	ObjVirus(uint16_t x, uint16_t y);

	// bool tick() override;

	void serialize(uint8_t * arr) override;
	size_t netsize() override; /* 9 */
};
