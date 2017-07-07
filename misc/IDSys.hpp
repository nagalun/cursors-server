#pragma once
#include <stdint.h>
#include <set>

class IDSys {
	uint32_t ids;
	std::set<uint32_t> freeids;

public:
	IDSys();
	uint32_t get_id();
	void free_id(const uint32_t);
};
