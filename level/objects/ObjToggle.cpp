#include "ObjToggle.hpp"

#include "../Level.hpp"

ObjToggle::ObjToggle(const std::vector<LevelObject*>& links, std::uint16_t x, std::uint16_t y, std::uint16_t w, std::uint16_t h, bool state)
: ObjClickBox(links, x, y, w, h, state ? 1 : 0, 0, state ? 0x51cc00 : 0xe9686d),
  default_state(state) {
	if (!default_state) { /* This could be dangerous? */
		for(auto obj : links) {
			obj->remove();
		}
	}
}

void ObjToggle::remove() {
	ObjClickBox::remove();
	reset();
}

bool ObjToggle::click() {
	count = count ? 0 : 1;
	color = count ? 0x51cc00 : 0xe9686d;
	if(count == 0) {
		for(auto obj : links) {
			obj->remove();
		}
	} else {
		for(auto obj : links) {
			obj->insert();
		}
	}
	return true;
}

bool ObjToggle::tick() {
	return false;
}

void ObjToggle::reset() {
	std::uint8_t def_state = default_state ? 1 : 0;
	if (def_state != count) {
		click();
	}
}
