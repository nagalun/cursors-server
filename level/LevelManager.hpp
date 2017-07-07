#pragma once
#include <cstddef>
#include <vector>

class Level;
struct Loop;

class LevelManager {
public:
	static std::vector<Level *> levels;
	static Loop * timer_loop;
	
	static Level * GetNextLevel(Level * const);
	static Level * GetPrevLevel(Level * const);
	static Level * GetLevel(size_t index);
	
	static Loop * const get_loop();
	
	static void add_level(Level * const);
	static void initialize_levels(Loop * const);
};
