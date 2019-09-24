#include <stdio.h>
#include "player.h"
#include "game.h"

#define NUM_OF_PLAYERS 4
#define NUM_OF_PACKETS 1
#define	MAX_SCORE 100

int main(){
	
	Game* game;
	size_t i;
	char option = 'p';
	Player* players[NUM_OF_PLAYERS];
	char* playersNames[NUM_OF_PLAYERS] = {"North", "East", "South", "West"};

	CardsInit();
	
	for(i=0;i<NUM_OF_PLAYERS;i++)
	{
		players[i] = PlayerCreate(playersNames[i],i,BOT);
	}
	
	game = GameCreate(players,NUM_OF_PACKETS,NUM_OF_RANKS,NUM_OF_PLAYERS,MAX_SCORE);
	
	while(option!='q')
	{
		GameStart(game);
		puts("Press any key to play again or q to quit");
		option = getchar();
	}
	
	GameDestroy(game);
	
	return 1;
}
