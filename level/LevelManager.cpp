#include "LevelManager.hpp"

#include "../LevelData.hpp"
#include "Level.hpp"

#include <algorithm>
#include <random>
#include <chrono>

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
	
	std::vector<Level *> allLevels[5];
	
	auto registerLvl = [&allLevels](int difficulty, Level * const lvl) {
		allLevels[difficulty].push_back(lvl);
	};
	
	auto randomizeLevels = [&allLevels]() {
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		for (int i = 0; i < 5; i++) {
			std::shuffle(allLevels[i].begin(), allLevels[i].end(), std::default_random_engine(seed));
			for (Level * const lvl : allLevels[i]) {
				add_level(lvl);
			}
		}
	};
	
	registerLvl(0, new LevelEasy1());
	registerLvl(0, new LevelEasy2());
	registerLvl(0, new LevelEasy3());
	registerLvl(0, new LevelEasy4());
	registerLvl(0, new LevelEasy5());
	registerLvl(0, new LevelEasy6());
	registerLvl(0, new LevelEasy7());
	LevelEasy8 * const e8 = new LevelEasy8();
	Level * const special = new LevelG(e8);
	e8->setSpecial(special);
	registerLvl(0, e8);
	registerLvl(0, new LevelEasy9());
	registerLvl(0, new LevelEasy10());
	registerLvl(0, new LevelEasy11());
	registerLvl(0, new LevelEasy12());
	registerLvl(0, new LevelEasy13());
	registerLvl(0, new LevelEasy14());
	registerLvl(1, new LevelEasy15());
	registerLvl(1, new LevelEasy16());
	registerLvl(1, new LevelEasy17());
	registerLvl(1, new LevelEasy18());
	registerLvl(1, new LevelEasy19());
	registerLvl(1, new LevelEasy20());
	registerLvl(1, new LevelEasy21());
	registerLvl(1, new LevelEasy22());
	registerLvl(1, new LevelEasy23());
	registerLvl(1, new LevelEasy24());
	registerLvl(1, new LevelEasy25());
	
	registerLvl(1, new LevelMedium1());
	registerLvl(1, new LevelMedium2());
	registerLvl(1, new LevelMedium3());
	registerLvl(1, new LevelMedium4());
	
	registerLvl(1, new LevelBreak1());
	
	registerLvl(1, new LevelMedium5());
	registerLvl(1, new LevelMedium6());
	registerLvl(1, new LevelMedium7());
	registerLvl(1, new LevelMedium8());
	registerLvl(1, new LevelMedium9());
	registerLvl(1, new LevelMedium10());
	registerLvl(1, new LevelMedium11());
	registerLvl(1, new LevelMedium12());
	registerLvl(1, new LevelMedium13());
	registerLvl(1, new LevelMedium14());
	registerLvl(1, new LevelMedium15());
	registerLvl(1, new LevelMedium16());
	registerLvl(1, new LevelMedium17());
	registerLvl(1, new LevelMedium18());
	registerLvl(1, new LevelMedium19());
	registerLvl(1, new LevelMedium20());
	registerLvl(1, new LevelMedium21());
	registerLvl(1, new LevelMedium22());
	registerLvl(1, new LevelMedium23());
	registerLvl(1, new LevelMedium24());
	registerLvl(1, new LevelMedium25());
	registerLvl(1, new LevelMedium26());
	registerLvl(1, new LevelMedium27());
	
	registerLvl(2, new LevelSM1());
	registerLvl(2, new LevelSM2());
	registerLvl(2, new LevelSM3());
	registerLvl(2, new LevelSM4());
	registerLvl(2, new LevelSM5());
	
	registerLvl(3, new LevelHard1());
	registerLvl(3, new LevelHard2());
	registerLvl(3, new LevelHard3());
	registerLvl(3, new LevelHard4());
	registerLvl(3, new LevelHard5());
	
	registerLvl(4, new LevelVeryHard1());
	registerLvl(4, new LevelVeryHard2());
	
	randomizeLevels();

	add_level(new LevelEnd());
	
	add_level(new LevelE());
	
	special->OnInit();
	special->start_ticking();
	for (const auto& ilvl : levels) {
		ilvl->OnInit();
		ilvl->start_ticking();
	}
	welcomeLevel->AddObject(new ObjText(30, 72, 12, true, "Total maps: " + std::to_string(levels.size() - 2)));
}
