#ifndef __QUEUE__H
#define __QUEUE__H
#include <stdio.h>
#include <stdlib.h>
#include "ADTErr.h"
#define TRUE 1
#define FALSE !TRUE
/*
Create the queue

params:
	_size: size of the queue

return pointer to queue when succes else return NULL
*/

typedef struct queue Queue;

Queue* QueueCreate(size_t _size);

/*
Destroy a queue

params:
	_queue: pointer to queue

*/
void QueueDestroy(Queue* _queue);

/*
Insert new item to the queue

params:
	_queue: pointer to queue
	_item: item to insert

return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_OVERFLOW
*/
ADTErr QueueInsert(Queue* _queue, int _item);

/*
Remove item from the queue

params:
	_queue: pointer to queue
	_item: a place to return the removed item

return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_UNDERFLOW
*/
ADTErr QueueRemove(Queue* _queue, int* _item);

/*
Check if the queue is empty

params:
	_queue: pointer to queue

return TRUE if empty else FALSE
*/
int QueueIsEmpty(Queue* _queue);

/*
Function for debug - prints the elements in the queue

params:
	_queue: pointer to queue

return num of printed items if succes else return ERR_NOT_INITIALIZED or ERR_EMPTY_QUEUE
*/
int QueuePrint(Queue* _queue);
#endif
