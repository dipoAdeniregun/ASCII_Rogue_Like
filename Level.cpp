#include "Level.h"
#include <iostream>
#include <cstdio>
#include "Player.h"
#include "Monster.h"

Level::Level() {
	_enemies = {};
	_level = {};
}

void Level::load(std::string levelFileName, Player &player){
	//open text file containing level data
	std::fstream levelTxt{levelFileName,  std::ios::in }; 
	if (!levelTxt.is_open())
	{
		perror(levelFileName.c_str());
		exit(1);
	}

	//read level data text into levelData vector
	std::string s;
	while (levelTxt) {
		std::getline(levelTxt, s);
		_level.push_back(s);
	}

	//process the level
	char tile;
	for (int i = 0; i < _level.size(); i++)
	{
		for (int j = 0; j < _level[i].size(); j++) {
			tile = _level[i][j];
			switch (tile) {
			case '@':
			
				player.setx(j);
				player.sety(i);
				break;
			case '>':
			case '<':
			case 'V':
			case 'A':
				_enemies.push_back(Monster(tile, j, i, 1, 10));
				break;
			default:
				break;
			}
			
			
		}
	}
	levelTxt.close();
}

//print the level given the level vector
void Level::print() {
	system("cls");
	for (auto row : _level) {
		printf("%s\n", row.c_str());
	}
	printf("\n");
}

void Level::setTile(char newChar, int targetX, int targetY) {_level[targetY][targetX] = newChar;}


//tries to move the player character in the direction pressed
void Level::movePlayer(char input, Player &player) {
	int newX, newY;
	player.getPosition(newX, newY);
	switch (input)
	{

	case 'W':		//move up
	case 'w':
		processMove(player, newX, newY-1);
		break;

	case 's':		//move down
	case 'S':
		processMove(player, newX, newY+1);
		break;

	case 'a':		//move left
	case 'A':
		processMove(player, newX-1, newY);
		break;

	case 'd':		//move right
	case 'D':
		processMove(player, newX+1, newY);
		break;
	case 'p':
	case 'P':
		printf("Exiting game!\n");
		break;
		//exit(0);
	default:		//wrong button press
		printf("Wrong button press!\n");
		break;
	}
}

void Level::processMove(Player &_player, int newX, int newY) {
	int oldX, oldY;
	_player.getPosition(oldX, oldY);
	
	char moveTile = _level[newY][newX];


	switch (moveTile)
	{
	case '.':
		_player.setPosition(newX, newY);
		setTile('@', newX, newY);
		setTile('.', oldX, oldY);
		break;

	case '#':
		printf("Blocked by wall!\n");
		system("PAUSE");
		break;
	case '<':
	case '>':
	case 'V':
	case 'A':
		//printf("Entering Combat!\n");
		//system("PAUSE");
		battleMonster(_player, newX, newY);
		

		break;
	default:
		perror("Invalid level character found!\n");
		exit(1);
		break;
	}
}

void Level::battleMonster(Player& player, int targetX, int targetY) {
	int enemyX, enemyY;
	int attackRoll;
	int attackResult;

	for (auto enemy : _enemies) {
		enemy.getPosition(enemyX, enemyY);

		if (targetX == enemyX && targetY == enemyY) {
			//do battle if we're trying to move to an enemy
			attackRoll = player.attack();
			printf("Player attacked for %d damage\n", attackRoll);
			system("PAUSE");

			attackResult = enemy.takeDamage(attackRoll);

			if (attackResult > 0) {
				player.addXp( attackResult);

				setTile('.', targetX, targetY);
				return;
			}

			attackRoll = enemy.attack();
			printf("Enemy attacked you for %d damage!\n", attackRoll);
			system("PAUSE");

			attackResult = player.takeDamage(attackRoll);

			if (attackResult > 0) {
				printf("Player died\n");
				exit(0);
			}

		}
	}
}