#include "mu_test.h"
#include <stdio.h>
#include <time.h>
#include "scheduler.h"

int task1(void* _context)
{
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf("I am task1:\n");
    printf ("Current local time and date: %s", asctime (timeinfo) );
	return --(*(int*)_context) > 0;
}

int task2(void* _context)
{
	time_t rawtime;
	struct tm * timeinfo;
	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf("I am task2:\n");
    printf ("Current local time and date: %s", asctime (timeinfo) );
	return --(*(int*)_context) > 0;
}

int task3(void* _context)
{
	printf("I am task3\n");
	PeriodicExecutor_Pause((PeriodicExecutor*)_context);
	return 1;
}

int task5(void* _context)
{
	time_t rawtime;
	struct tm * timeinfo;
	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf("I am task5:\n");
    printf ("Current local time and date: %s", asctime (timeinfo));
    if(--(*(int*)_context) == 0)
    {
		free(_context);
		return 0;
	}
	return 1;
}

int task4(void* _context)
{
	int* t2 = malloc(sizeof(int));
	*t2=3;
	
	printf("I am task4\n");
	PeriodicExecutor_Add((PeriodicExecutor*)_context,task5,(void*)t2,3000);
	return 0;
}



UNIT(PeriodicExecutor_CreateSuccess)

	PeriodicExecutor* executor;
	
	executor = PeriodicExecutor_Create(CLOCK_REALTIME);
	ASSERT_NOT_EQUAL_PTR(NULL,executor);
	PeriodicExecutor_Destroy(executor);

END_UNIT

UNIT(PeriodicExecutor_RunTest)

	PeriodicExecutor* executor;
	int t1,t2;
	
	t1=5;
	t2=3;
	
	executor = PeriodicExecutor_Create(CLOCK_REALTIME);
	PeriodicExecutor_Add(executor,task1,(void*)&t1,1000);
	PeriodicExecutor_Add(executor,task2,(void*)&t2,500);
	ASSERT_EQUAL_INT(PeriodicExecutor_Run(executor),8);
	PeriodicExecutor_Destroy(executor);

END_UNIT

UNIT(PeriodicExecutor_PauseTest)

	PeriodicExecutor* executor;
	/*int t2;
	t2=3;*/
	
	executor = PeriodicExecutor_Create(CLOCK_REALTIME);
	PeriodicExecutor_Add(executor,task3,(PeriodicExecutor*)executor,500);
	/*PeriodicExecutor_Add(executor,task2,(void*)&t2,3000);*/
	ASSERT_EQUAL_INT(PeriodicExecutor_Run(executor),1);
	ASSERT_EQUAL_INT(PeriodicExecutor_Run(executor),1);
	/*ASSERT_EQUAL_INT(PeriodicExecutor_Run(executor),3);*/
	PeriodicExecutor_Destroy(executor);

END_UNIT


UNIT(PeriodicExecutor_taskAddtask)

	PeriodicExecutor* executor;
	
	executor = PeriodicExecutor_Create(CLOCK_REALTIME);
	PeriodicExecutor_Add(executor,task4,(PeriodicExecutor*)executor,3000);
	ASSERT_EQUAL_INT(PeriodicExecutor_Run(executor),4);
	PeriodicExecutor_Destroy(executor);

END_UNIT


TEST_SUITE(Schedulaer Test)
	
	TEST(PeriodicExecutor_CreateSuccess)
	TEST(PeriodicExecutor_RunTest)
	TEST(PeriodicExecutor_PauseTest)
	TEST(PeriodicExecutor_taskAddtask)
	
END_SUITE
