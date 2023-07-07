#include "Monster.h"


//constructor that takes in health, probably used for continuing saved games
Monster::Monster(char ori, int _x, int _y, int _level, int _health)
	:x{ _x }, y{ _y }, level{ _level }, health{ _health }, orientation{ ori }
{
	atk = _level * 15;
	def = _level ;
	xp = _level * 10; 
	printInfo = { &level, &health,  &atk, &def, &xp };
	//printf("Level = %d\n", *printInfo[0]);
}

//constructor that doesn't take in health value, used for new game
Monster::Monster(char ori, int _x, int _y, int _level)
	: x{ _x }, y{ _y },  level{ _level }, orientation{ ori }
{
	health = level * 10;
	atk = _level;
	def = _level ;
	xp = _level * 25;
	printInfo = { &level, &health,  &atk, &def, &xp };
	//printf("Level = %d\n", *printInfo[0]);
}

void Monster::init(){ printInfo = { &level, &health,  &atk, &def, &xp }; }
void Monster::setx(int _x) { x = _x; };
void Monster::sety(int _y) { y = _y; };
void Monster::setPosition(int _x, int _y) { x = _x; y = _y; }

//copy constructor
Monster::Monster(const Monster& source) 
	: x{ source.x }, y{ source.y }, level{ source.level }, health{source.health}, atk{source.atk}, def{source.def}, xp{source.xp}
{
	printInfo = source.printInfo;
}

Monster& Monster::operator=(const Monster &source)
{
	x = source.x;
	y = source.y;
	level = source.level;
	health = source.health;
	atk = source.atk;
	def = source.def;
	xp = source.xp;
	
	if (this == &source) {
		return *this;
	}

	printInfo = {};

	for (size_t i = 0; i < source.printInfo.size(); i++) {
		printInfo.push_back(source.printInfo[i]);
	}
	return *this;
}

//get enemy x and y coordinates
void Monster::getPosition(int& _x, int& _y) {
	_x = x;
	_y = y;
}


/*
* Move all monsters in the direction they're facing until they hit a wall then 
* turn them in the opposite direction so they patrol a straight line from wall
* to wall
*/
void Monster::moveMonster() {
	switch (orientation) {
	case '>':
		x++;
		break;
	case '<':
		x--;
		break;
	case 'V':
		y++;
		break;
	case 'A':
		y--;
		break;
	default:
		break;
	}
}

//return a random number between 0 and the player's atk stat which is the amount of damage done
int Monster::attack() {
	static std::default_random_engine randomAttackEngine(time(NULL));
	std::uniform_int_distribution<int> attackRoll(0, atk);

	return attackRoll(randomAttackEngine);
}

int Monster::takeDamage(int attack) {
	attack -= def;		//defense stat reduces strength of incoming attack

	//if attack strength is bigger than def stat, reduce health by leftover attack strength
	health -= std::max(0, attack);	

	//return 0 if the monster is alive or the xp gained from defeating the monster otherwise
	return (health > 0) ? 0 : xp ;
}
