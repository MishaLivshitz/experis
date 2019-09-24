/** @file Cards.h
 *  @brief Card catalog description and access functions
 *
 *  @author Alex Katz 12/9/2018
 *
 *  @bug No known bugs.
 */
#ifndef __CARDS_H__
#define __CARDS_H__

#include "vector.h"

#define	NUM_OF_CARDS	(NUM_OF_SUITS * NUM_OF_RANKS)

typedef int CardID;

/* Suits */
typedef enum
{
	 SUIT_CLUBS
	,SUIT_DIAMONDS
	,SUIT_HEARTS
	,SUIT_SPADES
	,NUM_OF_SUITS
} Suit;

/* Ranks */
typedef enum
{
	 RANK_TWO
	,RANK_THREE
	,RANK_FOUR
	,RANK_FIVE
	,RANK_SIX
	,RANK_SEVEN
	,RANK_EIGHT
	,RANK_NINE
	,RANK_TEN
	,RANK_JACK
	,RANK_QUEEN
	,RANK_KING
	,RANK_ACE
	,NUM_OF_RANKS
} Rank;


/**
 * @brief Global initializer for cards catalogue
 * Multiple calls will not change anything
 */
void CardsInit();

/**
 * @brief Return Suit / Rank of a card
 * @param[in] _id: card ID (number)
 * @return Suit / Rank of the card
 */
Suit CardsGetSuit (CardID _cardID);
Rank CardsGetRank (CardID _cardID);

/**
 * @brief Return Id of a specific Card
 * @param[in] _suit: card suit
 * @param[in] _rand: card id
 * @return card ID
 */
CardID  CardsGetId(Suit _suit, Rank _rank);

/**
 * @brief Print representation of a given Card, catalog or container
 * @param[in] _id
 */
void CardsPrintCard(CardID _cardID);
void CardsPrintCatalog();

/**
 * @brief Print contents of Vector CardID container
 * @param[in]	_vector containter to print contents
 * @param[in]	_prefix - any string to print before the contents
 */
void CardsPrintVector(Vector* _vector, const char* _prefix);

#endif /*__CARD_H__*/
