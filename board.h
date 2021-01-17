#ifndef BOARD
#define BOARD
#include <vector>
#include "playerTeam.h"
#include "view.h"

class Board {
	std::vector<std::vector<PlayerTeam>> theBoard;
	std::unique_ptr<View> textView;
	bool boardIsFull() const;
	public:
		Board();

		// Check if a piece can be added in the given column
		bool validMove( int colNum ) const;

		// Check if coordinate falls on the board
		bool validLocation( int colNum, int rowNum ) const;

		// Returns expected y-coordinate of a piece dropped in the given column
		int dropHeight( int colNum ) const;

		// Drop a piece in column colNum
		void dropPiece( PlayerTeam player, int colNum );
	
		// Finds and returns the length of the longest line of similar pieces
		int longestRun( PlayerTeam player ) const;
		
		// Returns winner if there is a row of WIN_LENGTH, noPlayer otherwise
		PlayerTeam winner() const;

		bool gameIsOver() const;

		PlayerTeam at( int colNum, int rowNum ) const;
		
		void updateViews() const;

		void displayWinner() const;
};

#endif
