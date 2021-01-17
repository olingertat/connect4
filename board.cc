#include "board.h"
#include "textView.h"

using namespace std;

Board::Board()
	: theBoard{vector<vector<PlayerTeam>>(BOARD_WIDTH, vector<PlayerTeam>(BOARD_HEIGHT, noPlayer))}
	, textView{make_unique<TextView>()}
	{}

bool Board::boardIsFull() const {
	for(int col = 0; col < BOARD_WIDTH; ++col) {
		if(validMove(col)) return false;
	}
	return true;
}


// Check if a piece can be added in the given column
bool Board::validMove( int colNum ) const {
	if(colNum < 0 || colNum >= BOARD_WIDTH) return false;
	bool columnHasRoom = theBoard[colNum][BOARD_HEIGHT - 1] == noPlayer;
	return columnHasRoom;
}

// Check if coordinate falls on the board
bool Board::validLocation( int colNum, int rowNum ) const {
	bool colValid = (colNum >= 0 && colNum < BOARD_WIDTH);
	bool rowValid = (rowNum >= 0 && rowNum < BOARD_HEIGHT);
	return (colValid && rowValid);
}

// Returns expected y-coordinate of a piece dropped in the given column
int Board::dropHeight( int colNum ) const {
	for(int i = BOARD_HEIGHT - 1; i >= 0; --i) {
		if( theBoard[colNum][i] != noPlayer ) return ( i + 1 );
	}
	return 0;
}

// Drop a piece in column colNum
void Board::dropPiece( PlayerTeam player, int colNum ) {
	int rowNum = dropHeight(colNum);
	if( validMove(colNum) ) {
		theBoard[colNum][rowNum] = player;
		return;
	}
	throw -1;
}

// Finds and returns the length of the longest line of similar pieces
int Board::longestRun( PlayerTeam player ) const {
	int longestRun = 0;

	// horizonal runs
	for( int row = 0; row < BOARD_HEIGHT; ++row ) {
		int runCount = 0;
		for( int col = 0; col < BOARD_WIDTH; ++col ) {
			if( theBoard[col][row] == player ) {
				if( ++runCount > longestRun ) longestRun = runCount;
			} else {
				runCount = 0;
			}
		}
			
	}

	// vertical runs
	for( int col = 0; col < BOARD_WIDTH; ++col) {
		int runCount = 0;
		for( int row = 0; row < BOARD_HEIGHT; ++row ) {
			if( theBoard[col][row] == player ) {
				if( ++runCount > longestRun ) longestRun = runCount;
			} else {
				runCount = 0;
			}
		}
	}

	// diagonal (top left to bottom right) runs
	for( int offset = 0; offset < (BOARD_HEIGHT + BOARD_WIDTH - 2) ; ++offset ) {
		// offset refers to the sum of the x and y coords in the current diagonal
		int runCount = 0;
		int rowNum, colNum;

		// get the first coords in the diagonal
		if(offset < BOARD_HEIGHT) {
			rowNum = offset;
			colNum = 0;
		} else {
			rowNum = BOARD_HEIGHT - 1;
			colNum = offset - BOARD_HEIGHT + 1;
		}
		while(validLocation(rowNum, colNum)) {
			if( theBoard[colNum][rowNum] == player ) {
				if ( ++runCount > longestRun ) longestRun = runCount;
			} else {
				runCount = 0;
			}
			// move down and right
			--rowNum;
			++colNum;
		}
	}

	// diagonal (bottom left to top right) runs
	for( int offset = 0; offset < (BOARD_HEIGHT + BOARD_WIDTH - 2); ++offset ) {
		int runCount = 0;
		int rowNum, colNum;

		// get the first coords in the diagonal
		if(offset < BOARD_HEIGHT) {
			rowNum = BOARD_HEIGHT - 1 - offset;
			colNum = 0;
		} else {
			rowNum = 0;
			colNum = offset - BOARD_HEIGHT + 1;
		}
		while(validLocation(rowNum, colNum)) {
			if( theBoard[colNum][rowNum] == player ) {
				if( ++runCount > longestRun ) longestRun = runCount;
			} else {
				runCount = 0;
			}
			// move up and right
			++rowNum;
			++colNum;
		}
	}

	return longestRun;
}

// Returns winner if there is a row of WIN_LENGTH, noPlayer otherwise
PlayerTeam Board::winner() const {
	if(longestRun(playerX) >= WIN_LENGTH) return playerX;
	if(longestRun(playerO) >= WIN_LENGTH) return playerO;
	return noPlayer;
}

bool Board::gameIsOver() const {
	return (winner() != noPlayer || boardIsFull());
}

PlayerTeam Board::at(int colNum, int rowNum) const {
	return theBoard.at(colNum).at(rowNum);
}

void Board::updateViews() const {
	textView->updateView(*this);
}

void Board::displayWinner() const {
	textView->displayWinner(winner());
}


