#pragma once
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>

class Monster
{
private:
	int health;
	int x;
	int y;
	int level;
	char orientation;
	int atk;
	int def;
	int xp;
	
	

public:
	Monster(const Monster& source);
	Monster& operator=(const Monster& source);
	Monster(char orientation, int x, int y, int level, int health);
	Monster(char orientation, int x, int y,  int level);
	void setx(int _x);
	void sety(int _y);
	void setPosition(int _x, int _y);
	void getPosition(int& _x, int& _y);
	void moveMonster();
	int attack();
	int takeDamage(int attack);
	std::vector <int*> printInfo;
	void init();
};




