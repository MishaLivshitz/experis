
/*
 * This Header is for utils which can be used in different modules of  
 * project
 * 
 * Author: Michael Livshitz
 * Date: 1/5/19
 * **/
#ifndef _UTILS_H
#define _UTILS_H

#include "vector.h"
#include "cards.h"

typedef struct Pair
{
	size_t m_index;
	int m_val;
}Pair;


void Swap(Vector* _deck,Pair* _a, Pair* _b);

#endif
