#include "Util.hpp"
#include <queue>
#include <stdio.h>

/*template <typename E>
constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}*/

/* Checks if a point is inside of a box */
bool inside(point_t pos, box_t box) {
	return pos.x >= box.x         && pos.y >= box.y
	    && pos.x <  box.x + box.w && pos.y < box.y + box.h;
}

bool inside(box_t box1, box_t box2) {
	return !(box2.x > box1.x + box1.w
	    || box2.x + box2.w < box1.x
	    || box2.y > box1.y + box1.h
	    || box2.y + box2.h < box1.y);
}

bool equal(const point_t * pos1, const point_t * pos2) {
	std::uint32_t * p1 = (std::uint32_t *)pos1;
	std::uint32_t * p2 = (std::uint32_t *)pos2;
	return *p1 == *p2;
}

int32_t abs(const std::int32_t i) {
	return i < 0 ? -i : i;
}

/* Walk between two points in a straight line, checking for collisions */
point_t walk(point_t pos1, point_t pos2, std::uint8_t map[400 * 300]) {
	std::uint32_t * p1 = (std::uint32_t *)&pos1;
	std::uint32_t * p2 = (std::uint32_t *)&pos2;
	if(*p1 == *p2) { return pos2; }
	
	std::uint16_t x  = pos1.x;
	std::uint16_t y  = pos1.y;
	std::int32_t dx  =  abs(pos2.x - pos1.x);
	std::int32_t dy  = -abs(pos2.y - pos1.y);
	int8_t  sx  = pos1.x < pos2.x ? 1 : -1;
	int8_t  sy  = pos1.y < pos2.y ? 1 : -1;
	std::int32_t err = dx + dy;
	std::int32_t er2 = err * 2;

	while(*p1 != *p2) {
		if(er2 >= dy) {
			err += dy;
			x   += sx;
		}
		if(er2 <= dx) {
			err += dx;
			y   += sy;
		}
		if(x >= 400 || y >= 300 || map[y * 400 + x] & (1 << (std::uint8_t) ObjectType::WALL)) { break; }
		pos1.x = x;
		pos1.y = y;
		er2 = 2 * err;
	}
	return pos1;
}

point_t unstuck(point_t pos, std::uint8_t map[400 * 300]) {
	auto collides = [&map](std::uint16_t x, std::uint16_t y) -> bool {
		return map[y * 400 + x] & (1 << (std::uint8_t) ObjectType::WALL);
	};

	if(pos.x < 400 && pos.y < 300 && !collides(pos.x, pos.y)) {
		return pos;
	}

	std::uint8_t explored[400 * 300] = {};
	std::queue<point_t> queue;
	auto shouldqueue = [&explored](std::uint16_t x, std::uint16_t y) -> bool {
		if(x < 400 && y < 300 && !explored[y * 400 + x]) {
			explored[y * 400 + x] = 1;
			return true;
		}
		return false;
	};

	queue.push(pos);

	do {
		point_t p = queue.front();
		queue.pop();
		if(p.x < 400 && p.y < 300) {
			p.x -= 1;
			if(shouldqueue(p.x, p.y)) {
				if(!collides(p.x, p.y)) {
					return p;
				}
				queue.push(p);
			}
			p.x += 2;
			if(shouldqueue(p.x, p.y)) {
				if(!collides(p.x, p.y)) {
					return p;
				}
				queue.push(p);
			}
			p.x -= 1;
			p.y -= 1;
			if(shouldqueue(p.x, p.y)) {
				if(!collides(p.x, p.y)) {
					return p;
				}
				queue.push(p);
			}
			p.y += 2;
			if(shouldqueue(p.x, p.y)) {
				if(!collides(p.x, p.y)) {
					return p;
				}
				queue.push(p);
			}
		}
	} while(queue.size() != 0);
	return pos;
}
