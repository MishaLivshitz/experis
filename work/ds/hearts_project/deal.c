#include <stdio.h>
#include <stdlib.h>
#include "deal.h"
#include "cards.h"
#include "deck.h"
#include "player.h"
#include <assert.h>

#define ACTIVE_MAGIC_NUM 0xdeadea
#define CARDS_TO_EXCHANGE 3
#define EXCHANGE_LEFT(x,y) (x)-1 < 0 ? (y)-1: (x)-1
#define EXCHANGE_RIGHT(x,y) (x) + 1 == (y) ? 0: (x) + 1
#define EXCHANGE_ACRROS(x,y) (x) + (y)/2
#define	NUM_OF_PLAYERS 4
#define IS_VALID(D)		((D) && (D)->m_magicNum == ACTIVE_MAGIC_NUM)

struct Deal
{
	int m_magicNum;
	CardID* m_trick;
	size_t m_numOfPlayers;
	size_t m_numOfTricks;
	Player** m_players;
};

static void GiveCardsToPlayers(Player* _players[],Deck* _deck, size_t _numOfPlayers)
{
	size_t i;
	CardID cardID;
	while(!DeckIsEmpty(_deck))
	{
		for(i=0;i<_numOfPlayers;i++)
		{
			DeckRemoveCard(_deck,&cardID);
			PlayerTakeCard(_players[i],cardID);
		}
	}
}

static void PlayersExchange(Player* _players[], size_t _numOfPlayers, XchgMode _mode)
{
	int i,j;
	CardID playersCards[NUM_OF_PLAYERS][CARDS_TO_EXCHANGE];
	
	if(_mode == XCHG_NONE)
	{
		return;
	}
	
	for(i=0;i<_numOfPlayers;i++)
	{
		PlayerDiscardCard(_players[i], CARDS_TO_EXCHANGE, playersCards[i]);
	}
	
	switch(_mode)
	{
		case XCHG_LEFT:
			for(i=0;i<_numOfPlayers;i++)
			{
				for(j=0;j<CARDS_TO_EXCHANGE;j++)
				{
					PlayerTakeCard(_players[i],playersCards[EXCHANGE_LEFT(i,_numOfPlayers)][j]);
				}
			}
			break;
		case XCHG_RIGHT:
		
			for(i=0;i<_numOfPlayers;i++)
			{
				for(j=0;j<CARDS_TO_EXCHANGE;j++)
				{
					PlayerTakeCard(_players[i],playersCards[EXCHANGE_RIGHT(i,_numOfPlayers)][j]);
				}
			}
			
			break;
		case XCHG_ACROSS:
			for(i=0;i<_numOfPlayers/2;i++)
			{
				for(j=0;j<CARDS_TO_EXCHANGE;j++)
				{
					PlayerTakeCard(_players[i],playersCards[EXCHANGE_ACRROS(i,_numOfPlayers)][j]);
					PlayerTakeCard(_players[EXCHANGE_ACRROS(i,_numOfPlayers)],playersCards[i][j]);
				}
			}
			break;
			
		default:
		break;
	}
}

static size_t ChooseOpener(Player* _players[], CardID _cardID)
{
	size_t i;
	
	for(i=0;i<NUM_OF_PLAYERS;i++)
	{
		if(PlayerHasCard(_players[i],_cardID))
		{
			break;
		}
	}
	
	return i;
}

Deal* DealCreate(Player* _players[], size_t _numOfTricks, size_t _numOfPlayers)
{
	Deal* deal;
	
	if(NULL == (deal = (Deal*)calloc(1,sizeof(Deal))))
	{
		return NULL;
	}
	
	if(NULL == (deal->m_trick=(CardID*)calloc(_numOfPlayers,sizeof(CardID))))
	{
		free(deal);
		return NULL;
	}
	
	deal->m_numOfTricks = _numOfTricks;
	deal->m_players = _players;
	deal->m_numOfPlayers = _numOfPlayers;
	deal->m_magicNum = ACTIVE_MAGIC_NUM;
	return deal;
}

void DealDestroy(Deal* _deal)
{
	if(IS_VALID(_deal))
	{	
		_deal->m_magicNum = -1;
		free(_deal->m_trick);
		free(_deal);
	}
}

static size_t CalcScore(CardID trick[],size_t _scores[],int _numOfPlayers, CardID _leadCard)
{
	const Suit leadCardSuit = CardsGetSuit(_leadCard);
	Rank leadCardRank = CardsGetRank(_leadCard);
	Suit currCardSuit;
	Rank currCardRank;
	size_t loserIndex=0;
	
	while(--_numOfPlayers >= 0)
	{
		currCardSuit = CardsGetSuit(trick[_numOfPlayers]);
		currCardRank = CardsGetRank(trick[_numOfPlayers]);
		
		if(currCardSuit==leadCardSuit && currCardRank > leadCardRank)
		{
			leadCardRank = trick[_numOfPlayers];
			loserIndex = _numOfPlayers;
		}
		if(currCardSuit == SUIT_HEARTS)
		{
			_scores[_numOfPlayers]++;
		}
		if(currCardSuit == SUIT_SPADES && currCardRank == RANK_QUEEN)
		{
			_scores[_numOfPlayers]+=NUM_OF_RANKS;
		}
	}
	
	return loserIndex;
}

static void PlayTrick(Deal* _deal,size_t _leaderIndex,CardID _leadCard, int* isHeartValid)
{
	size_t i,j;
	
	for(j=0 ,i=_leaderIndex%_deal->m_numOfPlayers; j<NUM_OF_PLAYERS; i=(i+1)%_deal->m_numOfPlayers,j++)
	{
		_deal->m_trick[i] = PlayerGiveCard(_deal->m_players[i],isHeartValid,_leadCard);
		if(_leadCard==-1)
		{
			_leadCard=_deal->m_trick[i];
		}
	}
}

static void ReturnCardsToDeck(Deal* _deal, Deck* _deck)
{
	size_t i;
	
	for(i=0;i<NUM_OF_PLAYERS;i++)
	{
		DeckAddCard(_deck,_deal->m_trick[i]);
		_deal->m_trick[i] = -1;
	}
}

ADTErr DealPlay(Deal* _deal, Deck* _deck ,XchgMode _mode ,size_t _scores[])
{
	
	size_t trickNum=0;
	size_t leaderIndex=0;
	int isHeartValid = FALSE;
	CardID leadCard = RANK_TWO * SUIT_CLUBS;
	
	if(!IS_VALID(_deal) || NULL == _scores)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	DeckShuffle(_deck);
	GiveCardsToPlayers(_deal->m_players, _deck, _deal->m_numOfPlayers);
	PlayersExchange(_deal->m_players,_deal->m_numOfPlayers,_mode);
	
	leaderIndex = ChooseOpener(_deal->m_players,leadCard);
	
	while(trickNum<_deal->m_numOfTricks)
	{	
		
		PlayTrick(_deal, leaderIndex, leadCard, &isHeartValid);	
		leaderIndex = CalcScore(_deal->m_trick,_scores,_deal->m_numOfPlayers,leadCard);
		
		ReturnCardsToDeck(_deal,_deck);
		trickNum++;
		leadCard = -1;
	}
	
	return ERR_OK;
}
