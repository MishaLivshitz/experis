#include "ADTErr.h" 
#include "sort.h"
#include <assert.h>

#define NDEBUG

typedef enum
{
	SHAKE_SORT,
	BUBBLE_SORT,
	INSERTION_SORT,
	SHELL_SORT,
	MERGE_SORT
}SortType;

typedef enum
{
	UP,
	DOWN
}BubbleDirection;

typedef struct pair
{
	size_t m_index;
	int m_val;
}Pair;

typedef struct bubbleParams
{
	SortType m_sortType;
	BubbleDirection m_direction;
	int m_gap;
	size_t m_indexStart;
	size_t m_indexEnd;

}BubbleParams;

static void SwapVector(Vector* _vec,Pair _a, Pair _b)
{
	VectorSet(_vec,_a.m_index,_b.m_val);
	VectorSet(_vec,_b.m_index,_a.m_val);
}

static void SwapPairVal(Vector* _vec,Pair* _a, Pair* _b)
{
	size_t temp = _a->m_val;
	
	SwapVector(_vec,*_a,*_b);
	_a->m_val = _b->m_val;
	_b->m_val = temp;
}


static void CopyPartOfVec(Vector* _sourceVec,Vector* _destVec, size_t _start,size_t _end)
{
	int item;
	while(_start<=_end)
	{
		VectorGet(_sourceVec,_start,&item);
		VectorSet(_destVec,_start++,item);
	}
}

static int BubbleIteration(Vector* _vec,int _gap, char _myXor,size_t _begin)
{
	Pair item1,item2;
	int isSwaped = FALSE;

	item1.m_index=_begin;
	item2.m_index=_begin+_gap;
	VectorGet(_vec,item1.m_index,&item1.m_val);
	VectorGet(_vec,item2.m_index,&item2.m_val);
	
	if((item2.m_val>item1.m_val)^_myXor && item2.m_val!=item1.m_val)
	{
		SwapVector(_vec,item1,item2);
		isSwaped = TRUE;
	}

	return isSwaped;
}

static int BubbleItem(Vector* _vec,const BubbleParams* const _bubbleParams)
{
	size_t begin = _bubbleParams->m_indexStart;
	size_t end = _bubbleParams->m_indexEnd;
	int isSwaped = FALSE;
	int advancement = 1;
	int gap = _bubbleParams->m_gap;
	char myXor=1;
	
	if(DOWN==_bubbleParams->m_direction)
	{
		begin = _bubbleParams->m_indexEnd;
		end = _bubbleParams->m_indexStart;
		advancement *= -1;
		gap *= -1;
		myXor = 0;
	}

	switch(_bubbleParams->m_sortType)
	{
		case SHELL_SORT:
			while(begin+gap <= end)
			{
				BubbleIteration(_vec,gap,myXor,begin);
				begin+=advancement;
			}
			break;
		case MERGE_SORT:
		case INSERTION_SORT:
			while(begin!=end && (isSwaped=BubbleIteration(_vec,gap,myXor,begin)))
			{
				begin+=advancement;
			}
			break;

		default:
			while(begin!=end)
			{
				isSwaped|=BubbleIteration(_vec,gap,myXor,begin);
				begin+=advancement;
			}
	}

	return isSwaped;
}

static void InsertPivotInRightPlace(Vector* _vec ,Pair* _itemToSmall,Pair* _itemToBig, Pair* _itemPivot,size_t _pivotIndex, size_t _endIndex)
{
	ADTErr status;

	while(_itemToSmall->m_index>_itemToBig->m_index)
		{
			while(_itemToBig->m_val<=_itemPivot->m_val && _itemToBig->m_index < _endIndex)
			{
				_itemToBig->m_index++;
				status = VectorGet(_vec,_itemToBig->m_index,&_itemToBig->m_val);
				assert(status ==ERR_OK);
			}
			
			while(_itemToSmall->m_val>_itemPivot->m_val && _itemToSmall->m_index > _itemPivot->m_index)
			{
				_itemToSmall->m_index--;
				status = VectorGet(_vec,_itemToSmall->m_index,&_itemToSmall->m_val);
				assert(status ==ERR_OK);
			}
			
			if(_itemToBig->m_index<_itemToSmall->m_index)
			{
				SwapPairVal(_vec,_itemToBig,_itemToSmall);
			}
		}

		SwapVector(_vec,*_itemPivot,*_itemToSmall);	
}

static Pair FindMinPair(Vector* _vec,size_t _startIndex,size_t _size)
{
	int newVal;
	Pair minItem;

	minItem.m_index = _startIndex;
	VectorGet(_vec,_startIndex++,&minItem.m_val);
	
	while(_startIndex<=_size)
	{
		VectorGet(_vec,_startIndex,&newVal);
		if(newVal<minItem.m_val)
		{
			minItem.m_val=newVal;
			minItem.m_index = _startIndex; 
		}
		++_startIndex;
	}
	return minItem;
}

ADTErr ShakeSort(Vector* _vec){

	ADTErr status;
	BubbleParams bubbleParams={SHAKE_SORT,UP,INITIAL_GAP,1};
	
	if(ERR_OK!= (status=VectorItemsNum(_vec,&bubbleParams.m_indexEnd)))
	{
		return status;
	}
	
	while(bubbleParams.m_indexStart <= bubbleParams.m_indexEnd)
	{
		bubbleParams.m_direction = UP;
		if(FALSE==BubbleItem(_vec,&bubbleParams))
			{
				break;
			}
		
		bubbleParams.m_indexEnd--;
		bubbleParams.m_direction = DOWN;
		if(FALSE==BubbleItem(_vec,&bubbleParams))
			{
				break;
			}

		bubbleParams.m_indexStart++;
	}

	return status;
}

ADTErr QuickSort(Vector* _vec, size_t _pivotIndex,size_t _endIndex)
{
	Pair itemToSmall, itemToBig, itemPivot;
	ADTErr status;

	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(_pivotIndex > _endIndex)
	{
		return ERR_OK;
	}

	itemPivot.m_index =_pivotIndex;
	itemToBig.m_index =_pivotIndex;
	itemToSmall.m_index = _endIndex; 

	status = VectorGet(_vec,itemPivot.m_index,&itemPivot.m_val);
	status |= VectorGet(_vec,itemToBig.m_index,&itemToBig.m_val);
	status |= VectorGet(_vec,itemToSmall.m_index ,&itemToSmall.m_val);

	InsertPivotInRightPlace(_vec ,&itemToSmall,&itemToBig,&itemPivot,_pivotIndex,_endIndex);
	
	SwapVector(_vec,itemPivot,itemToSmall);	
	status = QuickSort(_vec,_pivotIndex,itemToSmall.m_index-1);
	status |= QuickSort(_vec,itemToSmall.m_index+1,_endIndex);

	return status;
}

ADTErr InsertionSort(Vector* _vec)
{
	ADTErr status;
	size_t numOfItems;
	BubbleParams bubbleParams={INSERTION_SORT,DOWN,INITIAL_GAP,1,2};

	if(ERR_OK!=(status = VectorItemsNum(_vec,&numOfItems)))
	{
		return status;
	}
		
	while(bubbleParams.m_indexEnd <= numOfItems)
	{
		BubbleItem(_vec,&bubbleParams);
		bubbleParams.m_indexEnd++;
	}

	return status;
}

ADTErr ShellSort(Vector* _vec)
{
	BubbleParams bubbleParams={SHELL_SORT,UP,INITIAL_GAP,1};

	if(ERR_OK != VectorItemsNum(_vec,&bubbleParams.m_indexEnd))
	{
		return ERR_GENERAL;
	}

	bubbleParams.m_gap = bubbleParams.m_indexEnd/2;

	while(bubbleParams.m_gap>1)
	{
		BubbleItem(_vec,&bubbleParams);			
		bubbleParams.m_gap/=2;
	}
	
	return InsertionSort(_vec);
}

ADTErr SelectionSort(Vector* _vec)
{
	size_t numOfItems;
	size_t indexStart=1;
	ADTErr status;
	Pair item1, item2;

	if(ERR_OK != (status=VectorItemsNum(_vec,&numOfItems)))
	{
		return status;
	}

	while(indexStart<numOfItems)
	{
		item1.m_index = indexStart;
		VectorGet(_vec,item1.m_index,&item1.m_val);
		item2 = FindMinPair(_vec,indexStart+1,numOfItems);
		if(item2.m_val<item1.m_val)
		{
			SwapVector(_vec,item1,item2);
		}

		++indexStart;
	}

	return ERR_OK;
}

static void MergeInPlace(Vector* _vec,size_t _startIndex,size_t _rightIndex,size_t _endIndex)
{
	Pair itemRight, itemPrev;
	BubbleParams bubbleParams={MERGE_SORT,DOWN,INITIAL_GAP};

	bubbleParams.m_indexStart = _startIndex;
	bubbleParams.m_indexEnd = _rightIndex;
	itemPrev.m_index =_rightIndex-1;
	itemRight.m_index=_rightIndex;

	VectorGet(_vec,itemRight.m_index,&itemRight.m_val);
	VectorGet(_vec,itemPrev.m_index,&itemPrev.m_val);
	
	while(bubbleParams.m_indexEnd<=_endIndex && itemRight.m_val<itemPrev.m_val)
	{
		BubbleItem(_vec,&bubbleParams);
		bubbleParams.m_indexEnd++;
		VectorGet(_vec,++itemRight.m_index,&itemRight.m_val);
		VectorGet(_vec,++itemPrev.m_index,&itemPrev.m_val);
	}
}	
		
static ADTErr MergeSubArray(Vector* _oldVec,Vector* _newVec,size_t _startIndex,size_t _rightIndex,size_t _endIndex)
{
	Pair itemStart, itemRight;
	size_t indexInsert = _startIndex;
	

	itemStart.m_index=_startIndex;
	itemRight.m_index=_rightIndex;	
	VectorGet(_oldVec,itemStart.m_index,&itemStart.m_val);
	VectorGet(_oldVec,itemRight.m_index,&itemRight.m_val);

	while(itemStart.m_index < _rightIndex && itemRight.m_index <= _endIndex)
	{
		if(itemStart.m_val>itemRight.m_val)
		{
			VectorSet(_newVec,indexInsert,itemRight.m_val);
			itemRight.m_index++;
			VectorGet(_oldVec,itemRight.m_index,&itemRight.m_val);
		}
		else
		{
			VectorSet(_newVec,indexInsert,itemStart.m_val);
			itemStart.m_index++;
			VectorGet(_oldVec,itemStart.m_index,&itemStart.m_val);
		}
		indexInsert++;
	}

	/*fill left leftovers*/
	while(itemStart.m_index < _rightIndex)
	{
		VectorSet(_newVec,indexInsert,itemStart.m_val);
		itemStart.m_index++;
		VectorGet(_oldVec,itemStart.m_index,&itemStart.m_val);;
		indexInsert++;
	}

	/*fill right leftovers*/
	while(itemRight.m_index <= _endIndex)
	{
		VectorSet(_newVec,indexInsert,itemRight.m_val);
		itemRight.m_index++;
		VectorGet(_oldVec,itemRight.m_index,&itemRight.m_val);
		indexInsert++;
	}

	return ERR_OK;
}

static ADTErr MergeSortRecRun(Vector* _oldVec,Vector* _newVec,size_t _start,size_t _end,int isInPlace)
{
	size_t numOfItems;
	
	if(_start >= _end)
	{
		return ERR_OK;
	}

	numOfItems = _end - _start;
	MergeSortRecRun(_oldVec,_newVec,_start,MIDDLE(_start,numOfItems),isInPlace);

	if(isInPlace)
	{
		MergeSortRecRun(_oldVec,_newVec,RIGHT(MIDDLE(_start,numOfItems)),_end,isInPlace);
		MergeInPlace(_oldVec,_start,RIGHT(MIDDLE(_start,numOfItems)),_end);
	}
	else
	{
		MergeSortRecRun(_newVec,_oldVec,RIGHT(MIDDLE(_start,numOfItems)),_end,isInPlace);
		MergeSubArray(_oldVec,_newVec,_start,RIGHT(MIDDLE(_start,numOfItems)),_end);
		CopyPartOfVec(_newVec,_oldVec,_start,_end);	
		
		
	}
	return ERR_OK;
}

ADTErr MergeSortRec(Vector* _vec,int isInPlace)
{
	ADTErr status;
	size_t end;
	Vector* newVec = NULL;
		
	if(ERR_OK != (status=VectorItemsNum(_vec,&end)))
	{
		return status;
	}
	
	if(NULL==(newVec = VectorCopy(_vec,newVec)))
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	MergeSortRecRun(_vec,newVec,START_INDEX,end,isInPlace);
	VectorDestroy(newVec);
	return ERR_OK;
}

ADTErr MergeSortIterative(Vector* _vec,int isInPlace)
{
	ADTErr status;
	size_t start=START_INDEX,end, numOfItems,subArraySize=2;
	Vector* newVec = NULL;
		
	if(ERR_OK != (status=VectorItemsNum(_vec,&numOfItems)))
	{
		return status;
	}
	
	if(NULL==(newVec = VectorCopy(_vec,newVec)))
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	while(subArraySize<=numOfItems)
	{
		end = start*subArraySize;
		while(end<=numOfItems)
		{
			MergeSubArray(_vec,newVec,start,MIDDLE(start,subArraySize),end);	
			CopyPartOfVec(newVec,_vec,start,end);
			start+=subArraySize;
			end+=subArraySize;
		}

		if(end > numOfItems && (end-subArraySize) != numOfItems)
		{
			end=numOfItems;
			start-=subArraySize;
			MergeSubArray(_vec,newVec,start,MIDDLE(start,subArraySize*2),end);
			CopyPartOfVec(newVec,_vec,start,end);	
		}

		start=START_INDEX;
		subArraySize*=2;
	}
	
	VectorDestroy(newVec);
	return ERR_OK;
}

static void CountOccurance(Vector* _vec,int* _countArr,size_t _numOfItems,size_t _colExtractor)
{	
	int item,i=1;	

	switch(_colExtractor)
	{
		case ZERO_EXTRACTOR:
			while(ERR_OK==VectorGet(_vec,i++,&item))
			{
				++_countArr[item];
			}
			break;

		default:
			while(ERR_OK==VectorGet(_vec,i++,&item))
			{
				++_countArr[EXTRACT_DIGIT(item,_colExtractor)];
			}
	}
}

static void AccumulateSumOccurances(int* _countArr, int _range)
{
	while(_range--)
	{
		++_countArr;
		*_countArr += *(_countArr - 1);
	}
}

static ADTErr RestoreSorted(Vector* _vec,int*_countArr,size_t _range,size_t _colExtractor)
{
	int item;
	Vector* newVec=VectorCopy(_vec,NULL);

	if(NULL==newVec)
	{
		return ERR_ALLOCATION_FAILED;
	}

	switch(_colExtractor)
	{
		case ZERO_EXTRACTOR:
			while(_range)
			{
				VectorGet(_vec,_range--,&item);
				VectorSet(newVec,_countArr[item]--,item);
			}
			break;
		default:
			while(_range)
				{
					VectorGet(_vec,_range--,&item);
					VectorSet(newVec,_countArr[EXTRACT_DIGIT(item,_colExtractor)]--,item);
				}
	}
	
	if(NULL==VectorCopy(newVec,_vec))
	{
		return ERR_GENERAL;
	}
	
	VectorDestroy(newVec);
	return ERR_OK;
}

static int FindMax(Vector* _vec,size_t _startIndex,size_t _size)
{
	int newVal;
	Pair maxItem;

	maxItem.m_index = _startIndex;
	VectorGet(_vec,_startIndex++,&maxItem.m_val);
	
	while(_startIndex<=_size)
	{
		VectorGet(_vec,_startIndex,&newVal);
		if(newVal>maxItem.m_val)
		{
			maxItem.m_val=newVal;
			maxItem.m_index = _startIndex; 
		}
		++_startIndex;
	}
	return maxItem.m_val;
}

ADTErr CountingSort(Vector* _vec,int _maxRange,size_t _colExtractor)
{

	int* countArr;
	size_t numOfItems;
	ADTErr status;

	if(ERR_OK!= (status=VectorItemsNum(_vec,&numOfItems)))
	{
		return status;
	}

	if(NULL== (countArr=(int*)calloc(_maxRange,sizeof(int))))
	{
		return ERR_ALLOCATION_FAILED;
	}
		
	CountOccurance(_vec,countArr,numOfItems,_colExtractor);
	AccumulateSumOccurances(countArr, _maxRange-1);
	RestoreSorted(_vec,countArr,numOfItems,_colExtractor);
	free(countArr);

	return ERR_OK;
}

static ADTErr SortByColumn(Vector* _vec,size_t _base,size_t _colExtractor)
{
	
	return CountingSort(_vec,_base,_colExtractor);
}

ADTErr RadixSort(Vector* _vec, size_t _base)
{
	size_t numOfItems;	
	size_t colExtractor=INITIAL_EXTRACTOR;	
	int maxVal;
	ADTErr status;

	if(ERR_OK!= (status=VectorItemsNum(_vec,&numOfItems)))
	{
		return status;
	}

	maxVal = FindMax(_vec,START_INDEX,numOfItems);
	while(maxVal && ERR_OK==status)
	{	
		status=SortByColumn(_vec,_base,colExtractor);
		colExtractor*=_base;
		maxVal/=_base;
	}
	
	return status;
}

