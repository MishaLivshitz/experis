
/*
 * This file describes the functionality of task
 * 
 * Author: Michael Livshitz
 * Date: 15/5/19
 * 
 * **/

#ifndef _PQ_H
#define _PQ_H


#include "ADTItem.h"

typedef enum
{
    PQ_SUCCESS,
    PQ_NOT_INIT,
    PQ_BAD_ALLOC
    
}PQ_Result;

typedef struct PrioQ PrioQ;


/*
 * @brief: This method creates a priority queue
 * 
 * @params:
 * 			_itemCmp: function to compare the objects
 * 			
 * @return: new queue when success else return NULL 
 * 
 * */
PrioQ* PrioQ_Create(AdtItemCompare _itemCmp);

/*
 * @brief: This method destroys a priority queue
 * 
 * @params:
 * 			_pq: priority queue
 * 			_destroyer: function to destroy the items of a queue
 * */
void PrioQ_Destroy(PrioQ* _pq , AdtItemDestroy _destroyer);

/*
 * @brief: insert/remove items 
 * 
 * @params:
 * 			_pq: priority queue
 * 			_item[in]: the item to insert
 * 			_item[out]: place to return the removed item
 * @return: PQ_SUCCESS
 * 	
 * */
PQ_Result PrioQ_Enqueue(PrioQ* _pq, AdtItem _item);
PQ_Result PrioQ_Dequeue(PrioQ* _pq ,AdtItem* _item);

/*
 *
 * 
 * @params:
 * 			_pq: priority queue
 * 			
 * @return:number of items in the queue
 * 	
 * */

size_t PrioQ_Size(const PrioQ* _pq);

#endif
