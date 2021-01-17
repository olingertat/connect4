#include "playerTeam.h"

PlayerTeam getOpposingTeam( PlayerTeam player ) {
	if(player == playerX) return playerO;
	if(player == playerO) return playerX;
	return noPlayer;
}

bool isMaximizingPlayer( PlayerTeam player ) {
	return player == MAXIMIZING_PLAYER;
}

char getTeamCharRepresentation( PlayerTeam player ) {
	if(player == playerX) return 'X';
	if(player == playerO) return 'O';
	return ' ';
}

