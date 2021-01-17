#include <iostream>
#include "humanPlayer.h"
using namespace std;

int HumanPlayer::getMove(Board* theBoard) {
	int theMove = -1;
	while(!theBoard->validMove(theMove)) {
		cout << "Please enter a column in which to drop a piece: ";
		cin >> theMove;
	}
	return theMove;
}

