#pragma once
#include <random>
#include <ctime>
#include <vector>
#include "Monster.h"
#include <algorithm>

class Player
{
private:
	int x;
	int y;
	int health;
	int level;
	int atk;
	int def;
	int xp;
	char symbol;
	
public:
	void init(int _level, int _health, int attack, int defense, int experience);
	char getSymbol();
	void setx(int _x);
	void sety(int _y);
	void setPosition(int _x, int _y);
	void getPosition(int& _x, int& _y);
	int  attack();
	int  takeDamage(int attack);
	void addXp(int xpAdded);
	std::vector <int*> printInfo;

};

