#ifndef VIEW
#define VIEW
#include "playerTeam.h"

class Board;

class View {
	public:
		virtual void updateView(const Board& theBoard) = 0;
		virtual void displayWinner(PlayerTeam winner) = 0;
		virtual ~View() = default;
};

#endif
