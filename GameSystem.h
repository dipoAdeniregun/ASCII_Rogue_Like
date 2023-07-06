#pragma once
#include "Level.h"
#include "Player.h"
#include "Monster.h"
#include <string>

class GameSystem
{
private:
	Player player;
	Level level;
public:
	GameSystem(std::string levelFileName);
	void playGame();
	char getMove();
};

