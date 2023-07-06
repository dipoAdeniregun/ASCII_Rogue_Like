#include "Player.h"

void Player::init(int _level, int _health, int _attack, int _defense, int _experience){
	level = _level ;
	health = _health ;
	atk = _attack ;
	def = _defense ;
	xp =  _experience ;
	printInfo = { &level, &health, &atk, &def, &xp };
}

char Player::getSymbol() { return symbol; };
void Player::setx(int _x) { x = _x; };
void Player::sety(int _y) { y = _y; };

//add xp from defeated enemies and level up if necessary
void Player::addXp(int xpAdded) { 
	xp += xpAdded;
	
	//level up
	while (xp > 50) {
		printf("Leveled up!\n");
		system("PAUSE");
		xp -= 50;
		atk += 10;
		def += 10;
		health += 10;
		level++;
	}
}
void Player::setPosition(int _x, int _y) { x = _x; y = _y; }

//get player x and y coordinates
void Player::getPosition(int& _x, int& _y) {
	_x = x;
	_y = y;
}

//return a random number between 0 and the player's atk stat which is the amount of damage done
int Player::attack(){
	static std::default_random_engine randomAttackEngine(time(NULL));
	std::uniform_int_distribution<int> attackRoll(0, atk);

	return attackRoll(randomAttackEngine);
}

int Player::takeDamage(int attack) {
	attack -= def;		//defense stat reduces strength of incoming attack

	//if attack strength is bigger than def stat, reduce health by leftover attack strength
	health -= std::max(0, attack);

	//return 0 if the monster is alive or the xp gained from defeating the monster otherwise
	return (health > 0) ? 0 : 1;
}
