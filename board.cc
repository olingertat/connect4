#include "board.h"
#include "textView.h"

using namespace std;

Board::Board()
	: theBoard{vector<vector<PlayerTeam>>(BOARD_WIDTH, vector<PlayerTeam>(BOARD_HEIGHT, noPlayer))}
	, textView{make_unique<TextView>()}
	, theMoves{stack<int>()}
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
		theMoves.push(colNum);
		return;
	}
	throw -1;
}

// Self-explanatory
void Board::undoMove() {
	int lastMoveCol = theMoves.top();
	theBoard[lastMoveCol][dropHeight(lastMoveCol)-1] = noPlayer;
	theMoves.pop();
}

// Check if adding a piece at colNum, rowNum completes a run of at least WIN_LENGTH
bool Board::checkWinLength(int colNum, int rowNum, int dx, int dy, PlayerTeam player) const {
	int runLength = 1;
	int numSteps = 1;
	while(validLocation(colNum+numSteps*dx, rowNum+numSteps*dy)) {
		if(theBoard[colNum+numSteps*dx][rowNum+numSteps*dy] == player) {
			++runLength;
			++numSteps;
		} else {
			break;
		}
	}
	numSteps = -1;
	while(validLocation(colNum+numSteps*dx, rowNum+numSteps*dy)) {
		if(theBoard[colNum+numSteps*dx][rowNum+numSteps*dy] == player) {
			++runLength;
			--numSteps;
		} else {
			break;
		}
	}
	return (runLength >= WIN_LENGTH);
}

// Check if adding a piece at colNum, rowNum wins the game for a player
bool Board::checkWinningMove(int colNum, int rowNum, PlayerTeam player) const {
	return (
		checkWinLength(colNum, rowNum, 1, 0, player)
		|| checkWinLength(colNum, rowNum, 0, 1, player)
		|| checkWinLength(colNum, rowNum, 1, 1, player)
		|| checkWinLength(colNum, rowNum, -1, 1, player)
	);
}

// Heuristic with +ve values in favor of playerX, -ve in favor of playerO
int Board::heuristic() const {
	// Check the number of places where a placement can complete a row of 4 and subtract
	// the count of such playerO placements from the count of such PlayerX placements
	int heuristicValue = 0;

	// First obtain the ranges to check for each column (between the minimum dropHeight for the column
	// and the maximum dropHeight of it and its adjacent columns inclusive)
	int dropHeights[BOARD_WIDTH];
	int maxAdjacentDropHeights[BOARD_WIDTH];
	for(int i = 0; i < BOARD_WIDTH; ++i) dropHeights[i] = dropHeight(i);
	maxAdjacentDropHeights[0] = max(dropHeights[0], dropHeights[1]);
	for(int i = 1; i < BOARD_WIDTH - 1; ++i) 
		maxAdjacentDropHeights[i] = max({dropHeights[i-1], dropHeights[i], dropHeights[i+1]});
	maxAdjacentDropHeights[BOARD_WIDTH-1] = max(dropHeights[BOARD_WIDTH-2], dropHeights[BOARD_WIDTH-1]);

	// Ensure each maxAdjacentDropHeight is not exceeding BOARD_HEIGHT (to avoid considering plays
	// outside of the board)
	for(int i = 0; i < BOARD_WIDTH; ++i) {
		if(maxAdjacentDropHeights[i] >= BOARD_HEIGHT) maxAdjacentDropHeights[i] = BOARD_HEIGHT-1;
	}

	// Use the found ranges to check the number of winning moves in each column for each player
	for(int col = 0; col < BOARD_WIDTH; ++col) {
		for(int row = dropHeights[col]; row <= maxAdjacentDropHeights[col]; ++row) {
			if(checkWinningMove(col, row, MAXIMIZING_PLAYER)) ++heuristicValue;
			if(checkWinningMove(col, row, MINIMIZING_PLAYER)) --heuristicValue;
		}
	}

	return heuristicValue;
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


