#include "player.h"
#include "cards.h"
#include "utils.h"
#include "search.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Player
{
	Player_Type m_type;
	Vector* m_hand[NUM_OF_SUITS];
	char m_name[1];
};

static void EscapeDestroy(Player* _player, size_t _index)
{
	while(_index>=0)
	{
		VectorDestroy(_player->m_hand[_index--]);
	}
	free(_player);
}

Player* PlayerCreate(char* _name, size_t _position, Player_Type _plType)
{
	
	Player* player;
	int i;
	size_t nameLen = strlen(_name);
	
	player = (Player*)malloc(sizeof(Player)+sizeof(char)*nameLen);
	if(!player) 
	{
		return player;
	}

	for(i=0;i<NUM_OF_SUITS;i++)
	{
		if(NULL==(player->m_hand[i]=VectorCreate(NUM_OF_RANKS,0)))
		{
			EscapeDestroy(player,i);
			return NULL;
		}
	}
	
	strcpy(player->m_name,_name);
	player->m_type = _plType;
	
	return player;
}

void PlayerDestroy(Player* _player)
{
	int i;
	
	if(NULL==_player)
	{
		return;
	}
	
	for(i=0;i<NUM_OF_SUITS;i++)
	{
		VectorDestroy(_player->m_hand[i]);
	}
	
	free(_player);
}

static size_t FindPlaceToInsert(Vector* _suitVec, CardID _newCardID)
{
	size_t i=1;
	int value;
	
	while(ERR_OK == VectorGet(_suitVec,i,&value))
	{
		if(value > _newCardID)
		{
			break;
		}
		 
		i++;
	} 
	
	return i;
}

static Pair FindMax(Vector* _hand[])
{
	size_t suitSize;
	size_t i;

	int currItem=0;
	Pair itemMax = {0,0};
	
	for(i=0;i<NUM_OF_SUITS;i++)
	{
		VectorItemsNum(_hand[i],&suitSize);
		
		if(!suitSize)
		{
			continue;
		}
		
		VectorGet(_hand[i],suitSize,&currItem);
		
		if(CardsGetRank(currItem)>CardsGetRank(itemMax.m_val))
		{
			itemMax.m_index = i;
			itemMax.m_val = currItem;
		}
	}
	
	return itemMax;
}

static CardID FindMin(Vector* _hand[],int* _isHeartsValid)
{
	Pair itemMin = {0,NUM_OF_CARDS-1};
	size_t i;
	size_t suitSize;
	int currItem=-1;
	
	for(i=0;i<NUM_OF_SUITS;i++)
	{
		VectorItemsNum(_hand[i],&suitSize);
		
		if(!suitSize || (SUIT_HEARTS == i && !*_isHeartsValid))
		{
			continue;
		}

		VectorGet(_hand[i],1,&currItem);
		
		if(CardsGetRank(currItem)<=CardsGetRank(itemMin.m_val))
		{
			itemMin.m_index = i;
			itemMin.m_val = currItem;
		}
	}
	
	if(currItem == -1)
	{
		itemMin.m_index = SUIT_HEARTS;
		VectorGet(_hand[itemMin.m_index],1,&itemMin.m_val);
		*_isHeartsValid = TRUE;
	}
	
	return itemMin.m_val;
}

static void BubbleItem(Vector* _suitVec, int _begin, int _end)
{
	Pair item1,item2;
	int advencment;

	advencment = _begin<=_end ? 1: -1;
	
	while(_begin != _end)
	{
		item1.m_index = _begin;
		VectorGet(_suitVec,item1.m_index,&item1.m_val);
		item2.m_index = _begin+advencment;
		VectorGet(_suitVec,item2.m_index,&item2.m_val);
		Swap(_suitVec,&item1,&item2);
		_begin+=advencment;	
	}
}

static void ExtractCard(Vector* _suitVec,size_t _numOfCards, size_t _index,CardID* _returnedCard)
{
	CardID first,last;

	VectorGet(_suitVec,_index,&first);
	VectorGet(_suitVec,_numOfCards,&last);
	VectorSet(_suitVec,_index,last);
	VectorSet(_suitVec,_numOfCards,first);
	
	VectorDelete(_suitVec,_returnedCard);
	BubbleItem(_suitVec,_index,_numOfCards-1);
	
}

ADTErr PlayerTakeCard(Player* _player, CardID _newCardID)
{
	size_t place,numOfItems;
	Vector* suitVec;
	
	if(NULL==_player || NULL == _player->m_hand || NULL == (suitVec = _player->m_hand[CardsGetSuit(_newCardID)]))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	place = FindPlaceToInsert(suitVec, _newCardID);
	VectorAdd(suitVec,_newCardID);
	VectorItemsNum(suitVec,&numOfItems);
	BubbleItem(suitVec,numOfItems,place);
	
	return ERR_OK;
}

CardID PlayerGiveCard(Player* _player,int* _isHeartsValid, CardID _leadCard)
{
	size_t numOfCards;
	Vector* suitVec;
	
	CardID returnedCard;
	
	if(NULL==_player || NULL == _player->m_hand || NULL == (suitVec = _player->m_hand[CardsGetSuit(_leadCard)]))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(suitVec, &numOfCards);
	
	if(!numOfCards || _leadCard== -1)
	{	
		returnedCard = FindMin(_player->m_hand,_isHeartsValid);
		suitVec = _player->m_hand[CardsGetSuit(returnedCard)];
		VectorItemsNum(suitVec, &numOfCards);
	}
	
	ExtractCard(suitVec,numOfCards,1,&returnedCard);
	
	return returnedCard;
}

int PlayerHasCard(Player* _player,CardID _cardID)
{
	size_t index;
	
	if(ERR_OK == BinarySearch(_player->m_hand[CardsGetSuit(_cardID)],_cardID,&index))
	{
		return index;
	}
	
	return 0;
}

void PlayerDiscardCard(Player* _player ,size_t _amount, CardID _cards[])
{
	size_t i;
	Pair itemMax;
	
	for(i=0; i<_amount;i++)
	{
		 itemMax = FindMax(_player->m_hand);
		 VectorDelete(_player->m_hand[itemMax.m_index],&_cards[i]);
	}
}

void PlayerPrint(Player* _player)
{
	int i;
	
	if(NULL==_player)
	{
		return;
	}
	
	printf("%s \n", _player->m_name);
	
	for(i=0;i<NUM_OF_SUITS;i++)
	{
		CardsPrintVector(_player->m_hand[i],"");
	}
	printf("\n");
}

void PlayerPrintName(Player* _player)
{
	if(NULL==_player)
	{
		return;
	}
	
	printf("%s",_player->m_name);
}
