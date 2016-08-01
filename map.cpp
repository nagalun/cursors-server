#include "json.hpp"

#include "server.hpp"

std::vector<uint8_t> cursorsio::map::create_text(uint16_t x, uint16_t y,
						 uint8_t size, bool centered,
						 std::string string){
	std::vector<uint8_t> object = {TEXT};
	addtoarr(x, object);
	addtoarr(y, object);
	addtoarr(size, object);
	object.emplace_back(centered ? 1 : 0);
	for(uint32_t x = 0; x < string.length(); x++)
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
	std::map<std::string, uint32_t> links;
	uint32_t mapid = 0;
	for(auto& map : mapjson){
		if(map["tag"].is_string()){
			links[map["tag"].get<std::string>()] = mapid;
		}
		mapid++;
	}
	mapid = 0;
	for(auto& map : mapjson){
		mapprop_t newmap;
		newmap.bytes = {STYPE_MAP_CHANGE};
		for(uint32_t e = 0; e < newmap.map.size(); e++){
			newmap.map[e] = 0;
		}
		uint16_t x = map["startpos"]["x"].get<uint16_t>();
		uint16_t y = map["startpos"]["y"].get<uint16_t>();
		addtoarr(x, newmap.bytes);
		addtoarr(y, newmap.bytes);
		uint16_t objectCount = map["objects"].size();
		addtoarr(objectCount, newmap.bytes);
		for(auto& object : map["objects"]){
			uint32_t id = s->getid();
			uint32_t pos = newmap.bytes.size();
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
				/* Overlapping objects
				newmap.objectdata[pos].second = newmap.map[x + 400 * y];*/
				for(int g = y; g < y + h; g++){
					for(int i = x; i < x + w; i++){
						if(color == 0){
							newmap.map[i + 400 * g] = 1;
						} else {
							newmap.map[i + 400 * g] = pos;
						}
					}
				}
				newmap.doors[color].push_back({id, pos});
				std::vector<uint8_t> b = cursorsio::map::create_wall(x, y, w, h, color);
				newmap.bytes.insert(newmap.bytes.end(), &b[0], &b[b.size()]);
			} else if(t == "exit") {
				uint16_t x = object["x"].get<uint16_t>();
				uint16_t y = object["y"].get<uint16_t>();
				uint16_t w = object["w"].get<uint16_t>();
				uint16_t h = object["h"].get<uint16_t>();
				bool isbad = object["isbad"].get<bool>();
				int offset = 1;
				uint32_t linkto = maps.size();
				if(object["offset"].is_number()){
					offset = object["offset"].get<int>();
				}
				if(object["tag"].is_string()){
					std::string tag = object["tag"].get<std::string>();
					try {
						links.at(tag);
						linkto = links[tag];
						offset--;
					} catch(std::out_of_range) { }
				}
				linkto = linkto + offset;
				newmap.objectdata[id].first = linkto;
				for(int g = y; g < y + h; g++){
					for(int i = x; i < x + w; i++){
							newmap.map[i + 400 * g] = pos;
					}
				}
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
					b = cursorsio::map::create_button(x, y, w, h, count, color);
				} else {
					b = cursorsio::map::create_area(x, y, w, h, count, color);
					/*if(newmap.map[x + 400 * y] > 1 && newmap.bytes.at(newmap.map[x + 400 * y]+4) == 1){
						uint32_t id = 0;
						memcpy(&id, &newmap.bytes[newmap.map[x + 400 * y]], 4);
						newmap.objectdata[newmap.map[x + 400 * y]].second = pos;
					}*/
				}
				/* Store maximum count */
				newmap.objectdata[id].first = count;
				for(int g = y; g < y + h; g++){
					for(int i = x; i < x + w; i++){
						newmap.map[i + 400 * g] = pos;
					}
				}
				newmap.bytes.insert(newmap.bytes.end(), &b[0], &b[b.size()]);
			}
		}
		uint32_t newmapid = maps.size();
		addtoarr(newmapid, newmap.bytes);
		maps.push_back({newmap});
	}
}
