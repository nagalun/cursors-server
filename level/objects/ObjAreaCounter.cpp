#include "ObjAreaCounter.hpp"

#include "../../types.hpp"
#include "../../Cursor.hpp"
#include "../../misc/Util.hpp"
#include "../Level.hpp"

ObjAreaCounter::ObjAreaCounter(std::vector<LevelObject*>& links, std::uint16_t x, std::uint16_t y, std::uint16_t w, std::uint16_t h, std::uint16_t count, std::uint32_t color)
: LevelObject(x, y, w, h, ObjectType::AREACOUNTER),
  count(count),
  maxcount(count),
  color(color),
  links(links) { }

bool ObjAreaCounter::recount() {
	std::int32_t newcount = maxcount - onarea.size();
	std::uint32_t oldcount = count;
	newcount = newcount <= 0 ? 0 : newcount;
	if(newcount != count){
		count = newcount;
		if(oldcount == 0) {
			for(auto obj : links) {
				obj->insert();
			}
		} else if(count == 0) {
			for(auto obj : links) {
				obj->remove();
			}
		}
		return true;
	}
	return false;
}

bool ObjAreaCounter::hover(Cursor * const cur) {
	if(onarea.emplace(cur).second) {
		return recount();
	}
	return false;
}

bool ObjAreaCounter::player_left(Cursor * const cur) {
	if(onarea.erase(cur)) {
		return recount();
	}
	return false;
}

bool ObjAreaCounter::tick() {
	bool updated = false;
	for(auto it = onarea.begin(); it != onarea.end();) {
		if(!inside((*it)->get_pos(), {this->x, this->y, this->w, this->h})) {
			onarea.erase(it++);
			updated = true;
		} else {
			++it;
		}
	}
	return updated ? recount() : false;
}

void ObjAreaCounter::reset() {
	onarea.clear();
	recount();
}

void ObjAreaCounter::serialize(std::uint8_t * arr) {
	LevelObject::serialize(arr);
	std::size_t offs = LevelObject::netsize();
	*(std::uint16_t *)(arr + offs) = count;
	*(std::uint32_t *)(arr + offs + 2) = color;
}

size_t ObjAreaCounter::netsize() { /* 19 */
	return LevelObject::netsize() + sizeof(std::uint16_t) + sizeof(std::uint32_t);
}

