/*
This module implements a tree oprations
Author:Michael Livshitz
Date: 14/4/19

gcc -ansi -pedantic -I ../include/ *.c
*/


#include <stdio.h>
#include <stdlib.h>
#include "ADTErr.h"
#define MAGIC_NUM_ACTIVE 0xdefdef
#define MAGIC_NUM_INACTIVE 0xdeaddef
#define FILE_NAME "treeInOrder.txt"

typedef struct tree Tree;
typedef int bool;

typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
}TreeTraverse;

typedef enum
{
	DESTROY,
	PRINT,
	SEARCH
	
}TreeAction;

/*
This method creates a tree

return pointer to the tree else return ERR_ALLOCATION_FAILED
*/
Tree* TreeCreate();

/*
This method destorys the tree

params:
	_tree: poniter to a tree
*/
void TreeDestroy(Tree* _tree);

/*
This method inserts an data to the tree

params:
	_tree: poniter to a tree
	_data: the data to insert

return ERR_OK if success else return ERR_NOT_INITIALIZED or ERR_ALLOCATION_FAILED or ERR_EXIST
*/
ADTErr TreeInsert(Tree* _tree, int _data);

/*
This method check if a given data is found in the tree

params:
	_tree: poniter to a tree
	_data: a data to look for

return TRUE if found else return FALSE
*/
bool TreeIsDataFound(Tree* _tree,int data);

/*
This method prints the elements in the tree

params:
	_tree: poniter to a tree
	_traverseMode: traverse mode
*/
void TreePrint(Tree* _tree, TreeTraverse _traverseMode);
