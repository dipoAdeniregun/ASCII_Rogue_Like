#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include "Monster.h"
#include "Player.h"

class Level
{
private:
	std::vector <std::string> _level;
	void processMove(Player& _player, int newX, int newY);
	std::vector <Monster> _enemies;
	std::vector <std::string> printInfo { "Level", "HP", "Atk", "Def" , "XP"};
	int longestLineLength = 0;
	bool inCombat;
	

public:
	Level();
	void load(std::string levelFileName, Player &player);
	void print(Player& _player);
	void movePlayer(char input, Player &player);
	void setTile(char newChar, int targetX, int targetY);
	void battleMonster(Player& player, int targetX, int targertY);
};

