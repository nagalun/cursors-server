#include "ObjVirus.hpp"

ObjVirus::ObjVirus(uint16_t x, uint16_t y)
: LevelObject(x, y, 0, 0, ObjectType::VIRUS) { }

void ObjVirus::serialize(uint8_t * arr) {
	*(uint32_t *)(arr)     = id;
	*(uint8_t  *)(arr + 4) = (uint8_t) type;
	*(uint16_t *)(arr + 5) = x;
	*(uint16_t *)(arr + 7) = y;
}

size_t ObjVirus::netsize() {
	return sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint16_t) * 2;
}
