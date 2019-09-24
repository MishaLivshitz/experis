#ifndef __SORT_H_
#define __SORT_H_

#include "vector.h"

#define ZERO_EXTRACTOR 0
#define INITIAL_EXTRACTOR 1
#define MIN_RANGE 0
#define DECIMAL_BASE 10


#define INITIAL_GAP 1
#define START_INDEX 1
#define MIDDLE(x,y) (x) + (y/2)
#define RIGHT(x) (x) + 1
#define EXTRACT_DIGIT(x,y) (x)/(y)%10
/*
This method implements shake sort
params: 
	_vec: vetor
retrun ERR_OK
*/

Vector_Result ShakeSort(Vector* _vec);

/*
This method implements InsertionSort
params: 
	_vec: vetor
retrun ERR_OK
*/
Vector_Result ShellSort(Vector* _vec);

/*
This method implements recursive quick sort

params: 
	_vec:vector
	_pivotIndex: pivot index
	_endIndex: end of vector index
retrun ERR_OK
*/
Vector_Result QuickSort(Vector* _vec, size_t _pivotIndex,size_t _endIndex);

/*
This method implements InsertionSort
params: 
	_vec: vetor
retrun ERR_OK
*/
Vector_Result InsertionSort(Vector* _vec);

/*
This method implements SelectionSort
params: 
	_vec: vetor
retrun ERR_OK
*/
Vector_Result SelectionSort(Vector* _vec);

/*
This method implements MergeSortRec
params: 
	_vec: vetor
	_isInPlace: boolean variable to decide if merge in place or not
retrun ERR_OK
*/
Vector_Result MergeSortRec(Vector* _vec, int _isInPlace);

/*
This method implements MergeSortIterative
params: 
	_vec: vetor
	_isInPlace: boolean variable to decide if merge in place or not
retrun ERR_OK
*/
Vector_Result MergeSortIterative(Vector* _vec,int isInPlace);
/*
This method implements CountingSort
params: 
	_vec: vetor
	_maxRange: maximal range
	size_t _colExtractor: a number for extract a specific digit from a number  (EXAMPLE: _colExtractor == 100 num=1235  num/_colExtractor=12 then num%10 will extract the 3rd digit)
						  ***should be: _colExtractor=ZERO_EXTRACTOR for regular counting sort***
retrun ERR_OK if SUCCESS else ERR_GENERAL or ERR_ALLOCATION_FAILED

*/

Vector_Result CountingSort(Vector* _vec,int _maxRange,size_t _colExtractor);

/*

This method implements radix sort
	params: 
		_vec: vetor
		_base: base
retrun ERR_OK if SUCCESS else ERR_GENERAL or ERR_ALLOCATION_FAILED
*/
Vector_Result RadixSort(Vector* _vec,size_t _base);


#endif
