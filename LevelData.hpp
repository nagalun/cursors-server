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

class LevelG : public Level {
	Level * const linkBack;
public:
	LevelG(Level * const lb) : Level(350, 250), linkBack(lb) {}

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
		AddObject(new ObjTeleport(linkBack, 25, 225, 50, 50));
		wallByColor[1].push_back(AddObject(new ObjWall(175, 100, 50, 25, 0xff9999)));
		AddObject(new ObjToggle(wallByColor[1], 130, 155, 40, 40, false));
	}
};

class LevelWelcome : public Level {
public:
	LevelWelcome() : Level(200, 150){}

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



class LevelBreak1 : public Level {
public:
	LevelBreak1() : Level(200, 150){}

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
		
		AddObject(new ObjWall(0, 270, 20, 10, 0x000000));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 0, 280, 20, 20));
	}
};



class LevelEasy1 : public Level {
public:
	LevelEasy1() : Level(200, 150){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(0, 40, 360, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(360, 40, 40, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(40, 50, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(80, 50, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(120, 50, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(160, 50, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(200, 50, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(240, 50, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(280, 50, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(320, 50, 10, 10, 0x99FFFF)));
		wallByColor[2].push_back(AddObject(new ObjWall(350, 50, 10, 20, 0x9999FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(0, 60, 30, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(60, 60, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(100, 60, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(140, 60, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(180, 60, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(220, 60, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(260, 60, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(300, 60, 10, 10, 0x99FFFF)));
		AddObject(new ObjWall(40, 70, 320, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(10, 80, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(40, 80, 10, 50, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(0, 100, 30, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(10, 120, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(50, 120, 130, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(180, 120, 40, 10, 0xFF9999)));
		AddObject(new ObjWall(220, 120, 180, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(40, 130, 10, 30, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(80, 130, 10, 30, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(120, 130, 10, 30, 0x99FFFF)));
		wallByColor[5].push_back(AddObject(new ObjWall(170, 130, 10, 40, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(220, 130, 10, 40, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(290, 130, 10, 30, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(330, 130, 10, 30, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(60, 140, 10, 30, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(100, 140, 10, 30, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(270, 140, 10, 30, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(310, 140, 10, 30, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(350, 140, 10, 30, 0x99FFFF)));
		AddObject(new ObjWall(0, 170, 180, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(180, 170, 40, 10, 0xFF9999)));
		AddObject(new ObjWall(220, 170, 140, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(360, 170, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(350, 180, 10, 50, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(370, 190, 30, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(360, 210, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(40, 220, 310, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(40, 230, 10, 20, 0xFFFF99)));
		wallByColor[4].push_back(AddObject(new ObjWall(90, 230, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(130, 230, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(170, 230, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(210, 230, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(250, 230, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(290, 230, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(330, 230, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(370, 230, 30, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(70, 240, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(110, 240, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(150, 240, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(190, 240, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(230, 240, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(270, 240, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(310, 240, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(350, 240, 10, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(0, 250, 40, 10, 0x99FFFF)));
		AddObject(new ObjWall(40, 250, 360, 10, 0x000000));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 230, 130, 40, 40));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 130, 130, 40, 40));
		AddObject(new ObjClickBox(wallByColor[3], 5, 5, 30, 30, 5, 1000, 0xFFFF99));
		AddObject(new ObjClickBox(wallByColor[2], 365, 265, 30, 30, 5, 1000, 0x9999FF));
		AddObject(new ObjClickBox(wallByColor[4], 55, 85, 30, 30, 5, 1000, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[4], 315, 185, 30, 30, 5, 1000, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[1], 180, 130, 40, 40, 1, 0xFF9999));
		AddObject(new ObjClickBox(wallByColor[5], 5, 135, 30, 30, 5, 1000, 0xFF99FF));
		AddObject(new ObjClickBox(wallByColor[5], 365, 135, 30, 30, 5, 1000, 0xFF99FF));
	}
};

class LevelEasy2 : public Level {
public:
	LevelEasy2() : Level(200, 150){}

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

class LevelEasy3 : public Level {
public:
	LevelEasy3() : Level(200, 150){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(0, 0, 170, 120, 0x000000));
		AddObject(new ObjWall(230, 0, 170, 120, 0x000000));
		AddObject(new ObjWall(170, 60, 20, 70, 0x000000));
		AddObject(new ObjWall(210, 60, 20, 70, 0x000000));
		AddObject(new ObjWall(60, 120, 110, 20, 0x000000));
		AddObject(new ObjWall(230, 120, 110, 20, 0x000000));
		AddObject(new ObjWall(170, 130, 10, 10, 0x000000));
		AddObject(new ObjWall(220, 130, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(60, 140, 120, 20, 0xFFFF99)));
		wallByColor[3].push_back(AddObject(new ObjWall(220, 140, 110, 20, 0xFFFF99)));
		AddObject(new ObjWall(60, 160, 120, 80, 0x000000));
		AddObject(new ObjWall(220, 160, 120, 80, 0x000000));
		AddObject(new ObjWall(180, 170, 10, 70, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(190, 170, 10, 10, 0x9999FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(200, 170, 10, 10, 0xFF9999)));
		AddObject(new ObjWall(210, 170, 10, 70, 0x000000));
		AddObject(new ObjWall(0, 180, 60, 120, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 180, 10, 10, 0xFF9999)));
		wallByColor[2].push_back(AddObject(new ObjWall(200, 180, 10, 10, 0x9999FF)));
		AddObject(new ObjWall(340, 180, 60, 120, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(190, 190, 10, 10, 0x9999FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(200, 190, 10, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 200, 10, 10, 0xFF9999)));
		wallByColor[2].push_back(AddObject(new ObjWall(200, 200, 10, 10, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(190, 210, 10, 10, 0x9999FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(200, 210, 10, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 220, 10, 10, 0xFF9999)));
		wallByColor[2].push_back(AddObject(new ObjWall(200, 220, 10, 10, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(190, 230, 10, 10, 0x9999FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(200, 230, 10, 10, 0xFF9999)));
		AddObject(new ObjWall(60, 240, 110, 60, 0x000000));
		AddObject(new ObjWall(230, 240, 110, 60, 0x000000));
		AddObject(new ObjClickBox(wallByColor[1], 345, 125, 50, 50, 5, 1000, 0xFF9999));
		AddObject(new ObjClickBox(wallByColor[2], 5, 125, 50, 50, 5, 1000, 0x9999FF));
		AddObject(new ObjClickBox(wallByColor[3], 175, 5, 50, 50, 5, 1000, 0xFFFF99));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 170, 240, 60, 60));
	}
};

class LevelEasy4 : public Level {
public:
	LevelEasy4() : Level(200, 290) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[1];
		
		AddObject(new ObjText(200, 13, 20, true, "Some walls are not what they look like"));
		AddObject(new ObjText(115, 213, 20, true, "Gold"));
		wallByColor[0].push_back(AddObject(new ObjWall(60, 180, 110, 60, 0xFFFF00)));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 190, 140, 20, 20));
		AddObject(new ObjClickBox({}, 81, 20, 18, 20, 0, 1000, 0x0));
		AddObject(new ObjClickBox({}, 190, 81, 20, 18, 0, 1000, 0x0));
		AddObject(new ObjClickBox({}, 221, 140, 18, 20, 0, 1000, 0x0));
		AddObject(new ObjClickBox({}, 190, 160, 20, 19, 0, 1000, 0x0));
		AddObject(new ObjWall(20, 20, 60, 20, 0x00000000));
		AddObject(new ObjWall(100, 20, 280, 20, 0x00000000));
		AddObject(new ObjWall(20, 40, 20, 240, 0x00000000));
		AddObject(new ObjWall(190, 40, 20, 40, 0x00000000));
		AddObject(new ObjWall(360, 40, 20, 240, 0x00000000));
		AddObject(new ObjWall(190, 100, 20, 40, 0x00000000));
		AddObject(new ObjWall(180, 130, 10, 40, 0x00000000));
		AddObject(new ObjWall(210, 130, 10, 40, 0x00000000));
		AddObject(new ObjWall(40, 140, 140, 20, 0x00000000));
		AddObject(new ObjWall(240, 140, 120, 20, 0x00000000));
		AddObject(new ObjWall(190, 180, 20, 100, 0x00000000));
		AddObject(new ObjWall(40, 260, 150, 20, 0x00000000));
		AddObject(new ObjWall(210, 260, 150, 20, 0x00000000));
		
	}
};

class LevelEasy5 : public Level {
public:
	LevelEasy5() : Level(370, 50) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[1];
		
		wallByColor[0].push_back(AddObject(new ObjWall(20, 40, 20, 20, 0xFF9999)));
		wallByColor[0].push_back(AddObject(new ObjWall(240, 40, 20, 20, 0xFF9999)));
		AddObject(new ObjAreaCounter(wallByColor[0], 0, 280, 20, 20, 1, 0xFF9999));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 200, 0, 20, 20));
		AddObject(new ObjWall(100, 0, 20, 40, 0x0));
		AddObject(new ObjWall(180, 0, 20, 40, 0x0));
		AddObject(new ObjWall(260, 0, 20, 160, 0x0));
		AddObject(new ObjWall(380, 0, 20, 300, 0x0));
		AddObject(new ObjWall(20, 20, 80, 20, 0x0));
		AddObject(new ObjWall(140, 20, 20, 140, 0x0));
		AddObject(new ObjWall(200, 20, 40, 20, 0x0));
		AddObject(new ObjWall(300, 20, 60, 20, 0x0));
		AddObject(new ObjWall(220, 40, 20, 40, 0x0));
		AddObject(new ObjWall(340, 40, 20, 40, 0x0));
		AddObject(new ObjWall(20, 60, 120, 20, 0x0));
		AddObject(new ObjWall(160, 60, 40, 20, 0x0));
		AddObject(new ObjWall(280, 60, 40, 20, 0x0));
		AddObject(new ObjWall(360, 60, 20, 20, 0x0));
		AddObject(new ObjWall(20, 100, 100, 20, 0x0));
		AddObject(new ObjWall(160, 100, 100, 20, 0x0));
		AddObject(new ObjWall(300, 100, 60, 20, 0x0));
		AddObject(new ObjWall(20, 120, 20, 80, 0x0));
		AddObject(new ObjWall(300, 120, 20, 80, 0x0));
		AddObject(new ObjWall(60, 140, 80, 20, 0x0));
		AddObject(new ObjWall(180, 140, 60, 20, 0x0));
		AddObject(new ObjWall(340, 140, 20, 100, 0x0));
		AddObject(new ObjWall(180, 160, 20, 40, 0x0));
		AddObject(new ObjWall(220, 160, 20, 140, 0x0));
		AddObject(new ObjWall(40, 180, 140, 20, 0x0));
		AddObject(new ObjWall(240, 180, 60, 20, 0x0));
		AddObject(new ObjWall(0, 220, 200, 20, 0x0));
		AddObject(new ObjWall(260, 220, 80, 20, 0x0));
		AddObject(new ObjWall(180, 240, 20, 40, 0x0));
		AddObject(new ObjWall(260, 240, 20, 60, 0x0));
		AddObject(new ObjWall(0, 260, 40, 20, 0x0));
		AddObject(new ObjWall(60, 260, 100, 20, 0x0));
		AddObject(new ObjWall(300, 260, 60, 20, 0x0));
		AddObject(new ObjWall(140, 280, 20, 20, 0x0));
		AddObject(new ObjWall(300, 280, 20, 20, 0x0));
		
	}
};

class LevelEasy6 : public Level {
public:
	LevelEasy6() : Level(200, 290) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[2];
		
		wallByColor[0].push_back(AddObject(new ObjWall(0, 120, 20, 20, 0xFF9999)));
		
		wallByColor[1].push_back(AddObject(new ObjWall(380, 120, 20, 20, 0x9999FF)));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 170, 110, 60, 60));
		AddObject(new ObjClickBox(wallByColor[1], 0, 140, 20, 20, 10, 1000, 0x9999FF));
		AddObject(new ObjClickBox(wallByColor[0], 380, 140, 20, 20, 10, 1000, 0xFF9999));
		AddObject(new ObjWall(20, 20, 170, 10, 0x0));
		AddObject(new ObjWall(210, 20, 170, 10, 0x0));
		AddObject(new ObjWall(20, 30, 10, 250, 0x0));
		AddObject(new ObjWall(370, 30, 10, 250, 0x0));
		AddObject(new ObjWall(40, 40, 320, 10, 0x0));
		AddObject(new ObjWall(40, 50, 10, 210, 0x0));
		AddObject(new ObjWall(350, 50, 10, 210, 0x0));
		AddObject(new ObjWall(60, 60, 280, 10, 0x0));
		AddObject(new ObjWall(60, 70, 10, 70, 0x0));
		AddObject(new ObjWall(330, 70, 10, 70, 0x0));
		AddObject(new ObjWall(80, 80, 110, 10, 0x0));
		AddObject(new ObjWall(210, 80, 110, 10, 0x0));
		AddObject(new ObjWall(80, 90, 10, 130, 0x0));
		AddObject(new ObjWall(310, 90, 10, 130, 0x0));
		AddObject(new ObjWall(100, 100, 200, 10, 0x0));
		AddObject(new ObjWall(100, 110, 10, 30, 0x0));
		AddObject(new ObjWall(120, 110, 10, 70, 0x0));
		AddObject(new ObjWall(160, 110, 10, 70, 0x0));
		AddObject(new ObjWall(230, 110, 10, 70, 0x0));
		AddObject(new ObjWall(270, 110, 10, 70, 0x0));
		AddObject(new ObjWall(290, 110, 10, 30, 0x0));
		AddObject(new ObjWall(140, 120, 10, 80, 0x0));
		AddObject(new ObjWall(250, 120, 10, 80, 0x0));
		AddObject(new ObjWall(60, 160, 10, 80, 0x0));
		AddObject(new ObjWall(100, 160, 10, 40, 0x0));
		AddObject(new ObjWall(290, 160, 10, 40, 0x0));
		AddObject(new ObjWall(330, 160, 10, 80, 0x0));
		AddObject(new ObjWall(110, 190, 30, 10, 0x0));
		AddObject(new ObjWall(150, 190, 100, 10, 0x0));
		AddObject(new ObjWall(260, 190, 30, 10, 0x0));
		AddObject(new ObjWall(90, 210, 220, 10, 0x0));
		AddObject(new ObjWall(70, 230, 260, 10, 0x0));
		AddObject(new ObjWall(50, 250, 140, 10, 0x0));
		AddObject(new ObjWall(210, 250, 140, 10, 0x0));
		AddObject(new ObjWall(30, 270, 340, 10, 0x0));
		
	}
};

class LevelEasy7 : public Level {
public:
	LevelEasy7() : Level(114, 78){}

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

class LevelEasy8 : public Level {
public:
	LevelEasy8() : Level(200, 150){}

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
		AddObject(new ObjTeleport(LevelManager::GetLevel(LevelManager::levels.size() - 2), 310, 40, 30, 30));
		AddObject(new ObjTeleport(10, 210, 10, 10));
		AddObject(new ObjRainbowClickBox(wallByColor[7], 45, 245, 40, 40, 50, 1000));
	}
};

class LevelEasy9 : public Level { /* Big button covering everything */
public:
	LevelEasy9() : Level(200, 150){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(10, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 20, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 100, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(160, 100, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(170, 100, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(180, 100, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(190, 100, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(200, 100, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(210, 100, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(220, 100, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(230, 100, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(240, 100, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(250, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 100, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(150, 110, 10, 10, 0xFFFFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(250, 110, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(10, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 120, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(150, 130, 10, 10, 0xFFFFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(250, 130, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(10, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 140, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(150, 150, 10, 10, 0xFFFFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(250, 150, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(10, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 160, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(150, 170, 10, 10, 0xFFFFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(250, 170, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(10, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 180, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(150, 190, 10, 10, 0xFFFFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(250, 190, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(10, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 200, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(160, 200, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(170, 200, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(180, 200, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(190, 200, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(200, 200, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(210, 200, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(220, 200, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(230, 200, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(240, 200, 10, 10, 0xFFFFFF)));
		AddObject(new ObjWall(250, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 260, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(50, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(90, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(270, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(350, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 280, 10, 10, 0x000000));
		AddObject(new ObjWall(390, 280, 10, 10, 0x000000));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 360, 260, 40, 40));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 360, 0, 40, 40));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 0, 260, 40, 40));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 0, 0, 40, 40));
		AddObject(new ObjClickBox(wallByColor[6], 0, 0, 400, 300, 5, 1000, 0xFFFFFF));
	}
};

class LevelEasy10 : public Level {
public:
	LevelEasy10() : Level(200, 230){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		wallByColor[1].push_back(AddObject(new ObjWall(70, 0, 20, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(100, 0, 20, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(130, 0, 30, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(170, 0, 20, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(210, 0, 30, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(250, 0, 30, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(290, 0, 30, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(70, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(90, 10, 10, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(110, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(130, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(150, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(170, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 10, 10, 30, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(210, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(230, 10, 10, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(250, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(290, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(310, 10, 10, 40, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(140, 20, 10, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(220, 20, 10, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(260, 20, 10, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(230, 30, 10, 20, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(180, 40, 10, 10, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(260, 40, 20, 10, 0xFF9999)));
		AddObject(new ObjWall(90, 50, 210, 10, 0x000000));
		AddObject(new ObjWall(90, 60, 10, 80, 0x000000));
		AddObject(new ObjWall(290, 60, 10, 90, 0x000000));
		AddObject(new ObjWall(120, 70, 160, 10, 0x000000));
		AddObject(new ObjWall(120, 80, 10, 90, 0x000000));
		AddObject(new ObjWall(270, 80, 10, 90, 0x000000));
		AddObject(new ObjWall(140, 90, 120, 10, 0x000000));
		AddObject(new ObjWall(140, 100, 10, 90, 0x000000));
		AddObject(new ObjWall(250, 100, 10, 90, 0x000000));
		AddObject(new ObjWall(160, 110, 80, 10, 0x000000));
		AddObject(new ObjWall(160, 120, 10, 50, 0x000000));
		AddObject(new ObjWall(230, 120, 10, 50, 0x000000));
		AddObject(new ObjWall(20, 130, 70, 10, 0x000000));
		AddObject(new ObjWall(180, 130, 40, 10, 0x000000));
		AddObject(new ObjWall(20, 140, 10, 130, 0x000000));
		AddObject(new ObjWall(180, 140, 10, 30, 0x000000));
		AddObject(new ObjWall(210, 140, 10, 30, 0x000000));
		AddObject(new ObjWall(300, 140, 60, 10, 0x000000));
		AddObject(new ObjWall(50, 150, 10, 20, 0x000000));
		AddObject(new ObjWall(70, 150, 50, 10, 0x000000));
		AddObject(new ObjWall(350, 150, 10, 40, 0x000000));
		AddObject(new ObjWall(40, 160, 10, 30, 0x000000));
		AddObject(new ObjWall(60, 160, 20, 10, 0x000000));
		AddObject(new ObjWall(90, 160, 30, 10, 0x000000));
		AddObject(new ObjWall(170, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(220, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(280, 160, 20, 10, 0x000000));
		AddObject(new ObjWall(310, 160, 10, 30, 0x000000));
		AddObject(new ObjWall(90, 170, 10, 100, 0x000000));
		AddObject(new ObjWall(290, 170, 10, 20, 0x000000));
		AddObject(new ObjWall(50, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 180, 10, 30, 0x000000));
		AddObject(new ObjWall(160, 180, 30, 10, 0x000000));
		AddObject(new ObjWall(210, 180, 40, 10, 0x000000));
		AddObject(new ObjWall(260, 180, 30, 10, 0x000000));
		AddObject(new ObjWall(300, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 180, 20, 10, 0x000000));
		AddObject(new ObjWall(360, 180, 20, 10, 0x000000));
		AddObject(new ObjWall(180, 190, 10, 30, 0x000000));
		AddObject(new ObjWall(260, 190, 20, 20, 0x000000));
		AddObject(new ObjWall(370, 190, 10, 60, 0x000000));
		AddObject(new ObjWall(30, 200, 40, 10, 0x000000));
		AddObject(new ObjWall(190, 200, 30, 20, 0x000000));
		AddObject(new ObjWall(240, 200, 10, 20, 0x000000));
		AddObject(new ObjWall(280, 200, 60, 10, 0x000000));
		AddObject(new ObjWall(350, 200, 20, 10, 0x000000));
		AddObject(new ObjWall(100, 210, 80, 10, 0x000000));
		AddObject(new ObjWall(220, 210, 20, 10, 0x000000));
		AddObject(new ObjWall(260, 210, 10, 40, 0x000000));
		AddObject(new ObjWall(330, 210, 10, 60, 0x000000));
		AddObject(new ObjWall(210, 220, 10, 30, 0x000000));
		AddObject(new ObjWall(110, 240, 100, 10, 0x000000));
		AddObject(new ObjWall(350, 240, 20, 10, 0x000000));
		AddObject(new ObjWall(350, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(30, 260, 60, 10, 0x000000));
		AddObject(new ObjWall(100, 260, 170, 10, 0x000000));
		AddObject(new ObjWall(280, 260, 50, 10, 0x000000));
		AddObject(new ObjWall(260, 270, 10, 30, 0x000000));
		AddObject(new ObjWall(280, 270, 10, 10, 0x000000));
		AddObject(new ObjWall(300, 280, 50, 10, 0x000000));
		AddObject(new ObjWall(270, 290, 40, 10, 0x000000));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 30, 210, 60, 50));
		AddObject(new ObjTeleport(310, 240, 20, 10));
		AddObject(new ObjTeleport(290, 210, 10, 20));
		AddObject(new ObjTeleport(340, 220, 20, 10));
		AddObject(new ObjTeleport(320, 160, 20, 10));
		AddObject(new ObjTeleport(280, 240, 20, 20));
	}
};



class LevelMedium1 : public Level {
public:
	LevelMedium1() : Level(205, 5){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(0, 0, 10, 60, 0x000000));
		AddObject(new ObjWall(40, 0, 10, 110, 0x000000));
		AddObject(new ObjWall(80, 0, 10, 110, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(140, 0, 10, 40, 0x99FFFF)));
		AddObject(new ObjWall(190, 0, 10, 290, 0x000000));
		AddObject(new ObjWall(250, 0, 20, 30, 0x000000));
		AddObject(new ObjWall(300, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(340, 0, 10, 10, 0x000000));
		AddObject(new ObjWall(20, 10, 10, 120, 0x000000));
		AddObject(new ObjWall(60, 10, 10, 120, 0x000000));
		AddObject(new ObjWall(100, 10, 10, 120, 0x000000));
		AddObject(new ObjWall(200, 10, 40, 10, 0x000000));
		AddObject(new ObjWall(280, 10, 10, 20, 0x000000));
		AddObject(new ObjWall(320, 10, 10, 20, 0x000000));
		AddObject(new ObjWall(360, 10, 10, 30, 0x000000));
		AddObject(new ObjWall(380, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 20, 10, 20, 0x000000));
		AddObject(new ObjWall(290, 20, 30, 10, 0x000000));
		AddObject(new ObjWall(330, 20, 30, 10, 0x000000));
		AddObject(new ObjWall(210, 30, 20, 10, 0x000000));
		AddObject(new ObjWall(250, 30, 10, 50, 0x000000));
		AddObject(new ObjWall(290, 30, 10, 30, 0x000000));
		AddObject(new ObjWall(310, 30, 10, 30, 0x000000));
		AddObject(new ObjWall(370, 30, 20, 10, 0x000000));
		AddObject(new ObjWall(110, 40, 40, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(150, 40, 40, 10, 0xFFFF99)));
		AddObject(new ObjWall(270, 40, 10, 40, 0x000000));
		AddObject(new ObjWall(330, 40, 10, 20, 0x000000));
		AddObject(new ObjWall(380, 40, 10, 20, 0x000000));
		AddObject(new ObjWall(140, 50, 10, 40, 0x000000));
		AddObject(new ObjWall(210, 50, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 50, 10, 30, 0x000000));
		AddObject(new ObjWall(340, 50, 20, 10, 0x000000));
		AddObject(new ObjWall(370, 50, 10, 50, 0x000000));
		AddObject(new ObjWall(120, 60, 10, 50, 0x000000));
		AddObject(new ObjWall(350, 60, 10, 20, 0x000000));
		AddObject(new ObjWall(10, 70, 10, 10, 0x000000));
		AddObject(new ObjWall(200, 70, 20, 10, 0x000000));
		AddObject(new ObjWall(240, 70, 10, 30, 0x000000));
		AddObject(new ObjWall(260, 70, 10, 10, 0x000000));
		AddObject(new ObjWall(280, 70, 70, 10, 0x000000));
		AddObject(new ObjWall(390, 70, 10, 10, 0x000000));
		AddObject(new ObjWall(150, 80, 30, 10, 0x000000));
		AddObject(new ObjWall(0, 90, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 90, 10, 30, 0x000000));
		AddObject(new ObjWall(230, 90, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 90, 10, 20, 0x000000));
		AddObject(new ObjWall(270, 90, 10, 20, 0x000000));
		AddObject(new ObjWall(300, 90, 20, 10, 0x000000));
		AddObject(new ObjWall(330, 90, 40, 10, 0x000000));
		AddObject(new ObjWall(380, 90, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 100, 60, 10, 0x000000));
		AddObject(new ObjWall(280, 100, 10, 50, 0x000000));
		AddObject(new ObjWall(300, 100, 10, 50, 0x000000));
		AddObject(new ObjWall(330, 100, 10, 30, 0x000000));
		AddObject(new ObjWall(350, 100, 10, 30, 0x000000));
		AddObject(new ObjWall(10, 110, 10, 10, 0x000000));
		AddObject(new ObjWall(200, 110, 10, 10, 0x000000));
		AddObject(new ObjWall(230, 110, 10, 40, 0x000000));
		AddObject(new ObjWall(310, 110, 10, 10, 0x000000));
		AddObject(new ObjWall(370, 110, 20, 20, 0x000000));
		AddObject(new ObjWall(30, 120, 30, 10, 0x000000));
		AddObject(new ObjWall(70, 120, 30, 10, 0x000000));
		AddObject(new ObjWall(110, 120, 70, 10, 0x000000));
		AddObject(new ObjWall(240, 120, 30, 10, 0x000000));
		AddObject(new ObjWall(360, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(30, 130, 10, 10, 0x000000));
		AddObject(new ObjWall(70, 130, 10, 10, 0x000000));
		AddObject(new ObjWall(110, 130, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 130, 10, 20, 0x000000));
		AddObject(new ObjWall(380, 130, 10, 20, 0x000000));
		AddObject(new ObjWall(50, 140, 10, 20, 0x000000));
		AddObject(new ObjWall(90, 140, 10, 20, 0x000000));
		AddObject(new ObjWall(130, 140, 60, 20, 0x000000));
		AddObject(new ObjWall(200, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(220, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(240, 140, 40, 10, 0x000000));
		AddObject(new ObjWall(290, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(310, 140, 70, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(0, 150, 10, 10, 0x3333FF)));
		AddObject(new ObjWall(10, 150, 40, 10, 0x000000));
		AddObject(new ObjWall(60, 150, 30, 10, 0x000000));
		AddObject(new ObjWall(100, 150, 30, 10, 0x000000));
		AddObject(new ObjWall(10, 160, 10, 130, 0x000000));
		AddObject(new ObjWall(210, 160, 190, 10, 0x000000));
		AddObject(new ObjWall(30, 170, 150, 10, 0x000000));
		AddObject(new ObjWall(30, 180, 10, 90, 0x000000));
		AddObject(new ObjWall(170, 180, 10, 110, 0x000000));
		AddObject(new ObjWall(200, 180, 190, 10, 0x000000));
		AddObject(new ObjWall(50, 190, 110, 10, 0x000000));
		AddObject(new ObjWall(50, 200, 10, 50, 0x000000));
		AddObject(new ObjWall(150, 200, 10, 70, 0x000000));
		AddObject(new ObjWall(210, 200, 190, 10, 0x000000));
		AddObject(new ObjWall(130, 210, 10, 40, 0x000000));
		AddObject(new ObjWall(200, 220, 190, 10, 0x000000));
		AddObject(new ObjWall(60, 240, 70, 10, 0x000000));
		AddObject(new ObjWall(210, 240, 190, 10, 0x000000));
		AddObject(new ObjWall(240, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(280, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(320, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(360, 250, 40, 10, 0x000000));
		AddObject(new ObjWall(40, 260, 110, 10, 0x000000));
		AddObject(new ObjWall(220, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(260, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(300, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(340, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(20, 280, 150, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 290, 10, 10, 0xFF9999)));
		AddObject(new ObjAreaCounter(wallByColor[4], 150, 40, 40, 40, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[3], 110, 0, 40, 40, 1, 0xFFFF99));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 150, 0, 40, 40));
		AddObject(new ObjClickBox(wallByColor[6], 65, 205, 30, 30, 5, 1000, 0x3333FF));
		AddObject(new ObjClickBox(wallByColor[1], 365, 265, 30, 30, 5, 1000, 0xFF9999));
	}
};

class LevelMedium2 : public Level {
public:
	LevelMedium2() : Level(200, 100){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		wallByColor[6].push_back(AddObject(new ObjWall(40, 0, 10, 30, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(80, 0, 10, 30, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(120, 0, 10, 30, 0x3333FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(160, 0, 10, 40, 0xFF9999)));
		wallByColor[2].push_back(AddObject(new ObjWall(230, 0, 10, 40, 0x9999FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(270, 0, 10, 30, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(310, 0, 10, 30, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(350, 0, 10, 30, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(60, 10, 10, 30, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(100, 10, 10, 30, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(140, 10, 10, 30, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(250, 10, 10, 30, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(290, 10, 10, 30, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(330, 10, 10, 30, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(10, 40, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(40, 40, 140, 40, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(180, 40, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(190, 40, 10, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(200, 40, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(210, 40, 10, 10, 0xFF99FF)));
		AddObject(new ObjWall(220, 40, 140, 40, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(360, 40, 30, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(180, 50, 10, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(190, 50, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(200, 50, 10, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(210, 50, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(0, 60, 30, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(180, 60, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(190, 60, 10, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(200, 60, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(210, 60, 10, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(370, 60, 30, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(180, 70, 10, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(190, 70, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(200, 70, 10, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(210, 70, 10, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(10, 80, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(40, 80, 40, 180, 0x000000));
		AddObject(new ObjWall(320, 80, 40, 180, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(360, 80, 30, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(0, 100, 30, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(370, 100, 30, 10, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(10, 120, 30, 10, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(90, 120, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(120, 120, 160, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(280, 120, 30, 10, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(360, 120, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(120, 130, 10, 130, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(150, 130, 10, 30, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(240, 130, 10, 30, 0xFFFF99)));
		AddObject(new ObjWall(270, 130, 10, 130, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(0, 140, 30, 10, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(80, 140, 30, 10, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(170, 140, 10, 30, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(220, 140, 10, 30, 0xFFFF99)));
		wallByColor[6].push_back(AddObject(new ObjWall(290, 140, 30, 10, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(370, 140, 30, 10, 0x3333FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(130, 150, 20, 10, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(250, 150, 20, 10, 0xFFFF99)));
		wallByColor[5].push_back(AddObject(new ObjWall(10, 160, 30, 10, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(90, 160, 30, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(280, 160, 30, 10, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(360, 160, 30, 10, 0x3333FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(140, 170, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(170, 170, 10, 130, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(180, 170, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(220, 170, 10, 130, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(230, 170, 30, 10, 0xFFFF99)));
		wallByColor[5].push_back(AddObject(new ObjWall(0, 180, 30, 10, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(80, 180, 30, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(290, 180, 30, 10, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(370, 180, 30, 10, 0x3333FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(130, 190, 30, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(190, 190, 30, 10, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(240, 190, 30, 10, 0xFFFF99)));
		wallByColor[5].push_back(AddObject(new ObjWall(10, 200, 30, 10, 0xFF99FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(90, 200, 30, 10, 0xFF99FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(280, 200, 30, 10, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(360, 200, 30, 10, 0x3333FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(180, 210, 30, 10, 0xFFFF99)));
		wallByColor[4].push_back(AddObject(new ObjWall(190, 230, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(80, 250, 40, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(180, 250, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(280, 250, 40, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(70, 260, 30, 40, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(300, 260, 30, 40, 0xFFFF99)));
		AddObject(new ObjAreaCounter(wallByColor[2], 220, 0, 10, 40, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 170, 0, 10, 40, 1, 0xFF9999));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 180, 260, 40, 40));
		AddObject(new ObjClickBox(wallByColor[3], 5, 225, 30, 30, 5, 1000, 0xFFFF99));
		AddObject(new ObjClickBox(wallByColor[4], 365, 225, 30, 30, 5, 1000, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[5], 285, 215, 30, 30, 5, 1000, 0xFF99FF));
		AddObject(new ObjClickBox(wallByColor[6], 85, 215, 30, 30, 5, 1000, 0x3333FF));
	}
};

class LevelMedium3 : public Level {
public:
	LevelMedium3() : Level(20, 20) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[3];
		
		wallByColor[0].push_back(AddObject(new ObjWall(40, 70, 10, 30, 0xFF0000)));
		wallByColor[0].push_back(AddObject(new ObjWall(60, 170, 10, 30, 0xFF0000)));
		
		wallByColor[1].push_back(AddObject(new ObjWall(40, 120, 10, 30, 0x0000FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(50, 170, 10, 30, 0x0000FF)));
		
		wallByColor[2].push_back(AddObject(new ObjWall(40, 170, 10, 30, 0x00FFFF)));
		AddObject(new ObjAreaCounter(wallByColor[0], 370, 20, 30, 30, 2, 0xFF0000));
		AddObject(new ObjAreaCounter(wallByColor[1], 370, 70, 30, 30, 1, 0x0000FF));
		AddObject(new ObjAreaCounter(wallByColor[2], 370, 120, 30, 30, 1, 0x00FFFF));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 370, 170, 30, 30));
		AddObject(new ObjClickBox(wallByColor[0], 100, 240, 40, 40, 10, 1000, 0xFF0000));
		AddObject(new ObjClickBox(wallByColor[1], 170, 240, 40, 40, 10, 1000, 0x0000FF));
		AddObject(new ObjClickBox({}, 40, 290, 30, 10, 0, 1000, 0x0));
		AddObject(new ObjClickBox(wallByColor[2], 240, 240, 40, 40, 10, 1000, 0x00FFFF));
		AddObject(new ObjText(301, 268, 28, false, "for cheaters"));
		AddObject(new ObjWall(40, 0, 360, 20, 0x0));
		AddObject(new ObjWall(40, 50, 360, 20, 0x0));
		AddObject(new ObjWall(40, 100, 360, 20, 0x0));
		AddObject(new ObjWall(40, 150, 360, 20, 0x0));
		AddObject(new ObjWall(40, 200, 360, 20, 0x0));
		AddObject(new ObjWall(40, 20, 10, 20, 0x0));
		AddObject(new ObjWall(60, 40, 10, 10, 0x0));
		AddObject(new ObjWall(60, 30, 10, 20, 0x0));
		AddObject(new ObjWall(80, 20, 10, 20, 0x0));
		AddObject(new ObjWall(100, 40, 10, 10, 0x0));
		AddObject(new ObjWall(100, 30, 10, 10, 0x0));
		AddObject(new ObjWall(120, 20, 10, 20, 0x0));
		AddObject(new ObjWall(140, 40, 10, 10, 0x0));
		AddObject(new ObjWall(140, 30, 10, 20, 0x0));
		AddObject(new ObjWall(160, 20, 10, 20, 0x0));
		AddObject(new ObjWall(180, 40, 10, 20, 0x0));
		AddObject(new ObjWall(180, 30, 10, 20, 0x0));
		AddObject(new ObjWall(200, 20, 10, 20, 0x0));
		AddObject(new ObjWall(220, 40, 10, 10, 0x0));
		AddObject(new ObjWall(220, 30, 10, 20, 0x0));
		AddObject(new ObjWall(240, 20, 10, 20, 0x0));
		AddObject(new ObjWall(260, 40, 10, 20, 0x0));
		AddObject(new ObjWall(260, 30, 10, 20, 0x0));
		AddObject(new ObjWall(280, 20, 10, 20, 0x0));
		AddObject(new ObjWall(300, 40, 10, 20, 0x0));
		AddObject(new ObjWall(300, 30, 10, 20, 0x0));
		AddObject(new ObjWall(320, 20, 10, 20, 0x0));
		AddObject(new ObjWall(340, 30, 10, 20, 0x0));
		AddObject(new ObjWall(60, 80, 100, 10, 0x0));
		AddObject(new ObjWall(150, 70, 10, 20, 0x0));
		AddObject(new ObjWall(170, 100, 20, 10, 0x0));
		AddObject(new ObjWall(170, 80, 70, 10, 0x0));
		AddObject(new ObjWall(230, 90, 10, 20, 0x0));
		AddObject(new ObjWall(250, 80, 110, 10, 0x0));
		AddObject(new ObjWall(350, 90, 10, 20, 0x0));
		AddObject(new ObjWall(70, 120, 20, 20, 0x0));
		AddObject(new ObjWall(100, 130, 10, 10, 0x0));
		AddObject(new ObjWall(120, 120, 10, 10, 0x0));
		AddObject(new ObjWall(120, 140, 20, 10, 0x0));
		AddObject(new ObjWall(160, 130, 10, 10, 0x0));
		AddObject(new ObjWall(170, 120, 10, 10, 0x0));
		AddObject(new ObjWall(190, 140, 10, 10, 0x0));
		AddObject(new ObjWall(190, 120, 10, 10, 0x0));
		AddObject(new ObjWall(220, 130, 10, 10, 0x0));
		AddObject(new ObjWall(210, 140, 10, 10, 0x0));
		AddObject(new ObjWall(250, 120, 10, 10, 0x0));
		AddObject(new ObjWall(270, 140, 10, 10, 0x0));
		AddObject(new ObjWall(240, 140, 10, 10, 0x0));
		AddObject(new ObjWall(280, 120, 10, 10, 0x0));
		AddObject(new ObjWall(300, 140, 10, 10, 0x0));
		AddObject(new ObjWall(280, 140, 10, 10, 0x0));
		AddObject(new ObjWall(310, 120, 10, 10, 0x0));
		AddObject(new ObjWall(310, 140, 10, 10, 0x0));
		AddObject(new ObjWall(330, 140, 10, 10, 0x0));
		AddObject(new ObjWall(340, 130, 10, 10, 0x0));
		AddObject(new ObjWall(320, 120, 10, 10, 0x0));
		AddObject(new ObjWall(80, 190, 10, 10, 0x0));
		AddObject(new ObjWall(90, 180, 10, 10, 0x0));
		AddObject(new ObjWall(110, 170, 10, 10, 0x0));
		AddObject(new ObjWall(120, 180, 10, 10, 0x0));
		AddObject(new ObjWall(140, 190, 10, 10, 0x0));
		AddObject(new ObjWall(150, 180, 10, 10, 0x0));
		AddObject(new ObjWall(170, 170, 10, 10, 0x0));
		AddObject(new ObjWall(180, 180, 10, 10, 0x0));
		AddObject(new ObjWall(200, 190, 10, 10, 0x0));
		AddObject(new ObjWall(210, 180, 10, 10, 0x0));
		AddObject(new ObjWall(230, 170, 10, 10, 0x0));
		AddObject(new ObjWall(240, 180, 10, 10, 0x0));
		AddObject(new ObjWall(260, 190, 10, 10, 0x0));
		AddObject(new ObjWall(270, 180, 10, 10, 0x0));
		AddObject(new ObjWall(290, 170, 10, 10, 0x0));
		AddObject(new ObjWall(300, 180, 10, 10, 0x0));
		AddObject(new ObjWall(320, 190, 10, 10, 0x0));
		AddObject(new ObjWall(330, 180, 10, 10, 0x0));
		AddObject(new ObjWall(40, 210, 30, 80, 0x0));
		
	}
};

class LevelMedium4 : public Level {
public:
	LevelMedium4() : Level(170, 230) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[1];
		
		wallByColor[0].push_back(AddObject(new ObjWall(290, 60, 10, 20, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(320, 60, 10, 20, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(150, 220, 10, 30, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(180, 220, 10, 30, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(160, 240, 20, 10, 0xFFFFFF)));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 0, 0, 60, 60));
		AddObject(new ObjText(200, 25, 20, true, "Someone turned off the lights,"));
		AddObject(new ObjText(200, 35, 20, true, "sorry about that."));
		AddObject(new ObjWall(0, 60, 290, 20, 0x0));
		AddObject(new ObjWall(330, 60, 70, 20, 0x0));
		AddObject(new ObjWall(60, 80, 20, 20, 0x0));
		AddObject(new ObjWall(120, 80, 20, 40, 0x0));
		AddObject(new ObjWall(200, 80, 40, 20, 0x0));
		AddObject(new ObjWall(260, 80, 40, 20, 0x0));
		AddObject(new ObjWall(320, 80, 20, 60, 0x0));
		AddObject(new ObjWall(360, 80, 40, 20, 0x0));
		AddObject(new ObjWall(0, 100, 40, 20, 0x0));
		AddObject(new ObjWall(100, 100, 20, 20, 0x0));
		AddObject(new ObjWall(160, 100, 20, 100, 0x0));
		AddObject(new ObjWall(220, 100, 20, 40, 0x0));
		AddObject(new ObjWall(280, 100, 20, 80, 0x0));
		AddObject(new ObjWall(380, 100, 20, 40, 0x0));
		AddObject(new ObjWall(20, 120, 20, 20, 0x0));
		AddObject(new ObjWall(60, 120, 20, 60, 0x0));
		AddObject(new ObjWall(180, 120, 20, 20, 0x0));
		AddObject(new ObjWall(260, 120, 20, 20, 0x0));
		AddObject(new ObjWall(340, 120, 20, 20, 0x0));
		AddObject(new ObjWall(80, 140, 40, 20, 0x0));
		AddObject(new ObjWall(140, 140, 20, 20, 0x0));
		AddObject(new ObjWall(0, 160, 60, 20, 0x0));
		AddObject(new ObjWall(200, 160, 40, 20, 0x0));
		AddObject(new ObjWall(260, 160, 20, 20, 0x0));
		AddObject(new ObjWall(300, 160, 40, 20, 0x0));
		AddObject(new ObjWall(360, 160, 20, 80, 0x0));
		AddObject(new ObjWall(40, 180, 20, 40, 0x0));
		AddObject(new ObjWall(100, 180, 20, 80, 0x0));
		AddObject(new ObjWall(140, 180, 20, 20, 0x0));
		AddObject(new ObjWall(180, 180, 40, 20, 0x0));
		AddObject(new ObjWall(0, 200, 20, 20, 0x0));
		AddObject(new ObjWall(80, 200, 20, 20, 0x0));
		AddObject(new ObjWall(240, 200, 60, 20, 0x0));
		AddObject(new ObjWall(320, 200, 20, 80, 0x0));
		AddObject(new ObjWall(120, 220, 30, 20, 0x0));
		AddObject(new ObjWall(190, 220, 30, 20, 0x0));
		AddObject(new ObjWall(340, 220, 20, 20, 0x0));
		AddObject(new ObjWall(0, 240, 100, 20, 0x0));
		AddObject(new ObjWall(140, 240, 10, 20, 0x0));
		AddObject(new ObjWall(190, 240, 10, 20, 0x0));
		AddObject(new ObjWall(240, 240, 40, 20, 0x0));
		AddObject(new ObjWall(300, 240, 20, 20, 0x0));
		AddObject(new ObjWall(150, 250, 40, 10, 0x0));
		AddObject(new ObjWall(40, 260, 20, 20, 0x0));
		AddObject(new ObjWall(160, 260, 20, 20, 0x0));
		AddObject(new ObjWall(220, 260, 40, 20, 0x0));
		AddObject(new ObjWall(360, 260, 40, 20, 0x0));
		AddObject(new ObjWall(0, 280, 20, 20, 0x0));
		AddObject(new ObjWall(80, 280, 20, 20, 0x0));
		AddObject(new ObjWall(120, 280, 20, 20, 0x0));
		AddObject(new ObjWall(200, 280, 40, 20, 0x0));
		AddObject(new ObjWall(280, 280, 20, 20, 0x0));
		AddObject(new ObjClickBox({}, 0, 80, 400, 220, 0, 1000, 0x0));
		
	}
};

class LevelMedium5 : public Level {
public:
	LevelMedium5() : Level(200, 150) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[4];
		
		wallByColor[0].push_back(AddObject(new ObjWall(190, 170, 20, 10, 0x3333FF)));
		wallByColor[0].push_back(AddObject(new ObjWall(190, 240, 10, 20, 0x3333FF)));
		
		wallByColor[1].push_back(AddObject(new ObjWall(140, 190, 10, 30, 0xFF99FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(180, 240, 10, 20, 0xFF99FF)));
		
		wallByColor[2].push_back(AddObject(new ObjWall(160, 240, 10, 20, 0x99FFFF)));
		
		wallByColor[3].push_back(AddObject(new ObjWall(170, 240, 10, 20, 0xFFFF99)));
		AddObject(new ObjClickBox(wallByColor[0], 175, 185, 40, 40, 5, 1000, 0x3333FF));
		AddObject(new ObjClickBox(wallByColor[1], 235, 105, 40, 40, 5, 1000, 0xFF99FF));
		AddObject(new ObjClickBox(wallByColor[2], 45, 5, 40, 40, 5, 1000, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[3], 355, 255, 40, 40, 5, 1000, 0xFFFF99));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 240, 190, 50, 50));
		AddObject(new ObjWall(90, 0, 20, 10, 0x0));
		AddObject(new ObjWall(140, 0, 10, 20, 0x0));
		AddObject(new ObjWall(180, 0, 10, 20, 0x0));
		AddObject(new ObjWall(200, 0, 10, 10, 0x0));
		AddObject(new ObjWall(220, 0, 10, 30, 0x0));
		AddObject(new ObjWall(240, 0, 10, 10, 0x0));
		AddObject(new ObjWall(340, 0, 10, 10, 0x0));
		AddObject(new ObjWall(360, 0, 10, 30, 0x0));
		AddObject(new ObjWall(380, 0, 10, 10, 0x0));
		AddObject(new ObjWall(10, 10, 30, 10, 0x0));
		AddObject(new ObjWall(120, 10, 20, 10, 0x0));
		AddObject(new ObjWall(150, 10, 10, 10, 0x0));
		AddObject(new ObjWall(170, 10, 10, 30, 0x0));
		AddObject(new ObjWall(260, 10, 10, 20, 0x0));
		AddObject(new ObjWall(280, 10, 50, 10, 0x0));
		AddObject(new ObjWall(30, 20, 10, 20, 0x0));
		AddObject(new ObjWall(100, 20, 10, 70, 0x0));
		AddObject(new ObjWall(200, 20, 10, 80, 0x0));
		AddObject(new ObjWall(230, 20, 10, 30, 0x0));
		AddObject(new ObjWall(250, 20, 10, 10, 0x0));
		AddObject(new ObjWall(270, 20, 20, 10, 0x0));
		AddObject(new ObjWall(320, 20, 40, 10, 0x0));
		AddObject(new ObjWall(370, 20, 20, 10, 0x0));
		AddObject(new ObjWall(10, 30, 20, 10, 0x0));
		AddObject(new ObjWall(90, 30, 10, 10, 0x0));
		AddObject(new ObjWall(110, 30, 10, 10, 0x0));
		AddObject(new ObjWall(130, 30, 40, 10, 0x0));
		AddObject(new ObjWall(180, 30, 10, 10, 0x0));
		AddObject(new ObjWall(280, 30, 10, 20, 0x0));
		AddObject(new ObjWall(300, 30, 10, 40, 0x0));
		AddObject(new ObjWall(350, 30, 10, 60, 0x0));
		AddObject(new ObjWall(10, 40, 10, 60, 0x0));
		AddObject(new ObjWall(130, 40, 10, 40, 0x0));
		AddObject(new ObjWall(210, 40, 10, 10, 0x0));
		AddObject(new ObjWall(240, 40, 10, 10, 0x0));
		AddObject(new ObjWall(260, 40, 10, 30, 0x0));
		AddObject(new ObjWall(320, 40, 20, 10, 0x0));
		AddObject(new ObjWall(370, 40, 20, 10, 0x0));
		AddObject(new ObjWall(30, 50, 40, 10, 0x0));
		AddObject(new ObjWall(80, 50, 10, 20, 0x0));
		AddObject(new ObjWall(120, 50, 10, 10, 0x0));
		AddObject(new ObjWall(150, 50, 50, 10, 0x0));
		AddObject(new ObjWall(330, 50, 20, 10, 0x0));
		AddObject(new ObjWall(380, 50, 10, 20, 0x0));
		AddObject(new ObjWall(60, 60, 20, 10, 0x0));
		AddObject(new ObjWall(90, 60, 10, 10, 0x0));
		AddObject(new ObjWall(170, 60, 10, 20, 0x0));
		AddObject(new ObjWall(210, 60, 50, 10, 0x0));
		AddObject(new ObjWall(270, 60, 30, 10, 0x0));
		AddObject(new ObjWall(310, 60, 10, 30, 0x0));
		AddObject(new ObjWall(330, 60, 10, 100, 0x0));
		AddObject(new ObjWall(360, 60, 20, 10, 0x0));
		AddObject(new ObjWall(20, 70, 30, 10, 0x0));
		AddObject(new ObjWall(60, 70, 10, 30, 0x0));
		AddObject(new ObjWall(110, 70, 20, 10, 0x0));
		AddObject(new ObjWall(140, 70, 20, 10, 0x0));
		AddObject(new ObjWall(190, 70, 10, 10, 0x0));
		AddObject(new ObjWall(240, 70, 10, 10, 0x0));
		AddObject(new ObjWall(280, 70, 10, 10, 0x0));
		AddObject(new ObjWall(80, 80, 10, 100, 0x0));
		AddObject(new ObjWall(220, 80, 10, 20, 0x0));
		AddObject(new ObjWall(260, 80, 10, 20, 0x0));
		AddObject(new ObjWall(300, 80, 10, 30, 0x0));
		AddObject(new ObjWall(360, 80, 10, 10, 0x0));
		AddObject(new ObjWall(380, 80, 20, 10, 0x0));
		AddObject(new ObjWall(20, 90, 10, 20, 0x0));
		AddObject(new ObjWall(40, 90, 20, 10, 0x0));
		AddObject(new ObjWall(120, 90, 80, 10, 0x0));
		AddObject(new ObjWall(210, 90, 10, 10, 0x0));
		AddObject(new ObjWall(230, 90, 30, 10, 0x0));
		AddObject(new ObjWall(270, 90, 20, 10, 0x0));
		AddObject(new ObjWall(40, 100, 10, 40, 0x0));
		AddObject(new ObjWall(90, 100, 40, 10, 0x0));
		AddObject(new ObjWall(160, 100, 10, 10, 0x0));
		AddObject(new ObjWall(180, 100, 10, 80, 0x0));
		AddObject(new ObjWall(280, 100, 10, 60, 0x0));
		AddObject(new ObjWall(320, 100, 10, 20, 0x0));
		AddObject(new ObjWall(340, 100, 50, 10, 0x0));
		AddObject(new ObjWall(0, 110, 10, 10, 0x0));
		AddObject(new ObjWall(60, 110, 20, 10, 0x0));
		AddObject(new ObjWall(120, 110, 10, 20, 0x0));
		AddObject(new ObjWall(140, 110, 10, 60, 0x0));
		AddObject(new ObjWall(20, 120, 20, 10, 0x0));
		AddObject(new ObjWall(100, 120, 10, 30, 0x0));
		AddObject(new ObjWall(150, 120, 20, 10, 0x0));
		AddObject(new ObjWall(210, 120, 20, 10, 0x0));
		AddObject(new ObjWall(290, 120, 20, 10, 0x0));
		AddObject(new ObjWall(350, 120, 20, 10, 0x0));
		AddObject(new ObjWall(380, 120, 10, 30, 0x0));
		AddObject(new ObjWall(10, 130, 20, 10, 0x0));
		AddObject(new ObjWall(50, 130, 20, 10, 0x0));
		AddObject(new ObjWall(220, 130, 10, 110, 0x0));
		AddObject(new ObjWall(300, 130, 20, 10, 0x0));
		AddObject(new ObjWall(360, 130, 10, 40, 0x0));
		AddObject(new ObjWall(20, 140, 10, 60, 0x0));
		AddObject(new ObjWall(110, 140, 30, 10, 0x0));
		AddObject(new ObjWall(160, 140, 20, 10, 0x0));
		AddObject(new ObjWall(340, 140, 10, 10, 0x0));
		AddObject(new ObjWall(370, 140, 10, 10, 0x0));
		AddObject(new ObjWall(0, 150, 10, 10, 0x0));
		AddObject(new ObjWall(30, 150, 20, 10, 0x0));
		AddObject(new ObjWall(60, 150, 20, 10, 0x0));
		AddObject(new ObjWall(240, 150, 40, 10, 0x0));
		AddObject(new ObjWall(300, 150, 30, 10, 0x0));
		AddObject(new ObjWall(100, 160, 30, 10, 0x0));
		AddObject(new ObjWall(150, 160, 20, 10, 0x0));
		AddObject(new ObjWall(260, 160, 10, 10, 0x0));
		AddObject(new ObjWall(300, 160, 10, 110, 0x0));
		AddObject(new ObjWall(350, 160, 10, 30, 0x0));
		AddObject(new ObjWall(380, 160, 20, 10, 0x0));
		AddObject(new ObjWall(10, 170, 10, 10, 0x0));
		AddObject(new ObjWall(40, 170, 30, 10, 0x0));
		AddObject(new ObjWall(90, 170, 20, 10, 0x0));
		AddObject(new ObjWall(160, 170, 10, 70, 0x0));
		AddObject(new ObjWall(210, 170, 10, 10, 0x0));
		AddObject(new ObjWall(230, 170, 20, 10, 0x0));
		AddObject(new ObjWall(280, 170, 20, 10, 0x0));
		AddObject(new ObjWall(320, 170, 10, 20, 0x0));
		AddObject(new ObjWall(60, 180, 10, 20, 0x0));
		AddObject(new ObjWall(100, 180, 50, 10, 0x0));
		AddObject(new ObjWall(240, 180, 50, 10, 0x0));
		AddObject(new ObjWall(310, 180, 10, 10, 0x0));
		AddObject(new ObjWall(340, 180, 10, 30, 0x0));
		AddObject(new ObjWall(370, 180, 20, 10, 0x0));
		AddObject(new ObjWall(10, 190, 10, 50, 0x0));
		AddObject(new ObjWall(30, 190, 20, 10, 0x0));
		AddObject(new ObjWall(70, 190, 20, 10, 0x0));
		AddObject(new ObjWall(120, 190, 10, 40, 0x0));
		AddObject(new ObjWall(380, 190, 10, 40, 0x0));
		AddObject(new ObjWall(80, 200, 30, 10, 0x0));
		AddObject(new ObjWall(320, 200, 20, 10, 0x0));
		AddObject(new ObjWall(350, 200, 20, 10, 0x0));
		AddObject(new ObjWall(30, 210, 40, 10, 0x0));
		AddObject(new ObjWall(90, 210, 10, 30, 0x0));
		AddObject(new ObjWall(350, 210, 10, 40, 0x0));
		AddObject(new ObjWall(40, 220, 10, 20, 0x0));
		AddObject(new ObjWall(60, 220, 20, 10, 0x0));
		AddObject(new ObjWall(100, 220, 20, 10, 0x0));
		AddObject(new ObjWall(140, 220, 10, 50, 0x0));
		AddObject(new ObjWall(310, 220, 30, 10, 0x0));
		AddObject(new ObjWall(360, 220, 20, 10, 0x0));
		AddObject(new ObjWall(20, 230, 20, 10, 0x0));
		AddObject(new ObjWall(70, 230, 10, 30, 0x0));
		AddObject(new ObjWall(170, 230, 50, 10, 0x0));
		AddObject(new ObjWall(110, 240, 20, 10, 0x0));
		AddObject(new ObjWall(320, 240, 30, 10, 0x0));
		AddObject(new ObjWall(360, 240, 10, 10, 0x0));
		AddObject(new ObjWall(380, 240, 20, 10, 0x0));
		AddObject(new ObjWall(0, 250, 60, 10, 0x0));
		AddObject(new ObjWall(80, 250, 40, 10, 0x0));
		AddObject(new ObjWall(340, 250, 10, 50, 0x0));
		AddObject(new ObjWall(110, 260, 30, 10, 0x0));
		AddObject(new ObjWall(160, 260, 140, 10, 0x0));
		AddObject(new ObjWall(310, 260, 20, 10, 0x0));
		AddObject(new ObjWall(10, 270, 90, 10, 0x0));
		AddObject(new ObjWall(120, 270, 10, 20, 0x0));
		AddObject(new ObjWall(180, 270, 10, 20, 0x0));
		AddObject(new ObjWall(270, 270, 10, 10, 0x0));
		AddObject(new ObjWall(290, 270, 10, 20, 0x0));
		AddObject(new ObjWall(10, 280, 10, 10, 0x0));
		AddObject(new ObjWall(50, 280, 10, 10, 0x0));
		AddObject(new ObjWall(90, 280, 30, 10, 0x0));
		AddObject(new ObjWall(140, 280, 30, 10, 0x0));
		AddObject(new ObjWall(200, 280, 40, 10, 0x0));
		AddObject(new ObjWall(250, 280, 10, 20, 0x0));
		AddObject(new ObjWall(310, 280, 20, 10, 0x0));
		AddObject(new ObjWall(30, 290, 10, 10, 0x0));
		AddObject(new ObjWall(70, 290, 10, 10, 0x0));
		AddObject(new ObjWall(140, 290, 10, 10, 0x0));
		AddObject(new ObjWall(210, 290, 10, 10, 0x0));
		AddObject(new ObjWall(270, 290, 10, 10, 0x0));
		AddObject(new ObjWall(310, 290, 10, 10, 0x0));
		
	}
};

class LevelMedium6 : public Level { // Made by Python
public:
	LevelMedium6() : Level(200, 10){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(30, 0, 160, 10, 0x000000));
		AddObject(new ObjWall(210, 0, 160, 10, 0x000000));
		AddObject(new ObjWall(60, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(100, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(140, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(180, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(330, 10, 10, 10, 0x000000));
		AddObject(new ObjWall(40, 20, 10, 130, 0x000000));
		AddObject(new ObjWall(80, 20, 10, 130, 0x000000));
		AddObject(new ObjWall(120, 20, 10, 130, 0x000000));
		AddObject(new ObjWall(160, 20, 10, 110, 0x000000));
		AddObject(new ObjWall(230, 20, 10, 110, 0x000000));
		AddObject(new ObjWall(270, 20, 10, 110, 0x000000));
		AddObject(new ObjWall(310, 20, 10, 110, 0x000000));
		AddObject(new ObjWall(350, 20, 10, 110, 0x000000));
		AddObject(new ObjWall(0, 30, 10, 240, 0x000000));
		AddObject(new ObjWall(30, 30, 10, 100, 0x000000));
		AddObject(new ObjWall(50, 30, 30, 100, 0x000000));
		AddObject(new ObjWall(90, 30, 30, 100, 0x000000));
		AddObject(new ObjWall(130, 30, 30, 100, 0x000000));
		AddObject(new ObjWall(170, 30, 20, 90, 0x000000));
		AddObject(new ObjWall(200, 30, 30, 10, 0x000000));
		AddObject(new ObjWall(240, 30, 30, 100, 0x000000));
		AddObject(new ObjWall(280, 30, 30, 100, 0x000000));
		AddObject(new ObjWall(320, 30, 30, 100, 0x000000));
		AddObject(new ObjWall(360, 30, 10, 100, 0x000000));
		AddObject(new ObjWall(390, 30, 10, 240, 0x000000));
		AddObject(new ObjWall(220, 40, 10, 80, 0x000000));
		AddObject(new ObjWall(380, 40, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 50, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 50, 20, 10, 0x000000));
		AddObject(new ObjWall(370, 60, 10, 10, 0x000000));
		AddObject(new ObjWall(20, 70, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(190, 80, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(380, 80, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 90, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(190, 90, 30, 10, 0x99FFFF)));
		wallByColor[5].push_back(AddObject(new ObjWall(190, 100, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(370, 100, 10, 10, 0x000000));
		AddObject(new ObjWall(20, 110, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 110, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(170, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(380, 120, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 130, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(140, 130, 10, 30, 0x3333FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(150, 130, 10, 30, 0x99FFFF)));
		wallByColor[5].push_back(AddObject(new ObjWall(160, 130, 10, 30, 0xFF99FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(170, 130, 10, 30, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(230, 130, 10, 30, 0xFF9999)));
		wallByColor[5].push_back(AddObject(new ObjWall(240, 130, 10, 30, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(250, 130, 10, 30, 0x99FFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(260, 130, 10, 30, 0x3333FF)));
		AddObject(new ObjWall(300, 130, 10, 20, 0x000000));
		AddObject(new ObjWall(340, 130, 10, 20, 0x000000));
		AddObject(new ObjWall(60, 140, 10, 130, 0x000000));
		AddObject(new ObjWall(100, 140, 10, 130, 0x000000));
		AddObject(new ObjWall(280, 140, 10, 140, 0x000000));
		AddObject(new ObjWall(320, 140, 10, 140, 0x000000));
		AddObject(new ObjWall(360, 140, 20, 10, 0x000000));
		AddObject(new ObjWall(20, 150, 10, 10, 0x000000));
		AddObject(new ObjWall(360, 150, 10, 120, 0x000000));
		AddObject(new ObjWall(30, 160, 30, 110, 0x000000));
		AddObject(new ObjWall(70, 160, 30, 110, 0x000000));
		AddObject(new ObjWall(110, 160, 70, 110, 0x000000));
		AddObject(new ObjWall(230, 160, 50, 110, 0x000000));
		AddObject(new ObjWall(290, 160, 30, 110, 0x000000));
		AddObject(new ObjWall(330, 160, 30, 110, 0x000000));
		AddObject(new ObjWall(380, 160, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 170, 10, 10, 0x000000));
		AddObject(new ObjWall(180, 170, 10, 100, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 170, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(220, 170, 10, 100, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(190, 180, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(370, 180, 10, 10, 0x000000));
		AddObject(new ObjWall(20, 190, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(190, 190, 30, 10, 0x99FFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(190, 200, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(380, 200, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 210, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 220, 20, 10, 0x000000));
		AddObject(new ObjWall(370, 220, 10, 10, 0x000000));
		AddObject(new ObjWall(20, 230, 10, 10, 0x000000));
		AddObject(new ObjWall(200, 240, 20, 10, 0x000000));
		AddObject(new ObjWall(380, 240, 10, 10, 0x000000));
		AddObject(new ObjWall(10, 250, 10, 10, 0x000000));
		AddObject(new ObjWall(190, 260, 20, 10, 0x000000));
		AddObject(new ObjWall(40, 270, 10, 10, 0x000000));
		AddObject(new ObjWall(80, 270, 10, 10, 0x000000));
		AddObject(new ObjWall(120, 270, 10, 10, 0x000000));
		AddObject(new ObjWall(160, 270, 10, 10, 0x000000));
		AddObject(new ObjWall(200, 270, 10, 10, 0x000000));
		AddObject(new ObjWall(240, 270, 10, 10, 0x000000));
		AddObject(new ObjWall(60, 280, 10, 20, 0x000000));
		AddObject(new ObjWall(100, 280, 10, 20, 0x000000));
		AddObject(new ObjWall(140, 280, 10, 20, 0x000000));
		AddObject(new ObjWall(180, 280, 10, 20, 0x000000));
		AddObject(new ObjWall(220, 280, 10, 20, 0x000000));
		AddObject(new ObjWall(260, 280, 10, 20, 0x000000));
		AddObject(new ObjWall(300, 280, 10, 20, 0x000000));
		AddObject(new ObjWall(340, 280, 10, 20, 0x000000));
		AddObject(new ObjWall(30, 290, 30, 10, 0x000000));
		AddObject(new ObjWall(70, 290, 30, 10, 0x000000));
		AddObject(new ObjWall(110, 290, 30, 10, 0x000000));
		AddObject(new ObjWall(150, 290, 30, 10, 0x000000));
		AddObject(new ObjWall(190, 290, 30, 10, 0x000000));
		AddObject(new ObjWall(230, 290, 30, 10, 0x000000));
		AddObject(new ObjWall(270, 290, 30, 10, 0x000000));
		AddObject(new ObjWall(310, 290, 30, 10, 0x000000));
		AddObject(new ObjWall(350, 290, 20, 10, 0x000000));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 180, 120, 50, 50));
		AddObject(new ObjClickBox(wallByColor[4], 0, 0, 35, 35, 5, 1000, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[5], 365, 0, 35, 35, 5, 1000, 0xFF99FF));
		AddObject(new ObjClickBox(wallByColor[6], 365, 265, 35, 35, 5, 1000, 0x3333FF));
		AddObject(new ObjClickBox(wallByColor[1], 0, 265, 35, 35, 5, 1000, 0xFF9999));
	}
};

class LevelMedium7 : public Level {
public:
	LevelMedium7() : Level(380, 20){}

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

class LevelMedium8 : public Level {
public:
	LevelMedium8() : Level(200, 270){}

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

class LevelMedium9 : public Level {
public:
	LevelMedium9() : Level(4, 149){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		AddObject(new ObjWall(70, 0, 10, 40, 0x000000));
		AddObject(new ObjWall(110, 0, 10, 40, 0x000000));
		AddObject(new ObjWall(150, 0, 10, 40, 0x000000));
		AddObject(new ObjWall(240, 0, 10, 40, 0x000000));
		AddObject(new ObjWall(280, 0, 10, 40, 0x000000));
		AddObject(new ObjWall(320, 0, 10, 40, 0x000000));
		AddObject(new ObjWall(30, 10, 10, 30, 0x000000));
		AddObject(new ObjWall(50, 10, 10, 50, 0x000000));
		AddObject(new ObjWall(90, 10, 10, 50, 0x000000));
		AddObject(new ObjWall(130, 10, 10, 50, 0x000000));
		AddObject(new ObjWall(170, 10, 10, 30, 0x000000));
		AddObject(new ObjWall(220, 10, 10, 30, 0x000000));
		AddObject(new ObjWall(260, 10, 10, 50, 0x000000));
		AddObject(new ObjWall(300, 10, 10, 50, 0x000000));
		AddObject(new ObjWall(340, 10, 10, 50, 0x000000));
		AddObject(new ObjWall(360, 10, 10, 30, 0x000000));
		AddObject(new ObjWall(0, 30, 30, 10, 0x000000));
		AddObject(new ObjWall(180, 30, 40, 10, 0x000000));
		AddObject(new ObjWall(370, 30, 30, 10, 0x000000));
		AddObject(new ObjWall(10, 50, 40, 10, 0x000000));
		AddObject(new ObjWall(60, 50, 30, 10, 0x000000));
		AddObject(new ObjWall(100, 50, 30, 10, 0x000000));
		AddObject(new ObjWall(140, 50, 120, 10, 0x000000));
		AddObject(new ObjWall(270, 50, 30, 10, 0x000000));
		AddObject(new ObjWall(310, 50, 30, 10, 0x000000));
		AddObject(new ObjWall(350, 50, 50, 10, 0x000000));
		AddObject(new ObjWall(0, 70, 390, 10, 0x000000));
		AddObject(new ObjWall(10, 90, 390, 10, 0x000000));
		AddObject(new ObjWall(0, 110, 390, 10, 0x000000));
		AddObject(new ObjWall(10, 130, 390, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(10, 140, 10, 20, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(20, 140, 10, 20, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(30, 140, 10, 20, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(40, 140, 10, 20, 0xFFFF99)));
		wallByColor[2].push_back(AddObject(new ObjWall(50, 140, 10, 20, 0x9999FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(60, 140, 10, 20, 0xFF9999)));
		AddObject(new ObjWall(90, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(130, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(170, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(210, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(250, 140, 10, 10, 0x000000));
		AddObject(new ObjWall(290, 140, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(320, 140, 10, 20, 0x3333FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(330, 140, 10, 20, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(340, 140, 10, 20, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(350, 140, 10, 20, 0xFFFF99)));
		wallByColor[2].push_back(AddObject(new ObjWall(360, 140, 10, 20, 0x9999FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(370, 140, 10, 20, 0xFF9999)));
		AddObject(new ObjWall(70, 150, 10, 20, 0x000000));
		AddObject(new ObjWall(110, 150, 10, 20, 0x000000));
		AddObject(new ObjWall(150, 150, 10, 20, 0x000000));
		AddObject(new ObjWall(190, 150, 10, 20, 0x000000));
		AddObject(new ObjWall(230, 150, 10, 20, 0x000000));
		AddObject(new ObjWall(270, 150, 10, 20, 0x000000));
		AddObject(new ObjWall(310, 150, 10, 20, 0x000000));
		AddObject(new ObjWall(10, 160, 60, 10, 0x000000));
		AddObject(new ObjWall(80, 160, 30, 10, 0x000000));
		AddObject(new ObjWall(120, 160, 30, 10, 0x000000));
		AddObject(new ObjWall(160, 160, 30, 10, 0x000000));
		AddObject(new ObjWall(200, 160, 30, 10, 0x000000));
		AddObject(new ObjWall(240, 160, 30, 10, 0x000000));
		AddObject(new ObjWall(280, 160, 30, 10, 0x000000));
		AddObject(new ObjWall(320, 160, 80, 10, 0x000000));
		AddObject(new ObjWall(0, 180, 390, 10, 0x000000));
		AddObject(new ObjWall(10, 200, 390, 10, 0x000000));
		AddObject(new ObjWall(0, 220, 390, 10, 0x000000));
		AddObject(new ObjWall(10, 240, 390, 10, 0x000000));
		AddObject(new ObjWall(50, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(90, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(130, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(260, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(300, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(340, 250, 10, 40, 0x000000));
		AddObject(new ObjWall(0, 260, 40, 10, 0x000000));
		AddObject(new ObjWall(70, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(110, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(150, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(170, 260, 60, 10, 0x000000));
		AddObject(new ObjWall(240, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(280, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(320, 260, 10, 40, 0x000000));
		AddObject(new ObjWall(360, 260, 40, 10, 0x000000));
		AddObject(new ObjWall(30, 270, 10, 20, 0x000000));
		AddObject(new ObjWall(170, 270, 10, 20, 0x000000));
		AddObject(new ObjWall(220, 270, 10, 20, 0x000000));
		AddObject(new ObjWall(360, 270, 10, 20, 0x000000));
		AddObject(new ObjClickBox(wallByColor[6], 0, 275, 25, 25, 5, 1000, 0x3333FF));
		AddObject(new ObjClickBox(wallByColor[5], 0, 0, 25, 25, 5, 1000, 0xFF99FF));
		AddObject(new ObjClickBox(wallByColor[4], 375, 0, 25, 25, 5, 1000, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[3], 375, 275, 25, 25, 5, 1000, 0xFFFF99));
		AddObject(new ObjClickBox(wallByColor[2], 185, 0, 25, 25, 5, 1000, 0x9999FF));
		AddObject(new ObjClickBox(wallByColor[1], 185, 275, 25, 25, 5, 1000, 0xFF9999));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 380, 140, 20, 20));
	}
};



class LevelSM1 : public Level {
public:
	LevelSM1() : Level(200, 280) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[0];
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 340, 10, 50, 20));
		AddObject(new ObjTeleport(0, 0, 400, 10));
		AddObject(new ObjTeleport(0, 10, 140, 290));
		AddObject(new ObjTeleport(390, 10, 10, 290));
		AddObject(new ObjTeleport(260, 30, 130, 270));
		AddObject(new ObjWall(180, 260, 40, 10, 0x0));
		AddObject(new ObjWall(180, 270, 10, 20, 0x0));
		AddObject(new ObjWall(210, 270, 10, 20, 0x0));
		
	}
};

class LevelSM2 : public Level {
public:
	LevelSM2() : Level(360, 25) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[0];
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 20, 270, 50, 20));
		AddObject(new ObjTeleport(0, 0, 400, 10));
		AddObject(new ObjTeleport(0, 10, 20, 290));
		AddObject(new ObjTeleport(380, 10, 20, 290));
		AddObject(new ObjTeleport(50, 40, 330, 40));
		AddObject(new ObjTeleport(20, 110, 330, 40));
		AddObject(new ObjTeleport(50, 180, 330, 30));
		AddObject(new ObjTeleport(20, 240, 330, 30));
		AddObject(new ObjTeleport(20, 290, 360, 10));
		AddObject(new ObjWall(370, 20, 10, 20, 0x0));
		AddObject(new ObjWall(340, 30, 30, 10, 0x0));
		AddObject(new ObjWall(340, 10, 40, 10, 0x0));
		
	}
};

class LevelSM3 : public Level {
public:
	LevelSM3() : Level(30, 280) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[0];
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 190, 10, 30, 40));
		AddObject(new ObjTeleport(0, 0, 400, 10));
		AddObject(new ObjTeleport(0, 10, 190, 60));
		AddObject(new ObjTeleport(220, 10, 180, 210));
		AddObject(new ObjTeleport(190, 50, 10, 20));
		AddObject(new ObjTeleport(210, 50, 10, 170));
		AddObject(new ObjTeleport(0, 70, 180, 60));
		AddObject(new ObjTeleport(190, 80, 20, 10));
		AddObject(new ObjTeleport(180, 100, 20, 30));
		AddObject(new ObjTeleport(0, 130, 20, 130));
		AddObject(new ObjTeleport(190, 140, 20, 80));
		AddObject(new ObjTeleport(50, 150, 140, 70));
		AddObject(new ObjTeleport(380, 220, 20, 80));
		AddObject(new ObjTeleport(20, 250, 340, 10));
		AddObject(new ObjTeleport(0, 260, 10, 40));
		AddObject(new ObjTeleport(50, 260, 310, 10));
		AddObject(new ObjTeleport(50, 290, 330, 10));
		AddObject(new ObjWall(10, 260, 40, 10, 0x0));
		AddObject(new ObjWall(10, 270, 10, 30, 0x0));
		AddObject(new ObjWall(20, 290, 30, 10, 0x0));
		
	}
};

class LevelSM4 : public Level {
public:
	LevelSM4() : Level(210, 30) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[0];
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 320, 250, 50, 40));
		AddObject(new ObjTeleport(0, 0, 180, 150));
		AddObject(new ObjTeleport(220, 0, 180, 10));
		AddObject(new ObjTeleport(230, 10, 170, 50));
		AddObject(new ObjTeleport(220, 50, 10, 10));
		AddObject(new ObjTeleport(340, 60, 60, 190));
		AddObject(new ObjTeleport(180, 80, 140, 70));
		AddObject(new ObjTeleport(0, 150, 140, 10));
		AddObject(new ObjTeleport(290, 150, 30, 40));
		AddObject(new ObjTeleport(0, 160, 20, 140));
		AddObject(new ObjTeleport(30, 170, 110, 60));
		AddObject(new ObjTeleport(140, 180, 130, 50));
		AddObject(new ObjTeleport(270, 210, 70, 40));
		AddObject(new ObjTeleport(30, 230, 20, 20));
		AddObject(new ObjTeleport(150, 230, 120, 30));
		AddObject(new ObjTeleport(60, 240, 70, 60));
		AddObject(new ObjTeleport(270, 250, 50, 10));
		AddObject(new ObjTeleport(370, 250, 30, 50));
		AddObject(new ObjTeleport(20, 260, 40, 40));
		AddObject(new ObjTeleport(130, 280, 190, 20));
		AddObject(new ObjTeleport(320, 290, 50, 10));
		AddObject(new ObjWall(190, 10, 40, 10, 0x0));
		AddObject(new ObjWall(220, 20, 10, 30, 0x0));
		AddObject(new ObjWall(190, 40, 30, 10, 0x0));
		
	}
};

class LevelSM5 : public Level {
public:
	LevelSM5() : Level(340, 265) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[0];
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 60, 160, 30, 30));
		AddObject(new ObjTeleport(0, 0, 400, 10));
		AddObject(new ObjTeleport(0, 10, 10, 290));
		AddObject(new ObjTeleport(90, 10, 90, 80));
		AddObject(new ObjTeleport(360, 10, 40, 230));
		AddObject(new ObjTeleport(200, 30, 140, 20));
		AddObject(new ObjTeleport(30, 40, 40, 120));
		AddObject(new ObjTeleport(200, 50, 80, 110));
		AddObject(new ObjTeleport(300, 70, 60, 70));
		AddObject(new ObjTeleport(70, 130, 130, 30));
		AddObject(new ObjTeleport(350, 140, 10, 100));
		AddObject(new ObjTeleport(30, 160, 30, 90));
		AddObject(new ObjTeleport(90, 160, 60, 10));
		AddObject(new ObjTeleport(210, 160, 20, 10));
		AddObject(new ObjTeleport(270, 160, 60, 10));
		AddObject(new ObjTeleport(130, 170, 20, 10));
		AddObject(new ObjTeleport(160, 170, 20, 80));
		AddObject(new ObjTeleport(90, 180, 20, 70));
		AddObject(new ObjTeleport(180, 180, 20, 70));
		AddObject(new ObjTeleport(240, 180, 20, 70));
		AddObject(new ObjTeleport(60, 190, 30, 60));
		AddObject(new ObjTeleport(110, 190, 50, 60));
		AddObject(new ObjTeleport(200, 190, 40, 60));
		AddObject(new ObjTeleport(260, 190, 90, 50));
		AddObject(new ObjTeleport(260, 240, 40, 10));
		AddObject(new ObjTeleport(380, 240, 20, 60));
		AddObject(new ObjTeleport(10, 280, 290, 20));
		AddObject(new ObjTeleport(300, 290, 80, 10));
		AddObject(new ObjWall(320, 250, 40, 10, 0x0));
		AddObject(new ObjWall(350, 260, 10, 20, 0x0));
		AddObject(new ObjWall(320, 270, 30, 10, 0x0));
		
	}
};




class LevelHard1 : public Level { /* Mazewall */
public:
	LevelHard1() : Level(205, 152) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[6];
		
		wallByColor[0].push_back(AddObject(new ObjWall(170, 50, 60, 20, 0x3333FF)));
		
		wallByColor[1].push_back(AddObject(new ObjWall(170, 70, 60, 20, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(380, 100, 20, 30, 0xFF9999)));
		
		wallByColor[2].push_back(AddObject(new ObjWall(170, 90, 60, 20, 0x99FFFF)));
		wallByColor[2].push_back(AddObject(new ObjWall(380, 150, 20, 30, 0x99FFFF)));
		
		wallByColor[3].push_back(AddObject(new ObjWall(0, 100, 20, 30, 0x9999FF)));
		
		wallByColor[4].push_back(AddObject(new ObjWall(170, 110, 60, 20, 0xFFFF99)));
		wallByColor[4].push_back(AddObject(new ObjWall(0, 150, 20, 30, 0xFFFF99)));
		
		wallByColor[5].push_back(AddObject(new ObjWall(170, 180, 60, 20, 0xFFFFFF)));
		AddObject(new ObjAreaCounter(wallByColor[5], 162, 0, 12, 10, 1, 0xFFFFFF));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 180, 10, 40, 30));
		AddObject(new ObjClickBox(wallByColor[1], 85, 35, 40, 50, 5, 1000, 0xFF9999));
		AddObject(new ObjClickBox(wallByColor[4], 275, 35, 40, 50, 5, 1000, 0xFFFF99));
		AddObject(new ObjClickBox(wallByColor[2], 85, 255, 70, 40, 5, 1000, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[0], 245, 255, 70, 40, 5, 1000, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[3], 140, 130, 130, 50, 1, 0x9999FF));
		AddObject(new ObjClickBox(wallByColor[1], 285, 215, 20, 20, 5, 1000, 0xFF9999));
		AddObject(new ObjClickBox(wallByColor[4], 265, 215, 20, 20, 5, 1000, 0xFFFF99));
		AddObject(new ObjClickBox(wallByColor[2], 245, 215, 20, 20, 5, 1000, 0x99FFFF));
		AddObject(new ObjClickBox(wallByColor[0], 225, 215, 20, 20, 5, 1000, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 90, 200, 20, 20, 1, 0xFFFFFF));
		AddObject(new ObjWall(160, 0, 10, 130, 0x0));
		AddObject(new ObjWall(230, 0, 10, 130, 0x0));
		AddObject(new ObjWall(20, 20, 120, 10, 0x0));
		AddObject(new ObjWall(260, 20, 120, 10, 0x0));
		AddObject(new ObjWall(20, 30, 10, 100, 0x0));
		AddObject(new ObjWall(130, 30, 10, 70, 0x0));
		AddObject(new ObjWall(260, 30, 10, 70, 0x0));
		AddObject(new ObjWall(370, 30, 10, 100, 0x0));
		AddObject(new ObjWall(50, 50, 30, 50, 0x0));
		AddObject(new ObjWall(320, 50, 30, 50, 0x0));
		AddObject(new ObjWall(80, 90, 50, 10, 0x0));
		AddObject(new ObjWall(270, 90, 50, 10, 0x0));
		AddObject(new ObjWall(30, 120, 130, 10, 0x0));
		AddObject(new ObjWall(240, 120, 130, 10, 0x0));
		AddObject(new ObjWall(20, 150, 120, 10, 0x0));
		AddObject(new ObjWall(270, 150, 110, 10, 0x0));
		AddObject(new ObjWall(20, 160, 10, 120, 0x0));
		AddObject(new ObjWall(80, 160, 60, 40, 0x0));
		AddObject(new ObjWall(270, 160, 50, 40, 0x0));
		AddObject(new ObjWall(370, 160, 10, 120, 0x0));
		AddObject(new ObjWall(50, 180, 10, 120, 0x0));
		AddObject(new ObjWall(140, 180, 30, 20, 0x0));
		AddObject(new ObjWall(230, 180, 40, 20, 0x0));
		AddObject(new ObjWall(340, 180, 10, 120, 0x0));
		AddObject(new ObjWall(80, 200, 10, 50, 0x0));
		AddObject(new ObjWall(310, 200, 10, 50, 0x0));
		AddObject(new ObjWall(90, 240, 220, 10, 0x0));
		AddObject(new ObjWall(160, 250, 80, 50, 0x0));
		
	}
};

class LevelHard2 : public Level {
public:
	LevelHard2() : Level(15, 285){}

	void OnInit(){
		std::vector<LevelObject*> wallByColor[7];
		wallByColor[2].push_back(AddObject(new ObjWall(30, 0, 10, 20, 0x9999FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(70, 0, 10, 20, 0x3333FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(110, 0, 10, 20, 0x99FFFF)));
		wallByColor[2].push_back(AddObject(new ObjWall(150, 0, 10, 20, 0x9999FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(190, 0, 10, 20, 0x99FFFF)));
		wallByColor[5].push_back(AddObject(new ObjWall(230, 0, 10, 20, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(270, 0, 10, 20, 0x99FFFF)));
		wallByColor[6].push_back(AddObject(new ObjWall(310, 0, 10, 20, 0x3333FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(350, 0, 10, 20, 0xFF9999)));
		AddObject(new ObjWall(390, 0, 10, 300, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(0, 20, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(30, 20, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(40, 20, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(70, 20, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(80, 20, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(110, 20, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(120, 20, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(150, 20, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(160, 20, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(190, 20, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(200, 20, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(230, 20, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(240, 20, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(270, 20, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(280, 20, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(310, 20, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(320, 20, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(350, 20, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(360, 20, 30, 10, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(30, 30, 10, 30, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(70, 30, 10, 30, 0xFFFF99)));
		wallByColor[4].push_back(AddObject(new ObjWall(110, 30, 10, 30, 0x99FFFF)));
		wallByColor[5].push_back(AddObject(new ObjWall(150, 30, 10, 30, 0xFF99FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 30, 10, 30, 0xFF9999)));
		wallByColor[5].push_back(AddObject(new ObjWall(230, 30, 10, 30, 0xFF99FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(270, 30, 10, 30, 0xFFFF99)));
		wallByColor[4].push_back(AddObject(new ObjWall(310, 30, 10, 30, 0x99FFFF)));
		wallByColor[1].push_back(AddObject(new ObjWall(350, 30, 10, 30, 0xFF9999)));
		wallByColor[4].push_back(AddObject(new ObjWall(0, 60, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(30, 60, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(40, 60, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(70, 60, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(80, 60, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(110, 60, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(120, 60, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(150, 60, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(160, 60, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(190, 60, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(200, 60, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(230, 60, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(240, 60, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(270, 60, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(280, 60, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(310, 60, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(320, 60, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(350, 60, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(360, 60, 30, 10, 0x99FFFF)));
		wallByColor[2].push_back(AddObject(new ObjWall(30, 70, 10, 30, 0x9999FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(70, 70, 10, 30, 0xFF99FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(110, 70, 10, 30, 0xFFFF99)));
		wallByColor[2].push_back(AddObject(new ObjWall(150, 70, 10, 30, 0x9999FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(190, 70, 10, 30, 0x3333FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(230, 70, 10, 30, 0x99FFFF)));
		wallByColor[5].push_back(AddObject(new ObjWall(270, 70, 10, 30, 0xFF99FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(310, 70, 10, 30, 0xFFFF99)));
		wallByColor[3].push_back(AddObject(new ObjWall(350, 70, 10, 30, 0xFFFF99)));
		wallByColor[6].push_back(AddObject(new ObjWall(0, 100, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(30, 100, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(40, 100, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(70, 100, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(80, 100, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(110, 100, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(120, 100, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(150, 100, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(160, 100, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(190, 100, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(200, 100, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(230, 100, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(240, 100, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(270, 100, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(280, 100, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(310, 100, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(320, 100, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(350, 100, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(360, 100, 30, 10, 0x99FFFF)));
		wallByColor[1].push_back(AddObject(new ObjWall(30, 110, 10, 30, 0xFF9999)));
		wallByColor[5].push_back(AddObject(new ObjWall(70, 110, 10, 30, 0xFF99FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(110, 110, 10, 30, 0x9999FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(150, 110, 10, 30, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(190, 110, 10, 30, 0x99FFFF)));
		wallByColor[5].push_back(AddObject(new ObjWall(230, 110, 10, 30, 0xFF99FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(270, 110, 10, 30, 0x99FFFF)));
		wallByColor[1].push_back(AddObject(new ObjWall(310, 110, 10, 30, 0xFF9999)));
		wallByColor[5].push_back(AddObject(new ObjWall(350, 110, 10, 30, 0xFF99FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(0, 140, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(30, 140, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(40, 140, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(70, 140, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(80, 140, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(110, 140, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(120, 140, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(150, 140, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(160, 140, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(190, 140, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(200, 140, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(230, 140, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(240, 140, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(270, 140, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(280, 140, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(310, 140, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(320, 140, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(350, 140, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(360, 140, 30, 10, 0xFF99FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(30, 150, 10, 30, 0xFF9999)));
		wallByColor[6].push_back(AddObject(new ObjWall(70, 150, 10, 30, 0x3333FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(110, 150, 10, 30, 0x9999FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(150, 150, 10, 30, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(190, 150, 10, 30, 0x3333FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(230, 150, 10, 30, 0x9999FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(270, 150, 10, 30, 0xFF99FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(310, 150, 10, 30, 0xFF9999)));
		wallByColor[5].push_back(AddObject(new ObjWall(350, 150, 10, 30, 0xFF99FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(0, 180, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(30, 180, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(40, 180, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(70, 180, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(80, 180, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(110, 180, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(120, 180, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(150, 180, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(160, 180, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(190, 180, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(200, 180, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(230, 180, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(240, 180, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(270, 180, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(280, 180, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(310, 180, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(320, 180, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(350, 180, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(360, 180, 30, 10, 0x3333FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(30, 190, 10, 30, 0x9999FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(70, 190, 10, 30, 0xFF9999)));
		wallByColor[1].push_back(AddObject(new ObjWall(110, 190, 10, 30, 0xFF9999)));
		wallByColor[4].push_back(AddObject(new ObjWall(150, 190, 10, 30, 0x99FFFF)));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 190, 10, 30, 0xFF9999)));
		wallByColor[6].push_back(AddObject(new ObjWall(230, 190, 10, 30, 0x3333FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(270, 190, 10, 30, 0x9999FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(310, 190, 10, 30, 0x3333FF)));
		wallByColor[3].push_back(AddObject(new ObjWall(350, 190, 10, 30, 0xFFFF99)));
		wallByColor[5].push_back(AddObject(new ObjWall(0, 220, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(30, 220, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(40, 220, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(70, 220, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(80, 220, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(110, 220, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(120, 220, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(150, 220, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(160, 220, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(190, 220, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(200, 220, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(230, 220, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(240, 220, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(270, 220, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(280, 220, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(310, 220, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(320, 220, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(350, 220, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(360, 220, 30, 10, 0x3333FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(30, 230, 10, 30, 0x3333FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(70, 230, 10, 30, 0x9999FF)));
		wallByColor[5].push_back(AddObject(new ObjWall(110, 230, 10, 30, 0xFF99FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(150, 230, 10, 30, 0x9999FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(190, 230, 10, 30, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(230, 230, 10, 30, 0xFFFF99)));
		wallByColor[3].push_back(AddObject(new ObjWall(270, 230, 10, 30, 0xFFFF99)));
		wallByColor[3].push_back(AddObject(new ObjWall(310, 230, 10, 30, 0xFFFF99)));
		wallByColor[2].push_back(AddObject(new ObjWall(350, 230, 10, 30, 0x9999FF)));
		wallByColor[6].push_back(AddObject(new ObjWall(0, 260, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(30, 260, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(40, 260, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(70, 260, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(80, 260, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(110, 260, 10, 10, 0x000000));
		wallByColor[4].push_back(AddObject(new ObjWall(120, 260, 30, 10, 0x99FFFF)));
		AddObject(new ObjWall(150, 260, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(160, 260, 30, 10, 0x3333FF)));
		AddObject(new ObjWall(190, 260, 10, 10, 0x000000));
		wallByColor[5].push_back(AddObject(new ObjWall(200, 260, 30, 10, 0xFF99FF)));
		AddObject(new ObjWall(230, 260, 10, 10, 0x000000));
		wallByColor[2].push_back(AddObject(new ObjWall(240, 260, 30, 10, 0x9999FF)));
		AddObject(new ObjWall(270, 260, 10, 10, 0x000000));
		wallByColor[3].push_back(AddObject(new ObjWall(280, 260, 30, 10, 0xFFFF99)));
		AddObject(new ObjWall(310, 260, 10, 10, 0x000000));
		wallByColor[1].push_back(AddObject(new ObjWall(320, 260, 30, 10, 0xFF9999)));
		AddObject(new ObjWall(350, 260, 10, 10, 0x000000));
		wallByColor[6].push_back(AddObject(new ObjWall(360, 260, 30, 10, 0x3333FF)));
		wallByColor[1].push_back(AddObject(new ObjWall(30, 270, 10, 30, 0xFF9999)));
		wallByColor[4].push_back(AddObject(new ObjWall(70, 270, 10, 30, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(110, 270, 10, 30, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(150, 270, 10, 30, 0xFF9999)));
		wallByColor[2].push_back(AddObject(new ObjWall(190, 270, 10, 30, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(230, 270, 10, 30, 0x9999FF)));
		wallByColor[4].push_back(AddObject(new ObjWall(270, 270, 10, 30, 0x99FFFF)));
		wallByColor[3].push_back(AddObject(new ObjWall(310, 270, 10, 30, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(350, 270, 10, 30, 0xFF9999)));
		AddObject(new ObjAreaCounter(wallByColor[6], 0, 270, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 120, 150, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 200, 230, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 240, 70, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 80, 30, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 0, 70, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 320, 150, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 0, 230, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 160, 30, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 240, 150, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 40, 110, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 120, 230, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 320, 0, 30, 20, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 320, 70, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 360, 0, 30, 20));
		AddObject(new ObjAreaCounter(wallByColor[4], 160, 70, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[4], 40, 190, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[4], 240, 0, 30, 20, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[4], 0, 30, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[4], 280, 230, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[4], 120, 270, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[4], 360, 70, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[2], 80, 70, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[2], 240, 230, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[2], 160, 110, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[2], 80, 190, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[2], 0, 150, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[2], 360, 150, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[2], 280, 30, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 120, 110, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[1], 40, 30, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[1], 0, 190, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[1], 160, 270, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[1], 280, 190, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[1], 200, 150, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[1], 80, 150, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[3], 40, 150, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[3], 0, 110, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[3], 120, 30, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[3], 200, 70, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[3], 160, 150, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[3], 80, 230, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[3], 280, 110, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[6], 160, 0, 30, 20, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 320, 230, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[4], 280, 150, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[2], 120, 0, 30, 20, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 280, 270, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[6], 80, 270, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 240, 30, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[4], 200, 30, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[4], 80, 110, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[3], 320, 190, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[2], 0, 0, 30, 20, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 160, 190, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[6], 360, 230, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 240, 110, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[4], 200, 110, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[3], 320, 30, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[2], 360, 30, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 40, 270, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[6], 120, 70, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 200, 0, 30, 20, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[4], 40, 0, 30, 20, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[3], 80, 0, 30, 20, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[2], 200, 270, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 360, 190, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[6], 280, 0, 30, 20, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 360, 110, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[4], 280, 70, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[3], 120, 190, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[2], 40, 230, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 360, 270, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[6], 240, 190, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[5], 200, 190, 30, 30, 1, 0xFF99FF));
		AddObject(new ObjAreaCounter(wallByColor[4], 160, 230, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjAreaCounter(wallByColor[3], 40, 70, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[2], 320, 110, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[6], 320, 270, 30, 30, 1, 0x3333FF));
		AddObject(new ObjAreaCounter(wallByColor[4], 240, 270, 30, 30, 1, 0x99FFFF));
	}
};


class LevelVeryHard1 : public Level {
public:
	LevelVeryHard1() : Level(235, 175){}

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

class LevelVeryHard2 : public Level {
public:
	LevelVeryHard2() : Level(390, 11) { }

	void OnInit() {
		std::vector<LevelObject*> wallByColor[5];
		
		wallByColor[0].push_back(AddObject(new ObjWall(0, 0, 380, 30, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(390, 20, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(0, 30, 350, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(370, 30, 10, 220, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(0, 40, 20, 40, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(330, 40, 30, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(380, 40, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(330, 50, 20, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(360, 60, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(390, 60, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(330, 70, 20, 60, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(60, 80, 270, 20, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(350, 80, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(380, 80, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(60, 100, 20, 40, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(360, 100, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(390, 100, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(350, 120, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(380, 120, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(120, 140, 230, 20, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(360, 140, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(390, 140, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(120, 160, 20, 40, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(330, 160, 30, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(380, 160, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(330, 170, 20, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(360, 180, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(390, 180, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(330, 190, 20, 60, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(180, 200, 150, 20, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(350, 200, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(380, 200, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(0, 210, 20, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(30, 210, 10, 30, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(180, 220, 20, 40, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(360, 220, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(390, 220, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(10, 230, 20, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(40, 230, 30, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(60, 240, 10, 50, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(350, 240, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(380, 240, 10, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(70, 260, 20, 10, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(240, 260, 160, 40, 0xFFFFFF)));
		wallByColor[0].push_back(AddObject(new ObjWall(80, 280, 10, 20, 0xFFFFFF)));
		
		wallByColor[1].push_back(AddObject(new ObjWall(0, 80, 10, 30, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(10, 100, 50, 10, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(60, 140, 10, 30, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(70, 160, 50, 10, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(120, 200, 10, 30, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(130, 220, 50, 10, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(180, 260, 10, 30, 0xFFFF99)));
		wallByColor[1].push_back(AddObject(new ObjWall(190, 280, 50, 10, 0xFFFF99)));
		
		wallByColor[2].push_back(AddObject(new ObjWall(10, 80, 10, 20, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(20, 90, 40, 10, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(70, 140, 10, 20, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(80, 150, 40, 10, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(130, 200, 10, 20, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(140, 210, 40, 10, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(190, 260, 10, 20, 0x9999FF)));
		wallByColor[2].push_back(AddObject(new ObjWall(200, 270, 40, 10, 0x9999FF)));
		
		wallByColor[3].push_back(AddObject(new ObjWall(20, 80, 40, 10, 0xFF9999)));
		wallByColor[3].push_back(AddObject(new ObjWall(80, 140, 40, 10, 0xFF9999)));
		wallByColor[3].push_back(AddObject(new ObjWall(140, 200, 40, 10, 0xFF9999)));
		wallByColor[3].push_back(AddObject(new ObjWall(200, 260, 40, 10, 0xFF9999)));
		
		wallByColor[4].push_back(AddObject(new ObjWall(0, 110, 60, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(50, 120, 10, 60, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(60, 170, 60, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(110, 180, 10, 60, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(120, 230, 60, 10, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(170, 240, 10, 60, 0x99FFFF)));
		wallByColor[4].push_back(AddObject(new ObjWall(180, 290, 60, 10, 0x99FFFF)));
		AddObject(new ObjTeleport(LevelManager::GetNextLevel(this), 0, 250, 50, 50));
		AddObject(new ObjAreaCounter(wallByColor[3], 85, 45, 30, 30, 1, 0xFF9999));
		AddObject(new ObjAreaCounter(wallByColor[2], 145, 105, 30, 30, 1, 0x9999FF));
		AddObject(new ObjAreaCounter(wallByColor[1], 205, 165, 30, 30, 1, 0xFFFF99));
		AddObject(new ObjAreaCounter(wallByColor[4], 265, 225, 30, 30, 1, 0x99FFFF));
		AddObject(new ObjClickBox({}, 0, 0, 400, 300, 0, 1000, 0x0));
		
	}
};



class LevelEnd : public Level {
public:
	LevelEnd() : Level(200, 150) { }

	void OnInit() {
		AddObject(new ObjText(200, 130, 60, true, "The end"));
		AddObject(new ObjText(200, 150, 20, true, "New levels will come. (really)"));
		AddObject(new ObjText(200, 165, 20, true, "You can go back to the welcome screen,"));
		AddObject(new ObjText(200, 175, 20, true, "or stay here with the other winners."));
		AddObject(new ObjTeleport(LevelManager::GetLevel(0), 0, 290, 10, 10));
		AddObject(new ObjWall(0, 260, 40, 10, 0x0));
		AddObject(new ObjWall(30, 270, 10, 20, 0x0));
		AddObject(new ObjWall(10, 280, 10, 20, 0x0));
		
	}
};
