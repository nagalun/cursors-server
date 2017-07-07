#include "ObjTeleport.hpp"

#include "../Level.hpp"
#include "../../Cursor.hpp"

ObjTeleport::ObjTeleport(uint16_t x, uint16_t y,
            uint16_t w, uint16_t h)
: LevelObject(x, y, w, h, ObjectType::TELEPORTER),
  target_lvl(nullptr),
  target_pos({0, 0}),
  appearance(ObjTeleport::Color::RED) { }

ObjTeleport::ObjTeleport(Level * target, uint16_t x, uint16_t y,
            uint16_t w, uint16_t h)
: LevelObject(x, y, w, h, ObjectType::TELEPORTER),
  target_lvl(target),
  target_pos(target ? target->get_spawnpoint() : (struct point_t){0, 0}), /* For stealth traps */
  appearance(ObjTeleport::Color::GREEN) { }

ObjTeleport::ObjTeleport(point_t target, uint16_t x, uint16_t y,
            uint16_t w, uint16_t h)
: LevelObject(x, y, w, h, ObjectType::TELEPORTER),
  target_lvl(nullptr),
  target_pos(target),
  appearance(ObjTeleport::Color::BLUE) { }

bool ObjTeleport::hover(Cursor * const cur) {
	if(target_lvl == nullptr) {
		switch(appearance) {
		case ObjTeleport::Color::GREEN: /* Stealth trap */
		case ObjTeleport::Color::RED:
			if(lvl != nullptr) {
				cur->tp(lvl->get_spawnpoint());
			}
			break;
		case ObjTeleport::Color::BLUE:
			cur->tp(target_pos);
			break;
		}
	} else { /* Level is linked */
		cur->set_lvl(target_lvl);
	}
	return false;
}

void ObjTeleport::serialize(uint8_t * arr) {
	LevelObject::serialize(arr);
	size_t offs = LevelObject::netsize();
	*(uint8_t *)(arr + offs) = (uint8_t) appearance;
}

size_t ObjTeleport::netsize() { /* 7 */
	return LevelObject::netsize() + sizeof(uint8_t);
}
