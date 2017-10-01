#include "ObjRainbowClickBox.hpp"

#include <cmath>

#include "../Level.hpp"

ObjRainbowClickBox::ObjRainbowClickBox(const std::vector<LevelObject*>& links, std::uint16_t x, std::uint16_t y, std::uint16_t w, std::uint16_t h, std::uint16_t count, std::uint32_t count_speed_msec)
: ObjClickBox(links, x, y, w, h, count, count_speed_msec, 0) { }

bool ObjRainbowClickBox::tick() {
	std::uint32_t t = lvl->get_time();
	std::uint8_t red = sin(0.02f * (t / 50) + 0) * 127 + 128;
	std::uint8_t green = sin(0.02f * (t / 50) + 2) * 127 + 128;
	std::uint8_t blue = sin(0.02f * (t / 50) + 4) * 127 + 128;

	std::uint32_t ncolor = red << 16 | green << 8 | blue;
	bool up = ncolor != color;

	if(up) {
		this->color = ncolor;
	}

	std::uint32_t curr_count_speed = (float)count_speed_msec * (1.0f / maxcount * (count + 1));
	std::int32_t diff = (std::int32_t)t - lastclicktime;
	diff /= (std::int32_t)curr_count_speed;
	if(diff > 0 && count < maxcount) {
		if(count == 0) {
			for(auto obj : links) {
				obj->insert();
			}
		}
		count += diff;
		count = count >= maxcount ? maxcount : count;
		lastclicktime += diff * curr_count_speed;
		return true;
	} else if(count >= maxcount) {
		lastclicktime = t;
	}
	return up;
}
