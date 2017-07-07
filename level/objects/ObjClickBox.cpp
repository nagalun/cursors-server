#include "ObjClickBox.hpp"

#include "../../types.hpp"
#include "../Level.hpp"

ObjClickBox::ObjClickBox(const std::vector<LevelObject*>& links, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t count, uint32_t count_speed_msec, uint32_t color)
: LevelObject(x, y, w, h, ObjectType::BUTTON),
  count(count),
  maxcount(count),
  count_speed_msec(count_speed_msec),
  color(color),
  lastclicktime(0),
  links(links) { }

bool ObjClickBox::click() {
	bool upd = false;
	if(count > 0) {
		--count;
		upd = true;
	}

	if(count == 0) {
		lastclicktime = lvl->get_time() + count_speed_msec * 2;
		if (upd) {
			for(auto obj : links) {
				obj->remove();
			}
		}
	}
	return upd;
}

bool ObjClickBox::tick() {
	uint32_t t = lvl->get_time();
	int32_t diff = (int32_t)t - lastclicktime;
	diff /= (int32_t)count_speed_msec;
	if(diff > 0 && count < maxcount) {
		if(count == 0) {
			for(auto obj : links) {
				obj->insert();
			}
		}
		count += diff;
		count = count >= maxcount ? maxcount : count;
		lastclicktime += diff * count_speed_msec;
		return true;
	} else if(count >= maxcount) {
		lastclicktime = t;
	}
	return false;
}

void ObjClickBox::reset() {
	if(count == 0) {
		for(auto obj : links) {
			obj->insert();
		}
	}
	count = maxcount;
	lastclicktime = 0;
}

void ObjClickBox::serialize(uint8_t * arr) {
	LevelObject::serialize(arr);
	size_t offs = LevelObject::netsize();
	*(uint16_t *)(arr + offs) = count;
	*(uint32_t *)(arr + offs + 2) = color;
}

size_t ObjClickBox::netsize() {
	return LevelObject::netsize() + sizeof(uint16_t) + sizeof(uint32_t);
}

