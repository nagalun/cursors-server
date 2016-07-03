#include "json.hpp"

#include "server.hpp"
#include "map.hpp"

std::vector<uint8_t> cursorsio::map::create_text(uint16_t x, uint16_t y,
						 uint8_t size, bool centered,
						 std::string string){
	std::vector<uint8_t> object = {TEXT};
	addtoarr(x, object);
	addtoarr(y, object);
	addtoarr(size, object);
	object.emplace_back(centered ? 1 : 0);
	for(int x = 0; x < string.length(); x++)
		object.emplace_back((uint8_t)string.c_str()[x]);
	object.emplace_back(0);
	return object;
}

std::vector<uint8_t> cursorsio::map::create_wall(uint16_t x, uint16_t y,
						 uint16_t width, uint16_t height,
						 uint32_t color, uint32_t id,
						 bool isupdate){
	std::vector<uint8_t> object;
	if(isupdate)
		addtoarr(id, object);
	object.push_back({WALL});
	addtoarr(x, object);
	addtoarr(y, object);
	addtoarr(width, object);
	addtoarr(height, object);
	addtoarr(color, object);
	return object;
}

std::vector<uint8_t> cursorsio::map::create_exit(uint16_t x, uint16_t y,
						 uint16_t width, uint16_t height,
						 bool isBad, uint32_t id,
						 bool isupdate){
	std::vector<uint8_t> object;
	if(isupdate)
		addtoarr(id, object);
	object.push_back({EXIT});
	addtoarr(x, object);
	addtoarr(y, object);
	addtoarr(width, object);
	addtoarr(height, object);
	object.emplace_back(isBad ? 1 : 0);
	return object;
}

std::vector<uint8_t> cursorsio::map::create_area(uint16_t x, uint16_t y,
						 uint16_t width, uint16_t height,
						 uint16_t count, uint32_t color,
						 uint32_t id, bool isupdate){
	std::vector<uint8_t> object;
	if(isupdate)
		addtoarr(id, object);
	object.push_back({AREA_TRIGGER});
	addtoarr(x, object);
	addtoarr(y, object);
	addtoarr(width, object);
	addtoarr(height, object);
	addtoarr(count, object);
	addtoarr(color, object);
	return object;
}

std::vector<uint8_t> cursorsio::map::create_button(uint16_t x, uint16_t y,
						   uint16_t width, uint16_t height,
						   uint16_t count, uint32_t color,
						   uint32_t id, bool isupdate){
	std::vector<uint8_t> object;
	if(isupdate)
		addtoarr(id, object);
	object.push_back({BUTTON});
	addtoarr(x, object);
	addtoarr(y, object);
	addtoarr(width, object);
	addtoarr(height, object);
	addtoarr(count, object);
	addtoarr(color, object);
	return object;
}

// this might change
void cursorsio::map::parse(cursorsio::server* s, const std::string & mapdata, std::vector<mapprop_t> & maps){
	nlohmann::json mapjson = nlohmann::json::parse(mapdata);
	for(auto& map : mapjson){
		mapprop_t newmap;
		newmap.bytes = {STYPE_MAP_CHANGE};
		uint16_t x = map["startpos"]["x"].get<uint16_t>();
		uint16_t y = map["startpos"]["y"].get<uint16_t>();
		addtoarr(x, newmap.bytes);
		addtoarr(y, newmap.bytes);
		uint16_t objectCount = map["objects"].size();
		addtoarr(objectCount, newmap.bytes);
		newmap.startpoint = { x, y };
		for(auto& object : map["objects"]){
			uint32_t id = s->get_id();
			addtoarr(id, newmap.bytes);
			std::string t = object["type"].get<std::string>();
			if(t == "text"){
				std::vector<uint8_t> b = cursorsio::map::create_text(object["x"].get<uint16_t>(),
										     object["y"].get<uint16_t>(),
										     object["size"].get<uint8_t>(),
										     object["centered"].get<bool>(),
										     object["string"].get<std::string>());
				newmap.bytes.insert(newmap.bytes.end(), &b[0], &b[b.size()]);
			} else if(t == "wall") {
				uint16_t x = object["x"].get<uint16_t>();
				uint16_t y = object["y"].get<uint16_t>();
				uint16_t w = object["w"].get<uint16_t>();
				uint16_t h = object["h"].get<uint16_t>();
				uint32_t color = std::stoul(object["color"].get<std::string>(), nullptr, 16);
				newmap.walls[id] = {x, y, w, h, color, false};
				std::vector<uint8_t> b = cursorsio::map::create_wall(x, y, w, h, color);
				newmap.bytes.insert(newmap.bytes.end(), &b[0], &b[b.size()]);
			} else if(t == "exit") {
				uint16_t x = object["x"].get<uint16_t>();
				uint16_t y = object["y"].get<uint16_t>();
				uint16_t w = object["w"].get<uint16_t>();
				uint16_t h = object["h"].get<uint16_t>();
				bool isbad = object["isbad"].get<bool>();
				newmap.exits[id] = {x, y, w, h, isbad};
				std::vector<uint8_t> b = cursorsio::map::create_exit(x, y, w, h, isbad);
				newmap.bytes.insert(newmap.bytes.end(), &b[0], &b[b.size()]);
			} else if(t == "button" || t == "area") {
				uint16_t x = object["x"].get<uint16_t>();
				uint16_t y = object["y"].get<uint16_t>();
				uint16_t w = object["w"].get<uint16_t>();
				uint16_t h = object["h"].get<uint16_t>();
				uint16_t count = object["count"].get<uint16_t>();
				uint32_t color = std::stoul(object["color"].get<std::string>(), nullptr, 16);
				std::vector<uint8_t> b;
				if(t == "button"){
					newmap.buttons[id].first = {x, y, w, h, count, count, color};
					b = cursorsio::map::create_button(x, y, w, h, count, color);
				} else {
					newmap.areas[id] = {x, y, w, h, count, count, color};
					b = cursorsio::map::create_area(x, y, w, h, count, color);
				}
				newmap.bytes.insert(newmap.bytes.end(), &b[0], &b[b.size()]);
			}
		}
		uint32_t newmapid = maps.size();
		addtoarr(newmapid, newmap.bytes);
		maps.push_back({newmap});
	}
}
