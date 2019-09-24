/*
This module responsible for all the methods of a player
Author: Michael Livshitz
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stddef.h>		/* size_t */
#include "ADTErr.h"
#include "cards.h"


typedef struct Player Player;

typedef enum 
{
	 BOT
	,HUMAN
}Player_Type;


/**
@brief: This method create a player

@parmas:
		_name: player name
		_position: player position on the table

@return pointer to a new player when success else return NULL
*/
Player* PlayerCreate(char* _name, size_t _position, Player_Type _plType);

/**
@brief: This method destory a player

@params: 
		_player: pointer to a player

*/
void PlayerDestroy(Player* _player);

/**
@Brief: This method get card from the deck

@Params:
	_player: pointer to a player
	_newCardID: a card id to add;

@return: ERR_OK when SUCCESS else ERR_NOT_INITIALIZED
*/
ADTErr PlayerTakeCard(Player* _player, CardID _newCardID);

/**
@Brief:This method give a card

@Params: 
		_player: pointer to a player
		_leadCard: current lead card
		_isHeartsValid: flag for validnace of hearts

@return: chosen card if success else NULL
*/
CardID PlayerGiveCard(Player* _player,int* _isHeartsValid, CardID _leadCard);

/**
 @Brief: This method check whether the player has a specific card
 
 @params: 
		_player: player
		_cardID: the card to look for
		
 @return TRUE if found else FALSE
*/
int PlayerHasCard(Player* _player, CardID _cardID);

/**
	@Brief: This method is discard cards from players' hand
	
	@Params:
			_player: player
			_amount: number of cards to discard
			_cards: place to return the discard cards
*/
void PlayerDiscardCard(Player* _player ,size_t _amount,CardID _cards[]);
/**
	@Brief: This method prints The name of a player
	
	@params:
			_player: player
			_name: place to return the name

*/
void PlayerPrintName(Player* _player);
/**
@brief: This method print a player data

@params: 
		_player: pointer to a player

*/
void PlayerPrint(Player* _player);


#endif
