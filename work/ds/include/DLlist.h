/*
This module responsible for implemnting a double linked list
Author: Michael Livshitz
Date:12.4.19

 gcc -ansi -pedantic -I ../include/ -I ../../c/include/ *.c ../../c/allocator/allocator.c
*/
#ifndef __D_LIST_H__
#define __D_LIST_H__
#include "ADTErr.h"
#include <stdlib.h>
#include <stdio.h>

#define MAGIC_NUM_ACTIVE 0xdefdef
#define MAGIC_NUM_INACTIVE 0xdeaddef
typedef int bool;

typedef struct list List;

/*
This method creates a List structure

params:
	_nodeSize: size of each node
	_numOfNodes: number of wanted nodes

return pointer to list if success else return NULL;
*/
List* ListCreate(size_t _numOfNodes);

/*
This method destroy a list

params: 
	_list: pointer to list.
*/
void ListDestroy(List* _list);

/*
This method insert new node to the head of the list

params:
	_list: pointer to list
	_data: the data of the new node

return ERR_OK if succes else return ERR_NOT_INITIALIZED or ERR_ALLOCATION_FAILED
*/
ADTErr ListPushHead(List* _list, int _data);

/*
This method insert new node to the tail of the list

params:
	_list: pointer to list
	_data: the data of the new node

return ERR_OK if succes else return ERR_NOT_INITIALIZED or ERR_ALLOCATION_FAILD
*/
ADTErr ListPushTail(List* _list, int _data);

/*
This method remove a node from the head of the list

params:
	_list: pointer to list
	_data: a place for the poped node data

ATTENTION: in case of _data==NULL no data will returned
return ERR_OK if succes else return ERR_NOT_INITIALIZED or ERR_EMPTY
*/
ADTErr ListPopHead(List* _list, int* _data);

/*
This method remove a node from the tail of the list

params:
	_list: pointer to list
	_data: a place for the poped node data

ATTENTION: in case of _data==NULL no data will returned
return ERR_OK if succes else return ERR_NOT_INITIALIZED or ERR_EMPTY
*/
ADTErr ListPopTail(List* _list, int* _data);

/*
This method counts the items of the list
params:
	_list: pointer to list

return number of items when succes else return ERR_NOT_INITIALIZED
*/
size_t ListCountItems(List* _list);

/*
This method check if the list is empty
params:
	_list: pointer to list

return TRUE if empty else return FALSE
*/
bool ListIsEmpty(List* _list);

/*
This method prints the list
params:
	_list: pointer to list
*/

void ListPrint(List* _list);
#endif
