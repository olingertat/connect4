#ifndef MIN_MAX_PLAYER
#define MIN_MAX_PLAYER
#include "player.h"

class MinMaxPlayer : public Player {
	bool maximizingPlayer;
	int depth;
	public:
		int getMove(Board* theBoard) override;
		MinMaxPlayer(bool maximizingPlayer, int depth);
		~MinMaxPlayer() override = default;
};

#endif
