#include "ObjWall.hpp"

#include "../../types.hpp"

ObjWall::ObjWall(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color)
: LevelObject(x, y, w, h, ObjectType::WALL),
  color(color) { }

void ObjWall::serialize(uint8_t * arr) {
	LevelObject::serialize(arr);
	size_t offs = LevelObject::netsize();
	*(uint32_t *)(arr + offs) = color;
}

size_t ObjWall::netsize() {
	return LevelObject::netsize() + sizeof(uint32_t);
}

