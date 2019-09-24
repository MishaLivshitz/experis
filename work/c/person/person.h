#include <stdio.h>
#include <stdlib.h>
#define STATUS_SUCCES 1
#define NULL_POINTER_ERR -1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAX_NAME_SIZE 30

#define AGE_SORT_FLAG 4
#define ID_SORT_FLAG 3
#define NAME_SORT_FLAG 2

typedef unsigned int people_amount;

typedef struct person person;
typedef struct person* personPtr;

/*
Author:Michael Livshits
Date:01/04/19
*/

/*
Allocating memory for persons
params: 
		numOfPesons => Numbers of persons to create (>0)

returns pointer to structs array if success
else returns NULL

*/
personPtr AllocatePepolesMem( people_amount _numOfPesons);

/*
Asks from the user for presons data and store it
Person data:
			age: > 0
			id: >= 0
			name: up to MAX_NAME_SIZE charecters
params: 
		numOfPesons => Numbers of persons to create (>0)
		persons => pointer to persons array

returns STATUS_SUCCES if success
else returns ERROR or NULL_POINTER_ERR

*/
int PutPersonsData(personPtr _persons, people_amount _numOfPesons);

/*
sort presons array
params: 
	_personsArr => pointer to persons array
	_sortByFlag => the filed to sort by: 
										 AGE_SORT_FLAG
										 ID_SORT_FLAG
										 NAME_SORT_FLAG
returns STATUS_SUCCES if success
else returns ERROR

*/
int SortPeople(personPtr _personsArr ,people_amount _numOfPesons, unsigned int _sortByFlag);

/*
Prints people array
params: 
		numOfPesons => Numbers of persons to create (>0)
		persons => pointer to persons array
*/

void printPersons(personPtr _personsArr,people_amount _numOfPesons);

