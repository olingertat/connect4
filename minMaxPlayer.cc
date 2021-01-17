#include "minMaxPlayer.h"
using namespace std;

MinMaxPlayer::MinMaxPlayer(bool maximizingPlayer, int depth)
	: Player{}, maximizingPlayer{maximizingPlayer}, depth{depth} {}

int minimax(Board* theBoard, int depth, bool maximizingPlayer) {
	if(depth == 0) {
		return theBoard->heuristic();
	}
	if(maximizingPlayer) {
		int value = -999;
		for(int i = 0; i < BOARD_WIDTH; ++i) {
			if(theBoard->validMove(i)) {
				if(theBoard->checkWinningMove(i, theBoard->dropHeight(i), MAXIMIZING_PLAYER)) {
					return 999;
				} 
				theBoard->dropPiece(MAXIMIZING_PLAYER, i);
				value = max(value, minimax(theBoard, depth-1, false));
				theBoard->undoMove();
			}
		}
		return value;
	} else {
		int value = 999;
		for(int i = 0; i < BOARD_WIDTH; ++i) {
			if(theBoard->validMove(i)) {
				if(theBoard->checkWinningMove(i, theBoard->dropHeight(i), MINIMIZING_PLAYER)) {
					return -999;
				} 
				theBoard->dropPiece(MINIMIZING_PLAYER, i);
				value = min(value, minimax(theBoard, depth-1, true));
				theBoard->undoMove();
			}
		}
		return value;
	}
}

int MinMaxPlayer::getMove(Board* theBoard) {
	if(maximizingPlayer) {
		// The initial value must be worse than a loss because we must choose a move, even if all possible moves lead to loss
		int bestMinMaxValue = -1000; 
		int bestMove = -1;
		for(int col = 0; col < BOARD_WIDTH; ++col) {
			if(theBoard->validMove(col)) {
				// check if we can win this turn
				if(theBoard->checkWinningMove(col, theBoard->dropHeight(col), MAXIMIZING_PLAYER)) return col;
				theBoard->dropPiece(MAXIMIZING_PLAYER, col);
				int childValue = minimax(theBoard, depth-1, false);
				if(bestMinMaxValue < childValue) {
					bestMove = col;
					bestMinMaxValue = childValue;
				}
				theBoard->undoMove();
			}
		}
	
		return bestMove;
	} else {
		// The initial value must be better than a loss because we must choose a move, even if all possible moves lead to loss
		int bestMinMaxValue = 1000; 
		int bestMove = -1;
		for(int col = 0; col < BOARD_WIDTH; ++col) {
			if(theBoard->validMove(col)) {
				// check if we can win this turn
				if(theBoard->checkWinningMove(col, theBoard->dropHeight(col), MINIMIZING_PLAYER)) return col;
				theBoard->dropPiece(MINIMIZING_PLAYER, col);
				int childValue = minimax(theBoard, depth-1, true);
				if(bestMinMaxValue > childValue) {
					bestMove = col;
					bestMinMaxValue = childValue;
				}
				theBoard->undoMove();
			}
		}
	
		return bestMove;
	}
}

