#include "GameSystem.h"

int main() {

	GameSystem newGame = GameSystem("level1.txt");
	newGame.playGame();

	return 0;
}