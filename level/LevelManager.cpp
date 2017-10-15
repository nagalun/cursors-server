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
	
	Level * const welcomeLevel = new LevelWelcome();
	add_level(welcomeLevel);
	
	add_level(new LevelEasy1());
	add_level(new LevelEasy2());
	add_level(new LevelEasy3());
	add_level(new LevelEasy4());
	add_level(new LevelEasy5());
	add_level(new LevelEasy6());
	add_level(new LevelEasy7());
	Level * const e8 = new LevelEasy8();
	add_level(e8);
	add_level(new LevelEasy9());
	add_level(new LevelEasy10());
	
	add_level(new LevelMedium1());
	add_level(new LevelMedium2());
	add_level(new LevelMedium3());
	add_level(new LevelMedium4());
	
	add_level(new LevelBreak1());
	
	add_level(new LevelMedium5());
	add_level(new LevelMedium6());
	add_level(new LevelMedium7());
	add_level(new LevelMedium8());
	add_level(new LevelMedium9());
	
	add_level(new LevelSM1());
	add_level(new LevelSM2());
	add_level(new LevelSM3());
	add_level(new LevelSM4());
	add_level(new LevelSM5());
	
	add_level(new LevelHard1());
	add_level(new LevelHard2());
	add_level(new LevelVeryHard1());
	add_level(new LevelVeryHard2());

	add_level(new LevelEnd());
	add_level(new LevelG(e8));
	add_level(new LevelE());
	for (const auto& ilvl : levels) {
		ilvl->OnInit();
		ilvl->start_ticking();
	}
	welcomeLevel->AddObject(new ObjText(30, 72, 12, true, "Total maps: " + std::to_string(levels.size() - 3)));
}
