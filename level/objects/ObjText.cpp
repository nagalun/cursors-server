#include "ObjText.hpp"

#include "../../types.hpp"

#include <cstring>

ObjText::ObjText(std::uint16_t x, std::uint16_t y, std::uint8_t textsize,
	        bool centered, const std::string& str)
: LevelObject(x, y, 0, 0, ObjectType::TEXT),
  string(str),
  centered(centered),
  textsize(textsize) { }

void ObjText::serialize(std::uint8_t * arr) {
	*(std::uint32_t *)(arr)      = id;
	*(std::uint8_t  *)(arr + 4)  = (std::uint8_t) type;
	*(std::uint16_t *)(arr + 5)  = x;
	*(std::uint16_t *)(arr + 7)  = y;
	*(std::uint8_t  *)(arr + 9)  = textsize;
	*(std::uint8_t  *)(arr + 10) = centered ? 1 : 0;
	const char * cstr = string.c_str();
	std::memcpy(arr + 11, cstr, string.size() + 1); /* null byte */
}

size_t ObjText::netsize() {
	return sizeof(std::uint32_t) + sizeof(std::uint8_t) * 3 + sizeof(std::uint16_t) * 2 + string.size() + 1;
}
