#include <iostream>
#include "board.h"
#include "textView.h"
using namespace std;

void TextView::updateView(const Board& theBoard) {
	for(int i = 0; i < BOARD_WIDTH+2; ++i) cout << '*';
	cout << '\n';
	for(int row = BOARD_HEIGHT - 1; row >= 0; --row) {
		cout << '*';
		for(int col = 0; col < BOARD_WIDTH; ++col) {
			cout << getTeamCharRepresentation(theBoard.at(col, row));
		}
		cout << "*\n";
	}
	for(int i = 0; i < BOARD_WIDTH+2; ++i) cout << '*';
	cout << "\n ";
	for(int i = 0; i < BOARD_WIDTH; ++i) cout << i;
	cout << " \n";
}

void TextView::displayWinner(PlayerTeam winner) {
	if(winner == playerX) cout << "Player 1 wins!";
	else if(winner == playerO) cout << "Player 2 wins!";
	else cout << "It's a tie!";
	cout << endl;
}
