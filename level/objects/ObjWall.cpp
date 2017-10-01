#include "ObjWall.hpp"

#include "../../types.hpp"

ObjWall::ObjWall(std::uint16_t x, std::uint16_t y, std::uint16_t w, std::uint16_t h, std::uint32_t color)
: LevelObject(x, y, w, h, ObjectType::WALL),
  color(color) { }

void ObjWall::serialize(std::uint8_t * arr) {
	LevelObject::serialize(arr);
	std::size_t offs = LevelObject::netsize();
	*(std::uint32_t *)(arr + offs) = color;
}

size_t ObjWall::netsize() {
	return LevelObject::netsize() + sizeof(std::uint32_t);
}

