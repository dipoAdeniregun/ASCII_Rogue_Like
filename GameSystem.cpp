#include "GameSystem.h"
#include <conio.h>

GameSystem::GameSystem(std::string levelFileName) {
	player = Player();
	level = Level();

	player.init(1, 100, 11, 11, 0);

	level.load(levelFileName, player);
}

void GameSystem::playGame(){
	char keyPressed ;

	do {
		level.print(player);
		keyPressed = getMove();
	} while (keyPressed != 'p');
	
	
}

char GameSystem::getMove(){
	char input = _getch();
	level.movePlayer(input, player);

	return input;
}


