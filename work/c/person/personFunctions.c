#include "person.h"


void swap(person *a, person *b){

	person temp = *a;
	*a=*b;
	*b=temp;
}


int BubbleUp(personPtr persons, int size ,unsigned _typeSize)
{
	int j,isSwaped=FALSE;

	for(j=0;j<size-1;j++)
	{
		switch(_typeSize)
		{
			case AGE_SORT_FLAG:
			if(persons[j].age>persons[j+1].age){
				isSwaped=TRUE;
				}
			break;

			case ID_SORT_FLAG:
			if(persons[j].id>persons[j+1].id){
				isSwaped=TRUE;
				}
			break;

			case NAME_SORT_FLAG:
			if(strcmp(persons[j],persons[j+1])>0){
				isSwaped=TRUE;
				}
			break;
		}
		if(isSwaped)
		{
			swap(&persons[j],&persons[j+1]);
		}
			
				
	}
	return isSwaped;
}

int PutPersonsData(personPtr _persons, people_amount _numOfPesons)
{
	int i;

	if(NULL==_persons)
	{
		return NULL_POINTER_ERR;
	}
	
	for(i=0;i<_numOfPesons;i++)
		{
			printf("Insert age, id and name of person #%d:",i+1);
			scanf("%u %u %s",&_persons[i].age,&_persons[i].id,_persons[i].name);
			getchar();
		}
	return STATUS_SUCCES;
}

personPtr AllocatePepolesMem(people_amount _numOfPesons)
{
	personPtr persons= (personPtr)malloc(sizeof(person)*_numOfPesons);

return persons;
}


int SortPeople(personPtr _personsArr, people_amount _numOfPesons,unsigned int _sortByFlag){


	int i;
	
	if(NULL==_personsArr)
	{
		return NULL_POINTER_ERR;
	}
	
	for(i=0;i<_numOfPesons;i++){
		if(FALSE==BubbleUp(_personsArr,_numOfPesons-i,_sortByFlag))
			{
			 	break;
			}
		}
	return STATUS_SUCCES;
}


void printPersons(personPtr _personsArr,people_amount _numOfPesons)
{

	int i;
	for(i=0;i<_numOfPesons;i++)
	{
		printf("Name:%s\n",_personsArr[i].name);
		printf("ID:%u\n",_personsArr[i].id);
		printf("Age:%u\n",_personsArr[i].age);
	}
}


