#ifndef BOARD
#define BOARD
#include <vector>
#include <stack>
#include "playerTeam.h"
#include "view.h"

class Board {
	std::vector<std::vector<PlayerTeam>> theBoard;
	std::unique_ptr<View> textView;
	std::stack<int> theMoves; // Stores the set of played moves for the purpose of undoing
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

		// Self-explanatory
		void undoMove();
	
		// Check if adding a piece at colNum, rowNum completes a line of WIN_LENGTH in the direction
		// indicated by dx, dy
		bool checkWinLength(int colNum, int rowNum, int dx, int dy, PlayerTeam player) const;

		// Check if adding a piece at colNum, rowNum wins the game for a player
		bool checkWinningMove(int colNum, int rowNum, PlayerTeam player) const;

		// Heuristic with +ve values in favor of playerX, -ve in favor of playerO
		int heuristic() const;

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
