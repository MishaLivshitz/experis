#include "MyMalloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define IS_FIT(B,S)			(int)(S) <= (int)((B)->m_size)
#define IS_FREE(B)			(B)->m_size > 0
#define NEXT_BLOCK(B,S)		((Block*)((Byte*)(B) + (S)) + 1)	


/*#define MIN_SIZE 			sizeof(Manager) + sizeof(Block) + sizeof(Block) * 5*/

typedef char Byte;

typedef struct Block 
{
	int 	m_size;
	
}Block;

typedef struct Manager
{
	int 	m_maxSize;
	Block* 	m_firstBlock;
	/* TODO:	remove firstBlock:
	 * 					consider adding Macro to get the first block
	 * */
	
}Manager;

static Block* ConvertToMyBlock(void* _userBlock)
{
	Block* myBlock = _userBlock;
	
	assert(myBlock);
	myBlock--;
	
	return myBlock;
}

static int IsInRagne(Manager* _man, Block* _block)
{
	assert(_man);
	assert(_block);
	return (Byte*)_man->m_firstBlock + _man->m_maxSize > (Byte*)_block;
	
}

static void AttachFreeBlocks(Manager* _myBuff,Block* _block)
{
	Block* nextBlock;
	
	assert(IS_FREE(_block));
	
	nextBlock = NEXT_BLOCK(_block,_block->m_size);
	while(IsInRagne(_myBuff,nextBlock) && IS_FREE(nextBlock))
	{
		_block->m_size += nextBlock->m_size;
		nextBlock = NEXT_BLOCK(_block,_block->m_size);;
	}			
}

static void* ExtractUserBlock(Block* _currBlock, size_t _nBytes)
{
	assert(IS_FREE(_currBlock));
	if(_currBlock->m_size >  _nBytes)
	{
		NEXT_BLOCK(_currBlock,_nBytes)->m_size = _currBlock->m_size - _nBytes - sizeof(Block);
	}
	_currBlock->m_size = -1*_nBytes;
	_currBlock++;
	
	return _currBlock;
}



void* MyMallocInit(void* _membuf, size_t _nBytes)
{
	Manager* myBuff = (Manager*)_membuf;
	
	if(!myBuff || !_nBytes)
	{
		return NULL;
	}
	
	/*TODO: 
	 * 		1. Alignment
	 * 		2. Init last block to 0 size
	 * 		
	 * */	
	
	myBuff->m_maxSize = _nBytes - sizeof(Manager);
	myBuff->m_firstBlock = (Block*)(myBuff + 1);
	myBuff->m_firstBlock->m_size = myBuff->m_maxSize - sizeof(Block);
	
	return myBuff;
}

void* MyMalloc(void* _membuf, size_t _nBytes)
{

	Block* currBlock;
	Manager* myBuff = (Manager*)_membuf;
	
	if(!myBuff)
	{
		return NULL;
	}
	
	currBlock = myBuff->m_firstBlock;
	
	do
	{
		if(IS_FREE(currBlock))
		{
			AttachFreeBlocks(myBuff,currBlock);
			if(IS_FIT(currBlock,_nBytes))
			{
				return ExtractUserBlock(currBlock,_nBytes);;
			}
			else
			{
				currBlock = NEXT_BLOCK(currBlock,currBlock->m_size);
			}		
		}
		else
		{
			currBlock = NEXT_BLOCK(currBlock,-1*currBlock->m_size);
		}
	
	} while(IsInRagne(myBuff,currBlock));
	
	return NULL;
}

void MyFree(void* _ptr)
{
	Block* myBlock;
	
	if(!_ptr)
	{
		return;
	}
	
	myBlock = ConvertToMyBlock(_ptr);
	if(myBlock->m_size<0)
	{
		myBlock->m_size *= -1;	
	}
	
	/*TODO: change line 148 to Macro -> SET_AS_FREE*/
	/*TODO: consider defrag!*/
	/*TODO: What if already free?!?!*/
}

#ifdef  DEBUG
/* Debugging support functions */
void	MyMallocPrint(void* _membuf)
{
	Manager* myBuff = (Manager*)_membuf;
	size_t i=1;
	Block* currBlock = myBuff->m_firstBlock;
	do
	{
		if(currBlock->m_size)
		{
			if(IS_FREE(currBlock))
			{
				printf("Block size #%ld = %d\n",i++,currBlock->m_size);
				currBlock = NEXT_BLOCK(currBlock,currBlock->m_size);
			}
			else
			{
				printf("Block size #%ld = %d\n",i++,currBlock->m_size);
				currBlock = (Block*)((Byte*)currBlock + (-1*currBlock->m_size)) + 1;
			}
		}
		else
		{
				currBlock = NEXT_BLOCK(currBlock,-1*currBlock->m_size);
		}
	}while(IsInRagne(myBuff,currBlock));
	puts("");
}
#endif /* DEBUG */
