/*
This module responsible for all the methods of a deck
Author: Michael Livshitz
*/

#ifndef _DECK_H_
#define _DECK_H_

#include <time.h>
#include <stddef.h>		/* size_t */
#include "cards.h"
#include "ADTErr.h"

typedef struct Deck Deck;

/**
@Brief: This method create a deck

@params:
		_initSize: initial size
		_extBlock:	extension block

@warning: both cannot be zero

@return: pointer to deck when success else return NULL
*/
Deck* DeckCreate(size_t _numOfPackets);

/**
This method destroy a deck

@params:
		_deck: pointer to deck
	
*/
void DeckDestroy(Deck* _deck);

/**
@Brief: This method add a card to the deck

@Params:
		_deck:deck
		_card: a card to add

@return: ERR_OK when success else return ERR_NOT_INITIALIZED or ERR_REALLOCATION_FAILED
*/
ADTErr DeckAddCard(Deck* _deck, CardID _card);

/**
@Brief: This method removes card from the Deck

@Params:
		_deck:deck
		_card: a place to return a card

if _card is NULL no card will be returned

@return: ERR_OK when success else return ERR_NOT_INITIALIZED or ERR_REALLOCATION_FAILED
*/
ADTErr DeckRemoveCard(Deck* _deck, CardID* _card);

/**
	@Brief: This method shuffle the deck
 
	@Params: _deck
 
	retrun ERR_OK when SUCCESS else return ERR_NOT_INITIALIZED
 */
ADTErr DeckShuffle(Deck* _deck);
/**
@Brief: This method check if the deck is empty

@Params: _deck: deck

@return: TRUE if deck is empty else retrun FALSE
*/
int DeckIsEmpty(Deck* _deck);

/**
@brief: This method print a deck 

@params: 
		_deck: pointer to a deck

*/
void DeckPrint(Deck* _deck);

#endif
