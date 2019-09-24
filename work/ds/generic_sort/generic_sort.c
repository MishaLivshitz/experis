#include "generic_sort.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BYTE_CAST(E)		((Byte*)(E))
#define BEGIN_INDEX 0  
#define END_INDEX(N,I)		(N)-(I)-1

typedef char Byte;


static void Swap(void* _a, void* _b, size_t _elemSize)
{
	void* temp= malloc(_elemSize);

	if(temp)
	{		
		memcpy(temp,_a,_elemSize);
		memcpy(_a,_b,_elemSize);
		memcpy(_b,temp,_elemSize);
		free(temp);
	}
}

static int BubbleUp(void* _elements, size_t _elemSize, size_t _begin, size_t _end, int(*_less)(const void*, const void*))
{
	int isSwaped=0;

	_end *= _elemSize;
	_begin *= _elemSize;

	for(_begin *= _elemSize;_begin<_end;_begin+=_elemSize)
	{
		if(_less(&BYTE_CAST(_elements)[_begin],&BYTE_CAST(_elements)[_begin+_elemSize]))
		{
			Swap(&BYTE_CAST(_elements)[_begin],&BYTE_CAST(_elements)[_begin+_elemSize], _elemSize);
			isSwaped = 1;
		}
	}

	return isSwaped;
}

int Sort(void* _elements, size_t _n, size_t _elemSize, int(*_less)(const void*, const void*))
{
	size_t i;
	
	for(i=0;i<_n;i++)
	{
		if(!BubbleUp(_elements,_elemSize,BEGIN_INDEX,END_INDEX(_n,i),_less))
			{
				break;
			}
	}

	return 1;
}
