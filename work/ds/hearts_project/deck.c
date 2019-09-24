#include "cards.h"
#include "vector.h"
#include "deck.h"
#include "utils.h"

#define ZERO_EXTENTION 0
#define DECK_PREFIX "Current Deck:"
#define ACTIVE_MAGIC_NUM 0xdecdec

#define IS_VALID(D)		((D) && (D)->m_magicNum == ACTIVE_MAGIC_NUM)
#define CARDS(D) (D)->m_cards

struct Deck
{
	int m_magicNum;
	Vector* m_cards;
};

Deck* DeckCreate(size_t _numOfPackets)
{
	Deck* deck;
	int i=0;
	
	if(NULL == (deck=(Deck*)calloc(1,sizeof(Deck))))
	{
		return NULL;
	}
	
	if(NULL==(CARDS(deck)=VectorCreate(_numOfPackets * NUM_OF_CARDS,0)))
	{
		free(deck);
		return NULL;
	}
	
	while(ERR_OK==VectorAdd(CARDS(deck),i++ % NUM_OF_CARDS))
	{}

	deck->m_magicNum = ACTIVE_MAGIC_NUM;
	return deck;
}

void DeckDestroy(Deck* _deck)
{
	if (IS_VALID(_deck))
	{
		_deck->m_magicNum = -1;
		VectorDestroy(CARDS(_deck));
		free(_deck);
	}
}

ADTErr DeckShuffle(Deck* _deck)
{
	size_t numOfCards;
	Pair item1,item2;
	
	if(!IS_VALID(_deck))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(CARDS(_deck),&numOfCards);

	srand(time(NULL));
	while(numOfCards > 1)
	{
		item1.m_index = numOfCards--;
		VectorGet(CARDS(_deck), item1.m_index, &item1.m_val);

		item2.m_index = rand() % numOfCards + 1;
		VectorGet(CARDS(_deck), item2.m_index, &item2.m_val);
		
		Swap(CARDS(_deck), &item1, &item2);
	}
	
	return ERR_OK;
}

ADTErr DeckAddCard(Deck* _deck, CardID _card)
{
	if(!IS_VALID(_deck))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return VectorAdd(CARDS(_deck),_card);
}

ADTErr DeckRemoveCard(Deck* _deck, CardID* _card)
{
	if(!IS_VALID(_deck))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return VectorDelete(CARDS(_deck),_card);
}

int DeckIsEmpty(Deck* _deck)
{
	size_t numOfCards;
	ADTErr status;
	
	if(!IS_VALID(_deck))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(ERR_OK != (status=VectorItemsNum(CARDS(_deck),&numOfCards)))
	{
		return TRUE;
	}
	
	return numOfCards == 0;
}

void DeckPrint(Deck* _deck)
{
	if(!IS_VALID(_deck))
	{
		return;
	}
	
	CardsPrintVector(CARDS(_deck),DECK_PREFIX);
}


