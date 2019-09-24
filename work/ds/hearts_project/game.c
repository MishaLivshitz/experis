#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "deck.h"
#include "deal.h"
#include "TTY.h"

#define ACTIVE_MAGIC_NUM 0xaeeaee
#define IS_VALID(G)		((G) && (G)->m_magicNum == ACTIVE_MAGIC_NUM)
#define NUM_OF_PLAYERS 4

struct Game
{
	int m_magicNum;
	Player** m_players;
	Deck* m_deck;
	Deal* m_deal;
	size_t m_maxScore;
};


Game* GameCreate(Player* _players[], size_t _numOfPackets, size_t _numOfTricks,size_t _numOfPlayers,size_t _maxScore)
{
	Game* game;
	
	game = (Game*)malloc(sizeof(Game));
	
	if(!game)
	{
		return game;
	}
	
	game->m_deck = DeckCreate(_numOfPackets);
	if(!game->m_deck)
	{
		free(game);
		return NULL;
	}
	
	game->m_deal = DealCreate(_players,_numOfTricks,_numOfPlayers);
	if(!game->m_deal)
	{
		free(game->m_deck);
		free(game);
		return NULL;
	}
	
	game->m_players = _players;
	game->m_maxScore = _maxScore;
	game->m_magicNum = ACTIVE_MAGIC_NUM;
	
	return game;
}

void GameDestroy(Game* _game)
{
	if(IS_VALID(_game))
	{
		_game->m_magicNum = -1;
		free(_game->m_deck);
		free(_game->m_deal);
		free(_game);
	}
}

static int CalcResults(size_t _maxScore, size_t* _scores, size_t* _totalScores)
{
	
	size_t i;
	int exitFlag=1;
	
	for(i=0;i< NUM_OF_PLAYERS; i++)
	{
		_totalScores[i]+=_scores[i];
		_scores[i]=0;
		
		if(_totalScores[i] >= _maxScore)
		{
			exitFlag=0;
		}
	}
	
	return exitFlag;
}

static size_t ResultsPrint(Player* _players[], size_t* _totalScores)
{
	size_t loser;
	size_t max=0;
	size_t i;
	
	for(i=0;i< NUM_OF_PLAYERS; i++)
	{
		PlayerPrintName(_players[i]);
	
		if(max<_totalScores[i])
		{
			loser=i;
			max = _totalScores[i];
		}
		printf("	%ld\n", _totalScores[i]);
	}
	putchar('\n');
	
	return loser;
}

ADTErr GameStart(Game* _game)
{
	size_t scores[NUM_OF_PLAYERS] = {0};
	size_t totalScores[NUM_OF_PLAYERS] = {0};
	int exitFlag=1;
	int k=0;
	int loser;
	
	if(!IS_VALID(_game))
	{
		return ERR_NOT_INITIALIZED;
	}
	printf("\n\n%s%s %s%s *****New game***** %s%s %s%s\n\n",TXT_RED,CHR_HEART,CHR_HEART,TXT_NORMAL,TXT_RED,CHR_HEART,CHR_HEART,TXT_NORMAL);
	while(exitFlag)
	{
		printf("\n%s%s %s%s	Deal #%d    %s%s %s%s\n\n",TXT_RED,CHR_HEART,CHR_HEART,TXT_NORMAL,k+1,TXT_RED,CHR_HEART,CHR_HEART,TXT_NORMAL);
		DealPlay(_game->m_deal,_game->m_deck,k++ % NUM_OF_MODES,scores);
		exitFlag = CalcResults(_game->m_maxScore, scores, totalScores);
		loser = ResultsPrint(_game->m_players,totalScores);
	}
	
	printf("LOSER: ");
	PlayerPrintName(_game->m_players[loser]);
	printf("\n\n");
	return ERR_OK;
}
