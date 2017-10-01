#include "LevelManager.hpp"

#include "../LevelData.hpp"
#include "Level.hpp"

#include <algorithm>

std::vector<Level *> LevelManager::levels = {};
Loop * LevelManager::timer_loop = nullptr;

Level * LevelManager::GetNextLevel(Level * const lvl) {
	auto search = std::find(levels.begin(), levels.end(), lvl);
	return ++search != levels.end() ? *search : nullptr;
}

Level * LevelManager::GetLevel(const std::size_t index) {
	return index >= levels.size() ? nullptr : levels[index];
}

Loop * const LevelManager::get_loop() {
	return timer_loop;
}

void LevelManager::add_level(Level * const lvl) {
	levels.push_back(lvl);
}

void LevelManager::initialize_levels(Loop * const loop) {
	timer_loop = loop;
	add_level(new Level0());
	add_level(new Level1());
	add_level(new Level2());
	add_level(new Level3());
	add_level(new Level4());
	add_level(new Level5());
	add_level(new Level6());
	add_level(new Level7());
	add_level(new Level8());
	add_level(new LevelE());
	for (const auto& ilvl : levels) {
		ilvl->OnInit();
		ilvl->start_ticking();
	}
}
