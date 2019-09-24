#include "list.h"
#include "person.h"
#include "UTestERR.h"
#include <string.h>
#define SIZE 4
#define RESET "\033[0m"
#define KGRN  "\x1B[32m"
#define KRED  "\x1B[31m"

int InsertPersonsData(Person* _Persons, people_amount _numOfPesons)
{
	int i;
	size_t startId = 307;

	if(NULL==_Persons)
	{
		return NULL_POINTER_ERR;
	}
	
	for(i=0;i<_numOfPesons;i++)
		{
			strcpy(_Persons[i].m_name ,"AVI");
			_Persons[i].m_id = startId;
			_Persons[i].m_age = 10;
			_Persons[i].m_next = NULL;
			startId = startId%2 == 0 ? startId+3: startId-5;
		}

	return STATUS_SUCCESS;
}

UTestERR TestListInsertHeadSuccess()
{
	
	int i;
	Person* head = NULL;
	Person persons[SIZE];

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertHead(head,&persons[i]);
	}

	for(i=SIZE - 1; head!=NULL; i--,head=head->m_next)
	{
		if(head != &persons[i] || head->m_id!=persons[i].m_id)
		{
			return TEST_FAILED;
		}
	}

	return TEST_SUCCESS;
}

UTestERR TestListInsertHeadNullPerson()
{
	
	int i;
	Person* head = NULL,*tempHead=NULL;
	Person persons[SIZE];

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertHead(head,&persons[i]);
	}
	
	tempHead = head;
	head = ListInsertHead(head,NULL);
	if(head->m_id==tempHead->m_id)
	{
		return TEST_SUCCESS;
	}

	return TEST_FAILED;
}


UTestERR TestListInsertHeadNullHead()
{
	Person* head = NULL;
	Person person = {12,307,"Michael",NULL};
	
	head = ListInsertHead(head,&person);
	if(head!=&person)
	{
		return TEST_FAILED;
	}
	if(head->m_id!=person.m_id)
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}

UTestERR TestListRemoveHeadSuccess()
{
	Person* head = NULL;
	Person* personReturn;
	Person person = {12,307,"Michael",NULL};

	head = ListInsertHead(head,&person);
	head = ListRemoveHead(head,&personReturn);

	if(personReturn == &person && NULL == head)
	{
		return TEST_SUCCESS;
	}

	return TEST_FAILED;
}


UTestERR TestListRemoveHeadNullHead()
{
	Person* head = NULL;
	Person person = {12,307,"Michael",NULL};
	Person* personReturn;

	head = ListInsertHead(head,&person);
	head = ListRemoveHead(head,&personReturn);
	head = ListRemoveHead(head,&personReturn);
	if(head!=NULL)
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}

UTestERR TestListRemoveHeadNullItem()
{
	Person* head = NULL, *tempHead=NULL;
	Person person = {12,307,"Michael",NULL};

	head = ListInsertHead(head,&person);
	if(head != ListRemoveHead(head,NULL))
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}

UTestERR TestListInsertByKeyNullPerson()
{
	
	int i;
	Person* head = NULL,*tempHead=NULL;
	Person persons[SIZE];

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertByKey(head, persons[i].m_id, &persons[i]);
	}
	
	tempHead = head;
	head = ListInsertByKey(head,2,NULL);
	if(head==tempHead)
	{
		return TEST_SUCCESS;
	}

	return TEST_FAILED;
}


UTestERR TestListInsertByKeyNullHead()
{
	Person* head = NULL;
	Person person = {12,307,"Michael",NULL};
	
	head = ListInsertByKey(head,person.m_id,&person);
	if(head!=&person)
	{
		return TEST_FAILED;
	}
	if(head->m_id!=person.m_id)
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}


UTestERR TestListInsertByKeySuccess()
{
	
	int i;
	Person* head = NULL;
	Person persons[SIZE];

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertByKey(head,persons[i].m_id,&persons[i]);
	}

	for(i=SIZE - 1; head->m_next!=NULL; i--,head=head->m_next)
	{
		if(head->m_id > head->m_next->m_id)
		{
			return TEST_FAILED;
		}
	}

	return TEST_SUCCESS;
}

UTestERR TestListInsertByKeyRecNullPerson()
{
	
	int i;
	Person* head = NULL,*tempHead=NULL;
	Person persons[SIZE];

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertByKeyRec(head, persons[i].m_id, &persons[i]);
	}
	
	tempHead = head;
	head = ListInsertByKeyRec(head,2,NULL);
	if(head==tempHead)
	{
		return TEST_SUCCESS;
	}

	return TEST_FAILED;
}


UTestERR TestListInsertByKeyRecNullHead()
{
	Person* head = NULL;
	Person person = {12,307,"Michael",NULL};
	
	head = ListInsertByKeyRec(head,person.m_id,&person);
	if(head!=&person)
	{
		return TEST_FAILED;
	}
	if(head->m_id!=person.m_id)
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}


UTestERR TestListInsertByKeyRecSuccess()
{
	
	int i;
	Person* head = NULL;
	Person persons[SIZE];

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertByKeyRec(head,persons[i].m_id,&persons[i]);
	}

	for(i=SIZE - 1; head->m_next!=NULL; i--,head=head->m_next)
	{
		if(head->m_id > head->m_next->m_id)
		{
			return TEST_FAILED;
		}
	}

	return TEST_SUCCESS;
}

UTestERR TestListRemoveByKeyNullPerson()
{
	
	int i;
	Person* head = NULL,*tempHead=NULL;
	Person persons[SIZE];

	InsertPersonsData(persons,SIZE);
	head = ListInsertByKey(head, persons[i].m_id, &persons[i]);
	if(head == ListRemoveByKey(head,persons[i].m_id,NULL))
	{
		return TEST_SUCCESS;
	}

	return TEST_FAILED;
}


UTestERR TestListRemoveByKeyNullHead()
{
	Person* head = NULL;
	Person person = {12,307,"Michael",NULL};
	Person* personReturn;

	head = ListInsertByKey(head,person.m_id,&person);
	head = ListRemoveByKey(head,person.m_id,&personReturn);
	head = ListRemoveByKey(head,person.m_id,&personReturn);
	if(head!=NULL)
	{
		return TEST_FAILED;
	}

	if(personReturn!=NULL)
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}

UTestERR TestListRemoveByKeySuccess()
{
	
	int i;
	Person* head = NULL;
	Person persons[SIZE];
	Person* personReturn=NULL,*tempPerson=NULL;

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertByKey(head,persons[i].m_id,&persons[i]);
	}
	
	for(i=SIZE - 1; head->m_next!=NULL; i--,head=head->m_next)
	{
		ListRemoveByKey(head,persons[i].m_id,&personReturn);
		if(head->m_next->m_id < personReturn->m_id)
		{
			return TEST_FAILED;
		}
	}

	return TEST_SUCCESS;
}


UTestERR TestListRemoveByKeyNotFound()
{
	
	int i;
	Person* head = NULL;
	Person persons[SIZE];
	Person* personReturn=NULL,*tempPerson=NULL;

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertByKey(head,persons[i].m_id,&persons[i]);
	}
	
	ListRemoveByKey(head,200,&personReturn);
	if(personReturn!=NULL)
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}

UTestERR TestListRemoveByKeyRecNullPerson()
{
	
	int i;
	Person* head = NULL,*tempHead=NULL;
	Person persons[SIZE];

	InsertPersonsData(persons,SIZE);
	head = ListInsertByKey(head, persons[i].m_id, &persons[i]);
	if(head == ListRemoveByKeyRec(head,persons[i].m_id,NULL))
	{
		return TEST_SUCCESS;
	}

	return TEST_FAILED;
}


UTestERR TestListRemoveByKeyRecNullHead()
{
	Person* head = NULL;
	Person person = {12,307,"Michael",NULL};
	Person* personReturn;

	head = ListInsertByKey(head,person.m_id,&person);
	head = ListRemoveByKeyRec(head,person.m_id,&personReturn);
	head = ListRemoveByKeyRec(head,person.m_id,&personReturn);
	if(head!=NULL)
	{
		return TEST_FAILED;
	}

	if(personReturn!=NULL)
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}

UTestERR TestListRemoveByKeyRecSuccess()
{
	
	int i;
	Person* head = NULL;
	Person persons[SIZE];
	Person* personReturn=NULL,*tempPerson=NULL;

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertByKey(head,persons[i].m_id,&persons[i]);
	}
	
	for(i=SIZE - 1; head->m_next!=NULL; i--,head=head->m_next)
	{
		ListRemoveByKeyRec(head,persons[i].m_id,&personReturn);
		if(head->m_next->m_id < personReturn->m_id)
		{
			return TEST_FAILED;
		}
	}

	return TEST_SUCCESS;
}


UTestERR TestListRemoveByKeyRecNotFound()
{
	
	int i;
	Person* head = NULL;
	Person persons[SIZE];
	Person* personReturn=NULL,*tempPerson=NULL;

	InsertPersonsData(persons,SIZE);
	for(i=0;i<SIZE;i++)
	{
		head = ListInsertByKey(head,persons[i].m_id,&persons[i]);
	}
	
	ListRemoveByKeyRec(head,200,&personReturn);
	if(personReturn!=NULL)
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}

void printTestResult(UTestERR result,char* testName)
{
	result==TRUE ? printf("%s: %sSUCCESS%s\n\n",testName,KGRN,RESET): printf("%s: %sFAILED%s\n\n",testName,KRED,RESET);
}

int main()
{
	puts("\n****************TESTS*****************\n");
	printTestResult(TestListInsertHeadSuccess(),"TestListInsertHeadSuccess");
	printTestResult(TestListInsertHeadNullPerson(),"TestListInsertHeadNullPerson");
	printTestResult(TestListInsertHeadNullHead(),"TestListInsertHeadNullHead");
	
	printTestResult(TestListInsertByKeyNullPerson(),"TestListInsertByKeyNullPerson");
	printTestResult(TestListInsertByKeyNullHead(),"TestListInsertByKeyNullHead");
	printTestResult(TestListInsertByKeySuccess(),"TestListInsertByKeySuccess");

	printTestResult(TestListInsertByKeyRecNullPerson(),"TestListInsertByKeyNullPerson");
	printTestResult(TestListInsertByKeyRecNullHead(),"TestListInsertByKeyNullHead");
	printTestResult(TestListInsertByKeyRecSuccess(),"TestListInsertByKeySuccess");

	printTestResult(TestListRemoveHeadSuccess(),"TestListRemoveHeadSuccess");
	printTestResult(TestListRemoveHeadNullHead(),"TestListRemoveHeadNullHead");
	printTestResult(TestListRemoveHeadNullItem(),"TestListRemoveHeadNullItem");

	printTestResult(TestListRemoveByKeyNullPerson(),"TestListRemoveByKeyNullPerson");
	printTestResult(TestListRemoveByKeyNullHead(),"TestListRemoveByKeyNullHead");
	printTestResult(TestListRemoveByKeySuccess(),"TestListRemoveByKeySuccess");
	printTestResult(TestListRemoveByKeyNotFound(),"TestListRemoveByKeyNotFound");

	printTestResult(TestListRemoveByKeyRecNullPerson(),"TestListRemoveByKeyRecNullPerson");
	printTestResult(TestListRemoveByKeyRecNullHead(),"TestListRemoveByKeyRecNullHead");
	printTestResult(TestListRemoveByKeyRecSuccess(),"TestListRemoveByKeyRecSuccess");
	printTestResult(TestListRemoveByKeyRecNotFound(),"TestListRemoveByKeyRecNotFound");
	puts("****************TESTS*****************\n");
	return 1;
}
