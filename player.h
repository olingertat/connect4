#ifndef PLAYER
#define PLAYER
#include "board.h"

class Player {
	public:
		virtual int getMove(Board* theBoard) = 0;
		virtual ~Player() = default;
};

#endif
