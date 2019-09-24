#ifndef __LIST_H_
#define __LIST_H_
#include <stdio.h>
#include <stdlib.h>
#include "person.h"

typedef int bool;


struct person{

	size_t m_id;
	size_t m_age;
	char m_name[MAX_NAME_SIZE];
	struct person* m_next;
};

/*gcc -ansi -pedantic -I ../include list.c listApp.c ../person/personFunctions.c*/

/*
A manual for list function uses
Author: Michael Livshitz
Date: 10.4.19
*/

/*
This method inserts a new person to the list

params:
	 _head: the head of the list
	 _p: the new person to insert

return new head pointer if succes
	 else:
		 if _p is NULL return _head
		 if _head is NULL return _p
*/
Person* ListInsertHead(Person* _head, Person* _p);

/*
This method removes item from the head

params:
	_head: the head of the list
	_item: a place to return the person

return new head pointer if succes
	 else:
		 if _item is NULL return _head
		 if _head is NULL return NULL
*/
Person* ListRemoveHead(Person* _head, Person** _item);

/*
This method insert an item sorted by key (id of person)

params:
	_head: the head of the list
	_key: the key to insert by
	_p: the person to insert

return the head pointer if succes
	else:
		 if _p is NULL return _head
		 if _head is NULL return _p
*/
Person* ListInsertByKey(Person* _head,int _key, Person* _p);

/*
This method insert an item sorted by key (id of person) recursivly

params:
	_head: the head of the list
	_key: the key to insert by
	_p: the person to insert

return the head pointer if succes 
	else:
		 if _p is NULL return _head
		 if _head is NULL return _p
*/
Person* ListInsertByKeyRec(Person* _head,int _key, Person* _p);

/*
This method remove an item by key (id of person)

params:
	_head: the head of the list
	_key: the key to insert by
	_p: a place to retrun the removed person

return the head pointer if succes
	else:
		 if _p is NULL return _head
		 if _head is NULL return NULL
*/
Person* ListRemoveByKey(Person* _head,int _key, Person** _p);

/*
This method remove an item by key (id of person) recursivly

params:
	_head: the head of the list
	_key: the key to insert by
	_p: a place to retrun the removed person

return the head pointer if succes 
	else:
		 if _p is NULL return _head
		 if _head is NULL return NULL
*/
Person* ListRemoveByKeyRec(Person* _head,int _key, Person** _p);

/*
This method prints the list

params:
	_head: the head of the list
*/
void PrintList(Person* _head);
#endif
