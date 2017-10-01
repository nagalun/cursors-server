#include "IdSys.hpp"

IdSys::IdSys()
: ids(0) { }

std::uint32_t IdSys::getId() {
	std::uint32_t id;
	if(!freeIds.empty()){
		auto it = freeIds.end();
		id = *--it;
		freeIds.erase(it);
	} else {
		id = ++currentId;
	}
	return id;
}

void IdSys::freeId(std::uint32_t const id) {
	if(id == currentId){
		--currentId;
	} else {
		freeIds.emplace(id);
	}
	if(!freeIds.empty()){
		auto it = freeIds.end();
		while(--it != freeIds.begin() && *it == currentId){
			freeIds.erase(it);
			--currentId;
			it = freeIds.end();
		}
	}
}
