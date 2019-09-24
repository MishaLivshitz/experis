#include "person.h"


struct person{

	size_t m_id;
	size_t m_age;
	char m_name[MAX_NAME_SIZE];
	struct person* m_next;
};


static void swap(Person *a, Person *b){

	Person temp = *a;
	*a=*b;
	*b=temp;
}


static int BubbleUp(Person* Persons, int size ,unsigned _typeSize)
{
	int j,isSwaped=FALSE;

	for(j=0;j<size-1;j++)
	{
		switch(_typeSize)
		{
			case AGE_SORT_FLAG:
			if(Persons[j].m_age>Persons[j+1].m_age){
				isSwaped=TRUE;
				}
			break;

			case ID_SORT_FLAG:
			if(Persons[j].m_id>Persons[j+1].m_id){
				isSwaped=TRUE;
				}
			break;

			case NAME_SORT_FLAG:
			if(strcmp(Persons[j],Persons[j+1])>0){
				isSwaped=TRUE;
				}
			break;
		}
		if(isSwaped)
		{
			swap(&Persons[j],&Persons[j+1]);
		}
			
				
	}
	return isSwaped;
}

int PutPersonsData(Person* _Persons, people_amount _numOfPesons)
{
	int i;

	if(NULL==_Persons)
	{
		return NULL_POINTER_ERR;
	}
	
	for(i=0;i<_numOfPesons;i++)
		{
			printf("Insert age, id and name of Person #%d:",i+1);
			scanf("%lu %lu %s",&_Persons[i].m_age,&_Persons[i].m_id,_Persons[i].m_name);
			getchar();
			_Persons[i].m_next=NULL;
		}
	return STATUS_SUCCESS;
}

Person* AllocatePepolesMem(people_amount _numOfPesons)
{
	Person* Persons= (Person*)malloc(sizeof(Person)*_numOfPesons);

return Persons;
}


int SortPeople(Person* _PersonsArr, people_amount _numOfPesons,size_t _sortByFlag){


	int i;
	
	if(NULL==_PersonsArr)
	{
		return NULL_POINTER_ERR;
	}
	
	for(i=0;i<_numOfPesons;i++){
		if(FALSE==BubbleUp(_PersonsArr,_numOfPesons-i,_sortByFlag))
			{
			 	break;
			}
		}
	return STATUS_SUCCESS;
}


void printPersons(Person* _PersonsArr,people_amount _numOfPesons)
{

	int i;
	for(i=0;i<_numOfPesons;i++)
	{
		printf("Name:%s\n",_PersonsArr[i].m_name);
		printf("ID:%lu\n",_PersonsArr[i].m_id);
		printf("Age:%lu\n",_PersonsArr[i].m_age);
	}
	printf("\n");
}


