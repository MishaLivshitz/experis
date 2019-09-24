/** @file Cards.c
 *  @brief Card catalog description and access functions
 *
 *  @author Alex Katz 12/9/2018
 *
 *  @bug No known bugs.
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "TTY.h"
#include "cards.h"

#define VALID_SUIT(S)		((S) < NUM_OF_SUITS)
#define VALID_RANK(R)		((R) < NUM_OF_RANKS)
#define VALID_CARD(IDX)		((IDX) < NUM_OF_CARDS)

typedef struct
{
	Suit	m_suit;
	Rank	m_rank;
} Card;

/* the card catalogue */
static Card s_Cards[NUM_OF_CARDS];

/* for UI */
static char* s_Suit[NUM_OF_SUITS] = { CHR_CLUB, CHR_DIAMOND, CHR_HEART, CHR_SPADE };
static char* s_Rank = "23456789TJQKA";

/**
 * @brief Global initializer for cards catalogue
 * Multiple calls will not change anything
 */
void CardsInit()
{
	Suit s;
	Rank r;
	CardID c;

	for (c = s = 0; s < NUM_OF_SUITS; s++)
	{
		for (r = 0; r < NUM_OF_RANKS; r++, c++)
		{
			s_Cards[c].m_suit = s;
			s_Cards[c].m_rank = r;
		}
	}
}


/**
 * @brief Return Suit / Rank of a card
 * @return Suit / Rank of the card
 */
Suit CardsGetSuit (CardID _cardID)
{
	assert(VALID_CARD(_cardID));
	return s_Cards[_cardID].m_suit;
}

Rank CardsGetRank (CardID _cardID)
{
	assert(VALID_CARD(_cardID));
	return s_Cards[_cardID].m_rank;
}

/**
 * @brief Return Id of a specific Card
 * @return card ID
 */
int  CardsGetId(Suit _suit, Rank _rank)
{
	assert(VALID_SUIT(_suit) && VALID_RANK(_rank));
	return _suit * NUM_OF_RANKS + _rank;
}

/**
 * @brief Print cards
 */
void CardsPrintCard(CardID _cardID)
{
	
	if(!strcmp(s_Suit[CardsGetSuit(_cardID)],CHR_HEART) ||
		!strcmp(s_Suit[CardsGetSuit(_cardID)],CHR_DIAMOND))
	{
		printf("%s%s%s %c",
		TXT_RED
		,s_Suit[CardsGetSuit(_cardID)]
		,TXT_NORMAL
		,s_Rank[CardsGetRank(_cardID)]);	
	}
	else
	{
		printf("%s%s%s %c",
		TXT_BLUE
		,s_Suit[CardsGetSuit(_cardID)]
		,TXT_NORMAL
		,s_Rank[CardsGetRank(_cardID)]);
	}
}

void CardsPrintCatalog()
{
	CardID  i;

	printf("Cards Catalogue = {");
	for (i = 0; i < NUM_OF_CARDS; i++)
	{
		CardsPrintCard(i);
		putchar((i+1 < NUM_OF_CARDS) ? ',' : '}');
	}
	putchar('\n');
}

void CardsPrintVector(Vector* _vec, const char* _prefix)
{
	int  i;
	CardID card;
	size_t nCards = 0;
	 
	VectorItemsNum(_vec,&nCards);

	printf("%s {", _prefix);

	for (i = 1; i <= nCards; i++)
	{
		VectorGet((Vector*)_vec, i, &card);
		CardsPrintCard(card);
		if (i < nCards)
			putchar(',');
	}

	putchar('}');
}

