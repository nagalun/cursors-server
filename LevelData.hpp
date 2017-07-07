#pragma once
#include <vector>

#include "level/Level.hpp"
#include "level/LevelManager.hpp"
#include "level/all.hpp"

class LevelE : public Level { /* Empty level */
public:
	LevelE() : Level(200, 150){ }

	void OnInit(){ }
};

class Level0 : public Level {
public:
	Level0() : Level(200, 150){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(40, 10, 10, 40, 0x000000));
		AddObject(new ObjWall(350, 10, 10, 40, 0x000000));
		AddObject(new ObjWall(10, 40, 30, 10, 0x000000));
		AddObject(new ObjWall(360, 40, 30, 10, 0x000000));
		AddObject(new ObjText(370, 60, 12, true, "Empty level"));
		AddObject(new ObjText(30, 60, 12, true, "Misc stuff"));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 10, 10, 30, 30));
		AddObject(new ObjTeleport(LevelManager::GetLevel(LevelManager::levels.size() - 1), 360, 10, 30, 30));
	}
};

class Level1 : public Level {
public:
	Level1() : Level(114, 78){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		wallByColor[1].push_back(AddObject(new ObjWall(30, 0, 10, 50, 0xFF9999)));
		wallByColor[2].push_back(AddObject(new ObjWall(90, 0, 10, 50, 0x9999FF)));
		AddObject(new ObjWall(150, 0, 10, 60, 0x000000));
		AddObject(new ObjWall(220, 0, 20, 140, 0x000000));
		AddObject(new ObjWall(270, 0, 10, 100, 0x000000));
		AddObject(new ObjWall(310, 0, 10, 100, 0x000000));
		AddObject(new ObjWall(250, 10, 10, 110, 0x000000));
		AddObject(new ObjWall(290, 10, 10, 110, 0x000000));
		AddObject(new ObjWall(180, 20, 20, 80, 0x000000));
		AddObject(new ObjWall(20, 50, 60, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(80, 50, 10, 10, 0x9999FF)));
		AddObject(new ObjWall(90, 50, 60, 10, 0x000000));
		AddObject(new ObjWall(20, 60, 10, 200, 0x000000));
		AddObject(new ObjWall(90, 60, 10, 200, 0x000000));
		AddObject(new ObjWall(130, 60, 10, 160, 0x000000));
		AddObject(new ObjWall(40, 70, 50, 10, 0x000000));
		AddObject(new ObjWall(160, 80, 20, 100, 0x000000));
		AddObject(new ObjWall(30, 90, 50, 10, 0x000000));
		AddObject(new ObjWall(40, 110, 50, 10, 0x000000));
		AddObject(new ObjWall(260, 110, 30, 10, 0x000000));
		AddObject(new ObjWall(300, 110, 50, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(350, 110, 50, 20, 0x3333FF)));
		AddObject(new ObjWall(200, 120, 20, 20, 0x000000));
		AddObject(new ObjWall(330, 120, 20, 140, 0x000000));
		AddObject(new ObjWall(30, 130, 50, 10, 0x000000));
		AddObject(new ObjWall(240, 130, 70, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(350, 130, 50, 20, 0xFFFF99)));
		AddObject(new ObjWall(40, 150, 50, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(350, 150, 50, 20, 0x99FFFF)));
		AddObject(new ObjWall(110, 160, 20, 10, 0x000000));
		AddObject(new ObjWall(180, 160, 150, 20, 0x000000));
		AddObject(new ObjWall(30, 170, 50, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(350, 170, 50, 20, 0xFF99FF)));
		AddObject(new ObjWall(100, 180, 20, 10, 0x000000));
		AddObject(new ObjWall(40, 190, 50, 10, 0x000000));
		AddObject(new ObjWall(110, 200, 20, 20, 0x000000));
		AddObject(new ObjWall(140, 200, 170, 20, 0x000000));
		AddObject(new ObjWall(30, 210, 50, 10, 0x000000));
		AddObject(new ObjWall(110, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(40, 230, 50, 10, 0x000000));
		AddObject(new ObjWall(130, 230, 10, 30, 0x000000));
		AddObject(new ObjWall(170, 230, 10, 30, 0x000000));
		AddObject(new ObjWall(100, 240, 30, 20, 0x000000));
		AddObject(new ObjWall(140, 240, 30, 20, 0x000000));
		AddObject(new ObjWall(180, 240, 150, 20, 0x000000));
		AddObject(new ObjWall(30, 250, 50, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(300, 260, 20, 40, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(330, 260, 20, 40, 0x3333FF)));
		AddObject(new ObjAreaCounter(wallByColor[1], 0, 60, 20, 200, 1, 0xFF9999));
		AddObject(new ObjClickBox(wallByColor[2], 45, 5, 40, 40, 5, 1000, 0x9999FF));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 100, 0, 50, 50));
		AddObject(new ObjClickBox(wallByColor[6], 365, 5, 30, 30, 5, 1000, 0x3333FF));
		AddObject(new ObjClickBox(wallByColor[3], 365, 45, 30, 30, 5, 1000, 0xFFFF99));
		AddObject(new ObjClickBox(wallByColor[4], 325, 45, 30, 30, 5, 1000, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[5], 325, 5, 30, 30, 5, 1000, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 330, 260, 70, 40, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 300, 260, 30, 40, 1, 0xFF99FF));
	}
};

class Level2 : public Level {
public:
	Level2() : Level(200, 150){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[8];
		AddObject(new ObjWall(0, 0, 400, 10, 0x000000));
		AddObject(new ObjWall(0, 10, 320, 30, 0x000000));
		wallByColor[7].push_back(AddObject(new ObjWall(320, 10, 70, 10, 0xFFD700)));
		AddObject(new ObjWall(390, 10, 10, 290, 0x000000));
		wallByColor[7].push_back(AddObject(new ObjWall(320, 20, 10, 10, 0xFFD700)));
		AddObject(new ObjWall(330, 20, 50, 20, 0x000000));
		wallByColor[7].push_back(AddObject(new ObjWall(380, 20, 10, 270, 0xFFD700)));
		AddObject(new ObjWall(0, 40, 50, 170, 0x000000));
		AddObject(new ObjWall(70, 40, 10, 20, 0x000000));
		AddObject(new ObjWall(140, 40, 170, 10, 0x000000));
		AddObject(new ObjWall(340, 40, 40, 240, 0x000000));
		AddObject(new ObjWall(140, 50, 50, 40, 0x000000));
		AddObject(new ObjWall(220, 50, 90, 40, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(70, 60, 10, 10, 0x3333FF)));
		AddObject(new ObjWall(70, 70, 10, 140, 0x000000));
		AddObject(new ObjWall(310, 70, 30, 210, 0x000000));
		AddObject(new ObjWall(190, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 90, 20, 120, 0x000000));
		AddObject(new ObjWall(80, 90, 60, 40, 0x000000));
		AddObject(new ObjWall(260, 90, 50, 50, 0x000000));
		AddObject(new ObjWall(150, 100, 40, 10, 0x000000));
		AddObject(new ObjWall(220, 100, 10, 20, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(230, 100, 10, 10, 0x9999FF)));
		AddObject(new ObjWall(240, 100, 10, 40, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(150, 110, 10, 10, 0xFF9999)));
		AddObject(new ObjWall(180, 110, 20, 10, 0x000000));
		AddObject(new ObjWall(210, 110, 10, 20, 0x000000));
		AddObject(new ObjWall(150, 120, 20, 10, 0x000000));
		AddObject(new ObjWall(190, 120, 20, 10, 0x000000));
		AddObject(new ObjWall(80, 130, 20, 80, 0x000000));
		AddObject(new ObjWall(130, 130, 10, 10, 0x000000));
		AddObject(new ObjWall(160, 130, 20, 10, 0x000000));
		AddObject(new ObjWall(200, 130, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 130, 10, 20, 0x000000));
		AddObject(new ObjWall(170, 140, 20, 10, 0x000000));
		AddObject(new ObjWall(220, 140, 10, 30, 0x000000));
		AddObject(new ObjWall(260, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(300, 140, 10, 140, 0x000000));
		AddObject(new ObjWall(130, 150, 10, 130, 0x000000));
		AddObject(new ObjWall(160, 150, 20, 10, 0x000000));
		AddObject(new ObjWall(210, 150, 10, 10, 0x000000));
		AddObject(new ObjWall(100, 160, 30, 120, 0x000000));
		AddObject(new ObjWall(150, 160, 20, 10, 0x000000));
		AddObject(new ObjWall(190, 160, 10, 20, 0x000000));
		AddObject(new ObjWall(230, 160, 10, 20, 0x000000));
		AddObject(new ObjWall(260, 160, 10, 120, 0x000000));
		AddObject(new ObjWall(150, 170, 10, 30, 0x000000));
		AddObject(new ObjWall(180, 170, 10, 20, 0x000000));
		AddObject(new ObjWall(200, 170, 10, 20, 0x000000));
		AddObject(new ObjWall(240, 170, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 170, 30, 110, 0x000000));
		AddObject(new ObjWall(170, 180, 10, 20, 0x000000));
		AddObject(new ObjWall(210, 180, 10, 20, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(240, 180, 10, 10, 0xFFFF99)));
		wallByColor[4].push_back(AddObject(new ObjWall(160, 190, 10, 10, 0x99FFFF)));
		AddObject(new ObjWall(220, 190, 30, 10, 0x000000));
		AddObject(new ObjWall(0, 210, 10, 90, 0x000000));
		AddObject(new ObjWall(90, 210, 10, 70, 0x000000));
		AddObject(new ObjWall(140, 210, 50, 10, 0x000000));
		AddObject(new ObjWall(200, 210, 60, 10, 0x000000));
		AddObject(new ObjWall(140, 220, 40, 60, 0x000000));
		AddObject(new ObjWall(210, 220, 50, 60, 0x000000));
		AddObject(new ObjWall(180, 250, 30, 30, 0x000000));
		wallByColor[7].push_back(AddObject(new ObjWall(90, 280, 290, 10, 0xFFD700)));
		AddObject(new ObjWall(10, 290, 380, 10, 0x000000));
		AddObject(new ObjAreaCounter(wallByColor[1], 150, 110, 30, 10, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[2], 230, 100, 10, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[3], 220, 180, 30, 10, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[4], 160, 170, 10, 30, 1, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[6], 95, 45, 40, 40, 5, 1000, 0x9999FF));
		AddObject(new ObjTeleport({30, 230}, 50, 40, 20, 50));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 100, 130, 30, 30));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 180, 220, 30, 30));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 270, 140, 30, 30));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 190, 50, 30, 30));
		AddObject(new ObjTeleport(LevelManager::GetLevel(8), 310, 40, 30, 30));
		AddObject(new ObjTeleport(10, 210, 10, 10));
		AddObject(new ObjRainbowClickBox(wallByColor[7], 45, 245, 40, 40, 50, 1000));
	}
};

class Level3 : public Level {
public:
	Level3() : Level(380, 20){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		wallByColor[3].push_back(AddObject(new ObjWall(80, 0, 10, 80, 0xFFFF99)));
		wallByColor[3].push_back(AddObject(new ObjWall(120, 0, 10, 80, 0xFFFF99)));
		wallByColor[4].push_back(AddObject(new ObjWall(310, 0, 10, 30, 0x99FFFF)));
		AddObject(new ObjWall(310, 30, 10, 190, 0x000000));
		AddObject(new ObjWall(80, 80, 150, 10, 0x000000));
		AddObject(new ObjWall(80, 90, 10, 130, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(120, 90, 10, 30, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(170, 90, 10, 30, 0xFF99FF)));
		AddObject(new ObjWall(220, 90, 10, 40, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(320, 100, 80, 10, 0xFF9999)));
		AddObject(new ObjWall(90, 120, 40, 10, 0x000000));
		AddObject(new ObjWall(170, 120, 50, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(0, 210, 80, 10, 0x9999FF)));
		AddObject(new ObjWall(90, 210, 220, 10, 0x000000));
		AddObject(new ObjClickBox(wallByColor[1], 325, 95, 70, 20, 5, 1000, 0xFF9999));
		AddObject(new ObjClickBox(wallByColor[2], 325, 225, 70, 70, 5, 1000, 0x9999FF));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 90, 90, 30, 30));
		AddObject(new ObjClickBox(wallByColor[3], 95, 5, 20, 70, 5, 1000, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[3], 0, 0, 10, 10, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[4], 270, 0, 40, 40, 1, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[5], 235, 85, 70, 10, 5, 1000, 0xFF99FF));
		AddObject(new ObjClickBox(wallByColor[6], 195, 95, 20, 20, 5, 1000, 0x3333FF));
		AddObject(new ObjClickBox(wallByColor[5], 185, 95, 10, 20, 5, 1000, 0xFF99FF));
		AddObject(new ObjTeleport(320, 170, 60, 10));
		AddObject(new ObjTeleport(340, 200, 60, 10));
		AddObject(new ObjTeleport(170, 220, 50, 50));
		AddObject(new ObjTeleport(170, 290, 50, 10));
		AddObject(new ObjTeleport(80, 250, 50, 50));
		AddObject(new ObjTeleport(80, 220, 50, 10));
		AddObject(new ObjTeleport(20, 120, 60, 50));
		AddObject(new ObjTeleport(10, 20, 70, 10));
		AddObject(new ObjTeleport(0, 50, 70, 10));
		AddObject(new ObjTeleport(200, 30, 30, 50));
		AddObject(new ObjTeleport(150, 0, 30, 50));
		AddObject(new ObjTeleport(170, 130, 120, 30));
	}
};

class Level4 : public Level {
public:
	Level4() : Level(200, 150){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(0, 0, 400, 60, 0x000000));
		AddObject(new ObjWall(0, 60, 90, 240, 0x000000));
		AddObject(new ObjWall(260, 60, 140, 80, 0x000000));
		AddObject(new ObjWall(160, 110, 30, 190, 0x000000));
		AddObject(new ObjWall(210, 110, 50, 30, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(210, 140, 30, 20, 0xFF9999)));
		wallByColor[2].push_back(AddObject(new ObjWall(240, 140, 30, 20, 0x9999FF)));
		AddObject(new ObjWall(290, 140, 110, 160, 0x000000));
		AddObject(new ObjWall(90, 160, 70, 140, 0x000000));
		AddObject(new ObjWall(190, 160, 100, 140, 0x000000));
		AddObject(new ObjClickBox(wallByColor[1], 215, 65, 40, 40, 20, 750, 0xFF9999));
		AddObject(new ObjClickBox(wallByColor[2], 95, 95, 60, 60, 45, 500, 0x9999FF));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 270, 140, 20, 20));
	}
};

class Level5 : public Level {
public:
	Level5() : Level(200, 270){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(0, 0, 400, 20, 0x000000));
		AddObject(new ObjWall(0, 20, 20, 280, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(160, 20, 20, 40, 0xFF9999)));
		AddObject(new ObjWall(220, 20, 20, 60, 0x000000));
		AddObject(new ObjWall(380, 20, 20, 280, 0x000000));
		AddObject(new ObjWall(20, 60, 200, 20, 0x000000));
		AddObject(new ObjWall(240, 60, 140, 20, 0x000000));
		AddObject(new ObjWall(30, 90, 160, 10, 0x000000));
		AddObject(new ObjWall(210, 90, 160, 10, 0x000000));
		AddObject(new ObjWall(30, 100, 10, 40, 0x000000));
		AddObject(new ObjWall(180, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(360, 100, 10, 40, 0x000000));
		AddObject(new ObjWall(180, 120, 40, 110, 0x000000));
		AddObject(new ObjWall(40, 130, 140, 10, 0x000000));
		AddObject(new ObjWall(220, 130, 140, 10, 0x000000));
		AddObject(new ObjWall(150, 140, 30, 90, 0x000000));
		AddObject(new ObjWall(220, 140, 30, 90, 0x000000));
		AddObject(new ObjWall(20, 150, 120, 20, 0x000000));
		AddObject(new ObjWall(260, 150, 120, 20, 0x000000));
		AddObject(new ObjWall(20, 170, 20, 10, 0x000000));
		AddObject(new ObjWall(60, 170, 80, 10, 0x000000));
		AddObject(new ObjWall(260, 170, 80, 10, 0x000000));
		AddObject(new ObjWall(360, 170, 20, 10, 0x000000));
		AddObject(new ObjWall(30, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(60, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(80, 180, 20, 120, 0x000000));
		AddObject(new ObjWall(120, 180, 20, 20, 0x000000));
		AddObject(new ObjWall(260, 180, 20, 20, 0x000000));
		AddObject(new ObjWall(300, 180, 20, 120, 0x000000));
		AddObject(new ObjWall(330, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(360, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 190, 10, 10, 0x000000));
		AddObject(new ObjWall(140, 190, 10, 110, 0x000000));
		AddObject(new ObjWall(250, 190, 10, 110, 0x000000));
		AddObject(new ObjWall(280, 190, 10, 10, 0x000000));
		AddObject(new ObjWall(20, 200, 60, 20, 0x000000));
		AddObject(new ObjWall(130, 200, 10, 100, 0x000000));
		AddObject(new ObjWall(260, 200, 10, 100, 0x000000));
		AddObject(new ObjWall(320, 200, 60, 20, 0x000000));
		AddObject(new ObjWall(110, 220, 20, 10, 0x000000));
		AddObject(new ObjWall(270, 220, 20, 10, 0x000000));
		AddObject(new ObjWall(30, 230, 10, 70, 0x000000));
		AddObject(new ObjWall(60, 230, 10, 70, 0x000000));
		AddObject(new ObjWall(120, 230, 10, 70, 0x000000));
		AddObject(new ObjWall(150, 230, 20, 70, 0x000000));
		AddObject(new ObjWall(230, 230, 20, 70, 0x000000));
		AddObject(new ObjWall(270, 230, 10, 70, 0x000000));
		AddObject(new ObjWall(330, 230, 10, 70, 0x000000));
		AddObject(new ObjWall(360, 230, 10, 70, 0x000000));
		AddObject(new ObjWall(20, 240, 10, 60, 0x000000));
		AddObject(new ObjWall(70, 240, 10, 60, 0x000000));
		AddObject(new ObjWall(100, 240, 20, 60, 0x000000));
		AddObject(new ObjWall(280, 240, 20, 60, 0x000000));
		AddObject(new ObjWall(320, 240, 10, 60, 0x000000));
		AddObject(new ObjWall(370, 240, 10, 60, 0x000000));
		AddObject(new ObjWall(40, 250, 20, 50, 0x000000));
		AddObject(new ObjWall(170, 250, 20, 50, 0x000000));
		AddObject(new ObjWall(210, 250, 20, 50, 0x000000));
		AddObject(new ObjWall(340, 250, 20, 50, 0x000000));
		AddObject(new ObjWall(190, 280, 20, 20, 0x000000));
		AddObject(new ObjTeleport({50, 240}, 170, 230, 20, 20));
		AddObject(new ObjTeleport({350, 240}, 210, 230, 20, 20));
		AddObject(new ObjTeleport({50, 180}, 70, 230, 10, 10));
		AddObject(new ObjTeleport({280, 210}, 20, 230, 10, 10));
		AddObject(new ObjTeleport({200, 270}, 370, 230, 10, 10));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 180, 20, 40, 40));
		AddObject(new ObjClickBox(wallByColor[1], 245, 25, 30, 30, 5, 1000, 0xFF9999));
		AddObject(new ObjTeleport({255, 185}, 370, 20, 10, 40));
		AddObject(new ObjTeleport({145, 185}, 20, 20, 10, 40));
		AddObject(new ObjTeleport({350, 180}, 20, 180, 10, 10));
		AddObject(new ObjTeleport({350, 240}, 70, 180, 10, 10));
		AddObject(new ObjTeleport({255, 185}, 110, 180, 10, 10));
		AddObject(new ObjTeleport({200, 270}, 110, 230, 10, 10));
		AddObject(new ObjTeleport({200, 270}, 280, 180, 10, 10));
		AddObject(new ObjTeleport({50, 240}, 320, 230, 10, 10));
		AddObject(new ObjTeleport({280, 210}, 320, 180, 10, 10));
		AddObject(new ObjTeleport({120, 210}, 280, 230, 10, 10));
		AddObject(new ObjTeleport({145, 185}, 370, 180, 10, 10));
		AddObject(new ObjTeleport(40, 120, 140, 10));
		AddObject(new ObjTeleport(40, 100, 140, 10));
		AddObject(new ObjTeleport(220, 100, 140, 10));
		AddObject(new ObjTeleport(220, 120, 140, 10));
		AddObject(new ObjTeleport({320, 40}, 350, 110, 10, 10));
		AddObject(new ObjTeleport({100, 40}, 40, 110, 10, 10));
	}
};

class Level6 : public Level {
public:
	Level6() : Level(235, 175){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(100, 0, 10, 160, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(120, 0, 10, 120, 0x99FFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(140, 0, 10, 100, 0x3333FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(160, 0, 10, 80, 0xFF9999)));
		wallByColor[2].push_back(AddObject(new ObjWall(180, 0, 10, 60, 0x9999FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(200, 0, 10, 40, 0xFFFF99)));
		wallByColor[5].push_back(AddObject(new ObjWall(220, 0, 10, 20, 0xFF99FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(240, 0, 10, 10, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(260, 0, 10, 10, 0xFF9999)));
		AddObject(new ObjWall(280, 0, 10, 100, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(300, 0, 10, 10, 0x99FFFF)));
		AddObject(new ObjWall(330, 0, 10, 80, 0x000000));
		AddObject(new ObjWall(380, 0, 20, 100, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(230, 10, 10, 10, 0xFF99FF)));
		AddObject(new ObjWall(240, 10, 30, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(270, 10, 10, 10, 0x99FFFF)));
		AddObject(new ObjWall(300, 10, 10, 110, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(310, 10, 20, 10, 0xFF9999)));
		AddObject(new ObjWall(240, 20, 10, 100, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(260, 20, 10, 10, 0x9999FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(210, 30, 30, 10, 0xFFFF99)));
		wallByColor[6].push_back(AddObject(new ObjWall(250, 30, 10, 10, 0x3333FF)));
		AddObject(new ObjWall(260, 30, 20, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(290, 30, 10, 10, 0x9999FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(310, 30, 20, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(260, 40, 10, 70, 0xFF99FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(190, 50, 50, 10, 0x9999FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(310, 50, 20, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(170, 70, 70, 10, 0xFF9999)));
		wallByColor[3].push_back(AddObject(new ObjWall(310, 70, 20, 10, 0xFFFF99)));
		wallByColor[2].push_back(AddObject(new ObjWall(330, 80, 10, 30, 0x9999FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(150, 90, 90, 10, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(280, 100, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(380, 100, 10, 10, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(130, 110, 90, 10, 0x99FFFF)));
		AddObject(new ObjWall(220, 110, 20, 10, 0x000000));
		AddObject(new ObjWall(250, 110, 50, 10, 0x000000));
		AddObject(new ObjWall(310, 110, 80, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(390, 110, 10, 10, 0x3333FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(220, 120, 10, 30, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(240, 120, 10, 30, 0xFF9999)));
		AddObject(new ObjWall(260, 120, 10, 40, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(280, 120, 10, 30, 0x3333FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(300, 120, 10, 30, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(320, 120, 10, 30, 0xFFFF99)));
		wallByColor[4].push_back(AddObject(new ObjWall(340, 120, 10, 30, 0x99FFFF)));
		wallByColor[1].push_back(AddObject(new ObjWall(360, 120, 10, 30, 0xFF9999)));
		wallByColor[3].push_back(AddObject(new ObjWall(380, 120, 10, 30, 0xFFFF99)));
		AddObject(new ObjWall(110, 150, 150, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(270, 150, 10, 10, 0x9999FF)));
		AddObject(new ObjWall(280, 150, 120, 10, 0x000000));
		AddObject(new ObjAreaCounter(wallByColor[1], 90, 190, 40, 40, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[3], 0, 90, 40, 40, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[4], 10, 180, 40, 40, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[2], 140, 210, 40, 40, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 230, 220, 40, 40, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 320, 180, 40, 40, 1, 0x3333FF));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 250, 120, 10, 30));
	}
};

class Level7 : public Level {
public:
	Level7() : Level(200, 150){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		wallByColor[1].push_back(AddObject(new ObjWall(20, 0, 10, 20, 0xFF9999)));
		AddObject(new ObjWall(60, 0, 10, 70, 0x000000));
		AddObject(new ObjWall(20, 20, 20, 20, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(40, 20, 20, 10, 0x9999FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(0, 30, 20, 10, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(30, 40, 10, 20, 0xFFFF99)));
		wallByColor[6].push_back(AddObject(new ObjWall(0, 60, 20, 10, 0x3333FF)));
		AddObject(new ObjWall(20, 60, 40, 10, 0x000000));
		AddObject(new ObjAreaCounter(wallByColor[2], 30, 0, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 0, 0, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[3], 30, 30, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[4], 0, 30, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[6], 5, 75, 30, 30, 5, 1000, 0x3333FF));

		AddObject(new ObjText(200, 250, 12, true, "Text object test."));

		auto vir = AddObject(new ObjVirus(55, 55));
		auto b20 = AddObject(new ObjToggle({{vir}}, 345, 245, 50, 50, false));
		auto b19 = AddObject(new ObjToggle({{b20}}, 345, 95, 30, 30, false));
		auto b18 = AddObject(new ObjToggle({b19}, 305, 95, 30, 30, false));
		auto b17 = AddObject(new ObjToggle({b18}, 265, 95, 30, 30, false));
		auto b16 = AddObject(new ObjToggle({b17}, 225, 95, 30, 30, false));
		auto b15 = AddObject(new ObjToggle({b16}, 185, 95, 30, 30, false));
		auto b14 = AddObject(new ObjToggle({b15}, 145, 95, 30, 30, false));
		auto b13 = AddObject(new ObjToggle({b14}, 105, 95, 30, 30, false));
		auto b12 = AddObject(new ObjToggle({b13}, 345, 55, 30, 30, false));
		auto b11 = AddObject(new ObjToggle({b12}, 305, 55, 30, 30, false));
		auto b10 = AddObject(new ObjToggle({b11}, 265, 55, 30, 30, false));
		auto b9 = AddObject(new ObjToggle({b10}, 225, 55, 30, 30, false));
		auto b8 = AddObject(new ObjToggle({b9}, 185, 55, 30, 30, false));
		auto b7 = AddObject(new ObjToggle({b8}, 145, 55, 30, 30, false));
		auto b6 = AddObject(new ObjToggle({b7}, 105, 55, 30, 30, false));
		auto b5 = AddObject(new ObjToggle({b6}, 105, 5, 40, 40, false));
		auto b4 = AddObject(new ObjToggle({b5}, 155, 5, 40, 40, false));
		auto b3 = AddObject(new ObjToggle({b4}, 205, 5, 40, 40, false));
		auto b2 = AddObject(new ObjToggle({b3}, 255, 5, 40, 40, false));
		auto b1 = AddObject(new ObjToggle({b2}, 305, 5, 40, 40, false));
		AddObject(new ObjToggle({b1}, 355, 5, 40, 40, false));
	}
};

class Level8 : public Level {
public:
	Level8() : Level(350, 250){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[2];
		AddObject(new ObjWall(0, 0, 25, 300, 0x000000));
		AddObject(new ObjWall(25, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(25, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(50, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(50, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(75, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(75, 75, 25, 225, 0x000000));
		AddObject(new ObjWall(100, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(100, 75, 25, 225, 0x000000));
		AddObject(new ObjWall(125, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(125, 75, 25, 75, 0x000000));
		AddObject(new ObjWall(125, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(150, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(150, 75, 25, 75, 0x000000));
		AddObject(new ObjWall(150, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(175, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(175, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(200, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(200, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(225, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(225, 75, 25, 75, 0x000000));
		AddObject(new ObjWall(225, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(250, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(250, 75, 25, 75, 0x000000));
		AddObject(new ObjWall(250, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(275, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(275, 75, 25, 225, 0x000000));
		AddObject(new ObjWall(300, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(300, 75, 25, 225, 0x000000));
		AddObject(new ObjWall(325, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(325, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(350, 0, 25, 25, 0x000000));
		AddObject(new ObjWall(350, 275, 25, 25, 0x000000));
		AddObject(new ObjWall(375, 0, 25, 300, 0x000000));
		AddObject(new ObjText(225, 230, 30, true, "Gold"));
		AddObject(new ObjText(200, 55, 20, true, "You sometimes get what you want"));
		wallByColor[0].push_back(AddObject(new ObjWall(187, 187, 75, 75, 0xffff00)));
		AddObject(new ObjTeleport(LevelManager::GetLevel(2), 25, 225, 50, 50));
		wallByColor[1].push_back(AddObject(new ObjWall(175, 100, 50, 25, 0xff9999)));
		AddObject(new ObjToggle(wallByColor[1], 130, 155, 40, 40, false));
	}
};
