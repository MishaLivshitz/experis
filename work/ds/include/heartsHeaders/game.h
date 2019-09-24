#ifndef _GAME_H_
#define _GAME_H_

#include <stddef.h>		/* size_t */
#include "ADTErr.h"
#include "player.h"

typedef struct Game Game;

/**
@Brief: This method create game

@params:
		_player: pointer to player
		_numOfPackets: number of packets to play with
		_numOfTricks: number of tricks per deal
		_numOfPlayers: number of players
		_maxScore: max score allowed;

@return: pointer to new game when success else return NULL
*/
Game* GameCreate(Player* _players[], size_t _numOfPackets, size_t _numOfTricks,size_t _numOfPlayers, size_t _maxScore);

/**
@Brief: This method destroy a game

@params:
		_game: pointer to game
*/
void GameDestroy(Game* _game);

/**
@Brief: This method start the game

@params:
		_game: pointer to game

return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_ALLOCATION_FAILED
*/
ADTErr GameStart(Game* _game);

#endif
