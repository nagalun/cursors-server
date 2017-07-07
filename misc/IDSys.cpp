#include "IDSys.hpp"

IDSys::IDSys()
: ids(0) { }

uint32_t IDSys::get_id() {
	uint32_t id = 0;
	if(!freeids.empty()){
		auto it = freeids.end();
		id = *--it;
		freeids.erase(it);
	} else {
		id = ++ids;
	}
	return id;
}

void IDSys::free_id(const uint32_t id) {
	if(id == ids){
		--ids;
	} else {
		freeids.emplace(id);
	}
	if(!freeids.empty()){
		auto it = freeids.end();
		while(--it != freeids.begin() && *it == ids){
			freeids.erase(it);
			--ids;
			it = freeids.end();
		}
	}
}
