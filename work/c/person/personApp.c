#include "person.h"


typedef struct person{

	unsigned int id;
	unsigned int age;
	char name[MAX_NAME_SIZE];
	pesron* next;

}

int main()
{

	char option;
	int exitFlag=FALSE,i;
	people_amount peopleAmount;
	personPtr persons = NULL; 
	
	printf("		*************************\n");
	printf("		*-------Persons---------*\n");
	printf("		*************************\n\n");

	printf("Insert how many people data to create:");
	scanf("%u",&peopleAmount);
	getchar();
	persons = AllocatePepolesMem(peopleAmount);
	if(NULL==persons)
		{
			printf("Memory allocation failed\n");
			return 0;
		}
	PutPersonsData(persons,peopleAmount);

	
	

	while(FALSE==exitFlag)
	{	
		printf("\n\nOptions:\n");
		printf("		   1: Sort by ID\n");
		printf("		   2: Sort by Age\n");
		printf("		   3: Sort by Name\n");
		printf("	  	   Q or q: Quit\n\n");
		printf("Choose one of the options:\n");
		option=getchar();
		switch(option)
		{
			case '1':
			printf("Sorting by id:\n");
			SortPeople(persons,peopleAmount,ID_SORT_FLAG);
			break;
			case '2':
			printf("Sorting by age:\n");
			SortPeople(persons,peopleAmount,AGE_SORT_FLAG);
			break;
			case '3':
			printf("Sorting by name:\n");
			SortPeople(persons,peopleAmount,NAME_SORT_FLAG);
			break;
			case 'q':
			case 'Q':
			exitFlag=TRUE;
			break;

			default:
			printf("Please choose valid option\n");
		}
	printPersons(persons,peopleAmount);
	printf("\n\n");
	getchar();
	}

	free(persons);
	persons = NULL;
	return 0;
}
