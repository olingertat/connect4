#ifndef TEXT_VIEW
#define TEXT_VIEW
#include "view.h"

class TextView : public View {
	public:
		void updateView(const Board& theBoard) override;
		void displayWinner(PlayerTeam player) override;
		~TextView() override = default;
};


#endif
