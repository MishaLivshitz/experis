#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS_NUM		5
#define INC_NUM 		10000000

volatile size_t g_inc=0;
pthread_mutex_t lock;

void* printFunc(void* tid)
{
	int i;
	
	for(i=0;i<*(int*)tid;i++)
	{
		pthread_mutex_lock(&lock);
		++g_inc;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main()
{
	
	pthread_t threads[THREADS_NUM];
	int params[THREADS_NUM];
	int status;
	int i;
	
	if (pthread_mutex_init(&lock, NULL) != 0) 
	{ 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 
	
	for(i=0;i<THREADS_NUM;i++)
	{
		params[i] = INC_NUM;
		status = pthread_create(&threads[i],NULL,printFunc,(void*)&params[i]);
		/*sleep(1);*/
		if(status)
		{
			perror("pthread_create");
			return errno;
		}
	}
	
	for(i=0;i<THREADS_NUM;i++)
	{
		pthread_join(threads[i],NULL);
	}
	
	printf("%ld\n",g_inc);
	return 0;
}
