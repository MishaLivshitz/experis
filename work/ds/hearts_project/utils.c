#include "utils.h"

void Swap(Vector* _deck,Pair* _a, Pair* _b)
{
	VectorSet(_deck,_a->m_index,_b->m_val);
	VectorSet(_deck,_b->m_index,_a->m_val);
}

