#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER
#include "player.h"

class HumanPlayer : public Player {
	public:
		int getMove(Board* theBoard) override;
		~HumanPlayer() override = default;
};


#endif
