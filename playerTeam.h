#ifndef PLAYER_TEAM
#define PLAYER_TEAM
#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7
#define WIN_LENGTH 4


typedef enum PlayerTeams {
	noPlayer,
	playerX,
	playerO
} PlayerTeam;

PlayerTeam getOpposingTeam( PlayerTeam player );

char getTeamCharRepresentation( PlayerTeam player );

#endif
