#pragma once
#include <cstdint>
#include <unordered_set>
#include <vector>

#include <uWS.h>

#include "../types.hpp"
#include "../misc/FixedArray.hpp"
#include "../misc/IdSys.hpp"

class Cursor;
class LevelObject;

class Level {
private:
	IdSys obj_ids;
	Timer * tick_timer;
	std::uint32_t time;
	std::uint32_t sentplayercount;
	const point_t spawn;
	std::uint8_t map[400 * 300];
	std::unordered_set<Cursor *> players_moved;
	std::unordered_set<Cursor *> players;
	std::unordered_set<LevelObject *> toupdate;
	std::unordered_set<std::uint32_t> objs_to_remove; /* ID to avoid use after free */
	std::unordered_set<LevelObject *> allobjects;
	std::unordered_set<LevelObject *> objects[6];
	FixedArray<line_t> lines;
	FixedArray<point_t> clicks;
	bool timer_active;

public:
	Level(const std::uint16_t x, const std::uint16_t y);
	~Level();

	void RemoveObject(LevelObject * obj);

	/* Official editor compatible functions */
	LevelObject * AddObject(LevelObject * obj);
	virtual void OnInit() = 0;

	void tick();
	static void do_tick(Timer * const);
	
	void start_ticking();
	void stop_ticking();

	void moved(Cursor * cur);
	void click(point_t pos);
	void draw(line_t line);

	point_t check_movement(point_t start, point_t end);

	point_t get_spawnpoint() const;
	std::uint32_t get_time() const;

	void add_player(Cursor *);
	void del_player(Cursor *);
	void send_map(uWS::WebSocket<uWS::SERVER> * socket, const std::uint32_t sync);

	void force_resend();
	void reset();
};
