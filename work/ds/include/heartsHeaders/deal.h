/*
This module responsible for all the methods of a deal
Author: Michael Livshitz
*/

#ifndef _DEAL_H_
#define _DEAL_H_

#include <stddef.h>		/* size_t */
#include "player.h"
#include "ADTErr.h"
#include "vector.h"
#include "deck.h"

typedef enum
{
	XCHG_LEFT = 0,
	XCHG_RIGHT,
	XCHG_ACROSS,
	XCHG_NONE,
	NUM_OF_MODES
} XchgMode;


typedef struct Deal Deal;
/**

	@Brief:This method create deal

	@params: 
		_players: players
		_numOfTricks: number of tricks per deal
		_numOfPlayers: number of players

	@return: pointer to deal when success else return NULL
*/
Deal* DealCreate(Player* _players[], size_t _numOfTricks, size_t _numOfPlayers);
/**
	@Brief: This method destroy a deal

	params:
		_deal: pointer to deal
*/
void DealDestroy(Deal* _deal);

/**
	@Brief: This method runs the deal and return the scores

	@Params:
			_deal: pointer to deal
			_deck: deck of cards
			_mode: exchange mode
			_scores:place to return the scores

	@return: ERR_OK when success else return ERR_NOT_INITIALIZED
*/
ADTErr DealPlay(Deal* _deal, Deck* _deck ,XchgMode _mode ,size_t _scores[]);


#endif
