#include "ObjText.hpp"

#include "../../types.hpp"

#include <cstring>

ObjText::ObjText(uint16_t x, uint16_t y, uint8_t textsize,
	        bool centered, const std::string& str)
: LevelObject(x, y, 0, 0, ObjectType::TEXT),
  string(str),
  centered(centered),
  textsize(textsize) { }

void ObjText::serialize(uint8_t * arr) {
	*(uint32_t *)(arr)      = id;
	*(uint8_t  *)(arr + 4)  = (uint8_t) type;
	*(uint16_t *)(arr + 5)  = x;
	*(uint16_t *)(arr + 7)  = y;
	*(uint8_t  *)(arr + 9)  = textsize;
	*(uint8_t  *)(arr + 10) = centered ? 1 : 0;
	const char * cstr = string.c_str();
	std::memcpy(arr + 11, cstr, string.size() + 1); /* null byte */
}

size_t ObjText::netsize() {
	return sizeof(uint32_t) + sizeof(uint8_t) * 3 + sizeof(uint16_t) * 2 + string.size() + 1;
}
