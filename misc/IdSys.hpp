#pragma once
#include <cstdint>
#include <set>

class IdSys {
	std::uint32_t currentId;
	std::set<std::uint32_t> freeIds;

public:
	IdSys();
	std::uint32_t getId();
	void freeId(std::uint32_t);
};
