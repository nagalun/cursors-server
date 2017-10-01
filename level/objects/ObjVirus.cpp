#include "ObjVirus.hpp"

ObjVirus::ObjVirus(std::uint16_t x, std::uint16_t y)
: LevelObject(x, y, 0, 0, ObjectType::VIRUS) { }

void ObjVirus::serialize(std::uint8_t * arr) {
	*(std::uint32_t *)(arr)     = id;
	*(std::uint8_t  *)(arr + 4) = (std::uint8_t) type;
	*(std::uint16_t *)(arr + 5) = x;
	*(std::uint16_t *)(arr + 7) = y;
}

size_t ObjVirus::netsize() {
	return sizeof(std::uint32_t) + sizeof(std::uint8_t) + sizeof(std::uint16_t) * 2;
}
