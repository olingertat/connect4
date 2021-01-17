#include <iostream>
#include "board.h"
#include "textView.h"
using namespace std;

void TextView::updateView(const Board& theBoard) {
	for(int row = BOARD_HEIGHT - 1; row >= 0; --row) {
		for(int col = 0; col < BOARD_WIDTH; ++col) {
			cout << getTeamCharRepresentation(theBoard.at(col, row));
		}
		cout << '\n';
	}
}

void TextView::displayWinner(PlayerTeam winner) {
	if(winner == playerX) cout << "Player 1 wins!";
	else if(winner == playerO) cout << "Player 2 wins!";
	else cout << "It's a tie!";
	cout << endl;
}
