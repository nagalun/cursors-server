#include "Level.hpp"
#include "LevelObject.hpp"
#include "../misc/Util.hpp"
#include "../Server.hpp" /* Extern playercount */
#include "../Cursor.hpp"
#include "LevelManager.hpp"

#include <cstdlib>
#include <cstring>

Level::Level(const std::uint16_t x, const std::uint16_t y)
: tick_timer(new Timer(LevelManager::get_loop())),
  time(0),
  sentplayercount(0),
  spawn({x, y}),
  lines(80),
  clicks(300),
  timer_active(false) {
	std::memset(&map, 0, sizeof(map));
	tick_timer->setData(this);
	/* TODO: Get max map size division for faster pathfinder,
	 * TODO: The map's bits should be more generic? (solid, click-able, hover-able, ...)
	 */
}

Level::~Level() {
	stop_ticking();
	tick_timer->close();
	for (auto obj : allobjects) {
		delete obj;
	}
}

void Level::RemoveObject(LevelObject * obj) {
	if (allobjects.erase(obj)) { /* If it did erase */
		obj_ids.freeId(obj->id);
		toupdate.erase(obj);
		objects[(std::uint8_t) obj->type].erase(obj);	
		objs_to_remove.emplace(obj->id);
		std::uint16_t x = obj->x;
		std::uint16_t y = obj->y;
		std::uint16_t w = obj->w;
		std::uint16_t h = obj->h;
		for (std::uint16_t ix = x; ix < x + w; ++ix) {
			for (std::uint16_t iy = y; iy < y + h; ++iy) {
				map[iy * 400 + ix] &= ~(1 << (std::uint8_t) obj->type);
			}
		}
		/* If another object of the same type was inside the removed object */
		for (auto obj2 : objects[(std::uint8_t) obj->type]) {
			std::uint16_t x2 = obj2->x;
			std::uint16_t y2 = obj2->y;
			std::uint16_t w2 = obj2->w;
			std::uint16_t h2 = obj2->h;
			if (inside({x,  y,  w,  h},
			           {x2, y2, w2, h2})) {
				for (std::uint16_t ix = x2; ix < x2 + w2; ++ix) {
					for (std::uint16_t iy = y2; iy < y2 + h2; ++iy) {
						map[iy * 400 + ix] |= 1 << (std::uint8_t) obj2->type;
					}
				}
			}
		}
	}
}

LevelObject * Level::AddObject(LevelObject * obj) {
	if (allobjects.emplace(obj).second) { /* If it was inserted (not already in set) */
		obj->set_lvl(this);
		obj->id = obj_ids.getId();
		objects[(std::uint8_t) obj->type].emplace(obj);
		std::uint16_t x = obj->x;
		std::uint16_t y = obj->y;
		std::uint16_t w = obj->w;
		std::uint16_t h = obj->h;
		for (std::uint16_t ix = x; ix < x + w; ++ix) {
			for (std::uint16_t iy = y; iy < y + h; ++iy) {
				/* Neat */
				map[iy * 400 + ix] |= 1 << (std::uint8_t) obj->type;
			}
		}
		if (obj->type == ObjectType::WALL) {
			for (auto player : players) {
				point_t p = player->get_pos();
				if (map[p.y * 400 + p.x] & (1 << (std::uint8_t) ObjectType::WALL)) {
					player->tp(unstuck(p, map));
				}
			}
		}
		obj->tick(); /* Hmm... */
		toupdate.emplace(obj);
	}
	return obj;
}

void Level::tick() {
	time += 50;

	point_t * click = clicks.get_data();
	std::size_t numclicks = clicks.get_items();

	line_t * line = lines.get_data();
	std::size_t numlines = lines.get_items();

	for (auto obj : allobjects) {
		if (obj->tick()) {
			toupdate.emplace(obj);
		}
	}

	for (std::size_t i = 0; i < numclicks; ++i) {
		std::uint8_t obj_clicked = map[click[i].y * 400 + click[i].x];
		if (obj_clicked) {
			/*for (std::uint8_t j = 0; j < 5; ++j) {*/ /* Fast way */
			if (obj_clicked & (1 << (std::uint8_t) ObjectType::BUTTON) /* (1 << j)*/) {
				for (auto obj : objects[(std::uint8_t) ObjectType::BUTTON]) {
					if (inside(click[i], {obj->x, obj->y, obj->w, obj->h})) {
						if (obj->click()) {
							toupdate.emplace(obj);
						}
					}
				}
			}
			/*}*/
		}
	}

	/* Tricky because players can get deleted from the set while iterating this */
	for (auto it = players_moved.begin(); it != players_moved.end();) {
		Cursor * const player = *it++;
		point_t pos = player->get_pos();
		std::uint8_t obj_hovered = map[pos.y * 400 + pos.x];
		if (obj_hovered) {
			/*for(std::uint8_t j = 0; j < 5; ++j) {*/ /* Fast way */
			if (obj_hovered & (1 << (std::uint8_t) ObjectType::AREACOUNTER) /*(1 << j)*/) {
				for (auto obj : objects[(std::uint8_t) ObjectType::AREACOUNTER /* j */]) {
					if (inside(pos, {obj->x, obj->y, obj->w, obj->h}) && obj->hover(player)) {
						toupdate.emplace(obj);
					}
				}
			}
			if (obj_hovered & (1 << (std::uint8_t) ObjectType::TELEPORTER)) {
				for (auto obj : objects[(std::uint8_t) ObjectType::TELEPORTER]) {
					if (inside(pos, {obj->x, obj->y, obj->w, obj->h})) {
						obj->hover(player);
					}
				}
			}
			/*}*/
		}
	}

	std::uint16_t nplayers = players.size();
	nplayers = nplayers >= 100 ? 100 : nplayers;
	std::uint16_t nclicks  = numclicks;
	std::uint16_t nremoves = objs_to_remove.size();
	std::uint16_t nupdates = toupdate.size();
	std::uint16_t nlines   = numlines;
	/* std::uint32_t totalplayers = playercount; */
	
	if (nplayers == 0) {
		stop_ticking();
		reset();
	} else if (sentplayercount != playercount || players_moved.size() || nclicks || nremoves || nupdates || nlines) {
		std::size_t finalsize = 1 + sizeof(std::uint16_t)
		                     + sizeof(std::uint16_t)
		                     + sizeof(std::uint16_t)
		                     + sizeof(std::uint16_t)
		                     + sizeof(std::uint16_t)
		                     + sizeof(std::uint32_t);
		finalsize += nplayers  * sizeof(packet_player_t);
		finalsize += numclicks * sizeof(point_t);
		finalsize += nremoves  * sizeof(std::uint32_t);
		for (auto obj : toupdate) {
			finalsize += obj->netsize();
		}
		finalsize += numlines * sizeof(line_t);
	
		std::size_t offset = 0;
		std::uint8_t * buf = (std::uint8_t *)malloc(finalsize);
	
		*(std::uint8_t  *)(buf + offset) = (std::uint8_t) ServerMsg::MAP_UPDATE;
		offset += sizeof(std::uint8_t);
		*(std::uint16_t *)(buf + offset) = nplayers;
		offset += sizeof(std::uint16_t);
	
		for (auto player : players) {
			player->serialize(buf + offset);
			offset += player->netsize();
			if (--nplayers == 0) {
				break;
			}
		}
	
		*(std::uint16_t *)(buf + offset) = nclicks;
		offset += sizeof(std::uint16_t);
	
		std::memcpy(buf + offset, click, nclicks * sizeof(point_t));
		offset += nclicks * sizeof(point_t);
	
		*(std::uint16_t *)(buf + offset) = nremoves;
		offset += sizeof(std::uint16_t);
	
		for (std::uint32_t id : objs_to_remove) {
			*(std::uint32_t *)(buf + offset) = id;
			offset += sizeof(std::uint32_t);
		}
	
		*(std::uint16_t *)(buf + offset) = nupdates;
		offset += sizeof(std::uint16_t);
	
		for (auto obj : toupdate) {
			obj->serialize(buf + offset);
			offset += obj->netsize();
		}
	
		*(std::uint16_t *)(buf + offset) = nlines;
		offset += sizeof(std::uint16_t);
	
		std::memcpy(buf + offset, line, numlines * sizeof(line_t));
		offset += numlines * sizeof(line_t);
	
		*(std::uint32_t *)(buf + offset) = playercount;

		for (auto player : players) {
			player->get_ws()->send((const char *)buf, finalsize, uWS::BINARY);
		}

		free(buf);
		players_moved.clear();
		sentplayercount = playercount;
	}

	clicks.clear();
	lines.clear();
	objs_to_remove.clear();
	toupdate.clear();
}

void Level::do_tick(Timer * const t) {
	Level * const lvl = (Level *)t->getData();
	lvl->tick();
}

void Level::start_ticking() {
	if (!timer_active) {
		timer_active = true;
		tick_timer->start(do_tick, 50, 50);
	}
}

void Level::stop_ticking() {
	if (timer_active) {
		timer_active = false;
		tick_timer->stop();
	}
}

void Level::moved(Cursor * cur) {
	players_moved.emplace(cur);
}

void Level::click(point_t pos) {
	clicks.insert(pos);
};

void Level::draw(line_t line) {
	if (players.size() <= 30) {
		lines.insert(line);
	}
};

point_t Level::check_movement(point_t start, point_t end) {
	start = walk(start, end, map);
	if (!equal(&start, &end) && end.x < 400 && end.y < 300) {
		// pathfinder goes here
		return end;
	}
	return start;
}

point_t Level::get_spawnpoint() const {
	return spawn;
}

uint32_t Level::get_time() const {
	return time;
}

void Level::add_player(Cursor * cur) {
	if (players.size() == 0) {
		start_ticking();
	}
	players.emplace(cur);
	cur->move(spawn, false, false);
}

void Level::del_player(Cursor * cur) {
	players.erase(cur);
	players_moved.erase(cur);
	for (auto obj : allobjects) {
		if (obj->player_left(cur)) {
			toupdate.emplace(obj);
		}
	}
	force_resend();
}

void Level::send_map(uWS::WebSocket<uWS::SERVER> * socket, const std::uint32_t sync) {
	std::size_t offs = 0;
	std::uint16_t numobjs = allobjects.size();
	std::size_t finalsize = 1 + sizeof(point_t)
	                     + sizeof(std::uint16_t)
	                     + sizeof(std::uint32_t);
	for (auto obj : allobjects) {
		finalsize += obj->netsize();
	}

	std::uint8_t * buf = (std::uint8_t *)malloc(finalsize);

	*(std::uint8_t  *)(buf + offs) = (std::uint8_t) ServerMsg::NEW_MAP;
	offs                     += sizeof(std::uint8_t);

	*(point_t  *)(buf + offs) = spawn;
	offs                     += sizeof(point_t);

	*(std::uint16_t *)(buf + offs) = numobjs;
	offs                     += sizeof(std::uint16_t);

	for (auto obj : allobjects) {
		obj->serialize(buf + offs);
		offs += obj->netsize();
	}

	*(std::uint32_t *)(buf + offs) = sync;

	socket->send((const char *)buf, finalsize, uWS::BINARY);
	free(buf);
}

void Level::force_resend() {
	sentplayercount = 0;
}

void Level::reset() {
	for (auto obj : allobjects) {
		obj->reset();
	}
}
