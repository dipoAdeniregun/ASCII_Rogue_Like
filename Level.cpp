#include "Level.h"
#include <iostream>
#include <cstdio>
#include "Player.h"
#include "Monster.h"
#include <algorithm>


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
		longestLineLength = std::max(longestLineLength, (int) s.size());
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
				_enemies.push_back(Monster(tile, j, i, 1));
				//printf("HP: %d", *_enemies.back().printInfo[1]);
				
				break;
			default:
				break;
			}
			
			
		}
	}
	levelTxt.close();
}

//print the level given the level vector
void Level::print(Player &_player) {
	system("cls");
	for (int i = 0; i < _level.size(); i++) {
		printf("%-*s",longestLineLength, _level[i].c_str());
		if (i == 0)
		{
			printf("\tPlayer Stats");
			//printf("\t Enemy Info");
		}
		else if (i <= printInfo.size()) {
			printf("\t%-6s", printInfo[i-1].c_str());
			printf("%-6d", *(_player.printInfo[i-1]));

		}
		
		printf("\n");
		
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

	for (size_t i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(enemyX, enemyY);

		if (targetX == enemyX && targetY == enemyY) {
			//do battle if we're trying to move to an enemy
			_enemies[i].init();	//hacky way to set Monster printInfo pointers correctly
			printf("Enemy  Stats\n");
			for (size_t j = 0; j < printInfo.size(); j++)
			{
				printf("%-6s", printInfo[j].c_str());
				printf("%6d\n", *(_enemies[i].printInfo[j]));
			}
			attackRoll = player.attack();
			printf("\nPlayer attacked for %d damage\n", attackRoll);
			

			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult > 0) {
				printf("Enemy defeated\n");
				player.addXp( attackResult);
				//_enemies.erase(_enemies.begin()+i);
				setTile('.', targetX, targetY);
				return;
			}

			attackRoll = _enemies[i].attack();
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