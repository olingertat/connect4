#ifndef CONTROLLER
#define CONTROLLER
#include "board.h"
#include "player.h"

class Controller {
	Board* theBoard;
	PlayerTeam currPlayer = playerX;
	std::unique_ptr<Player> playerOne;
	std::unique_ptr<Player> playerTwo;
	public:
		void playGame();
		Controller(Board* theBoard, std::unique_ptr<Player> playerOne, std::unique_ptr<Player> playerTwo);
};

#endif
