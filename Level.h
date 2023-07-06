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

public:
	Level();
	void load(std::string levelFileName, Player &player);
	void print();
	void movePlayer(char input, Player &player);
	void setTile(char newChar, int targetX, int targetY);
	void battleMonster(Player& player, int targetX, int targertY);
};

