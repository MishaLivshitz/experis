#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"

#define THREADS_NUM			5
#define DEFAULT_ITERATIONS 	10
#define DEFAULT_CAPACITY 	10
#define DEFAULT_SLEEP		500
#define NUM_OF_VALUSE		30
#define RAND_RANGE			1000

#define BAD_ARGS_ERR 	"No such option, usage: [n<num of it>, w<miliSec>, c - coms, d - isDelete,e - actuvate terminator f<file name>]"

typedef struct t_params
{
	int					m_mSeconds;
	int 				m_numOfIter;
	int 				m_tNum;
	int*				m_terminator;
	pthread_mutex_t* 	m_lock;
	sem_t* 				m_semEmptyID;
	sem_t*				m_semFullID;
	Queue*				m_queue;
	
}t_params;

typedef struct GetOptParams
{
	int m_pNum;
	int m_cNum;
	int m_mSleep;
	int m_nProduce;
	int m_qCapacity;
	
}GetOptParams;

int static valuesArr[NUM_OF_VALUSE];


int GetOptHandler(int _argc,char* _argv[],GetOptParams *_p)
{
	int opt;
	
	while(-1 != (opt=getopt(_argc,_argv,"n: p: c: q: w:")))
	{
		switch(opt)
		{
			
			case 'n':
				_p->m_nProduce = atoi(optarg);
				break;
				
			case 'w':
				_p->m_mSleep = atoi(optarg) * 1000;
				break;
				
			case 'c':
				_p->m_cNum = atoi(optarg);
				break;
				
			case 'p':
				_p->m_pNum = atoi(optarg);
				break;
				
			case 'q':
				_p->m_qCapacity = atoi(optarg);
				break;
				
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	return 1;
}

void InitValues()
{
	int i;
	
	for(i=0;i<NUM_OF_VALUSE;i++)
	{
		valuesArr[i] = rand() % RAND_RANGE + 1;
	}
}

void* producer(void *_params)
{
	int i;
	t_params* params = (t_params*)_params;
	
	for(i=0;i<params->m_numOfIter;i++)
	{
		sem_wait(params->m_semEmptyID);	
			usleep(params->m_mSeconds);
			pthread_mutex_lock(params->m_lock);
				printf("Producer #%d\n",params->m_tNum);
				Queue_Enque(params->m_queue,(void*)&valuesArr[i]);
				printf("Item produced:%d\n",valuesArr[i]);
			pthread_mutex_unlock(params->m_lock);
			
		sem_post(params->m_semFullID);
	}
	
	return NULL;
}

void* consumer(void *_params)
{

	int *item = NULL;
	t_params* params = (t_params*)_params;
	
	while(1)
	{
		
		pthread_mutex_lock(params->m_lock);
			if(!params->m_terminator)
			{
				pthread_mutex_unlock(params->m_lock);
				break;
			}
		pthread_mutex_unlock(params->m_lock);
		
		sem_wait(params->m_semFullID);
			pthread_mutex_lock(params->m_lock);
				printf("Consumer #%d\n",params->m_tNum);
				Queue_Deque(params->m_queue,(void*)&item);
				if(item)
				{
					printf("Item consumed:%d\n",*item);
				}
			pthread_mutex_unlock(params->m_lock);
			usleep(params->m_mSeconds);
			
		sem_post(params->m_semEmptyID);
	}
	
	return NULL;
}

int InitSemaphores(sem_t* _full,sem_t* _empty, int _numOfActions)
{
	if(0 != sem_init(_full,0,0))
	{
		perror("sem_init");
		return errno;
	}
	
	if(0 != sem_init(_empty,0,_numOfActions))
	{
		perror("sem_init");
		return errno;
	}

	return 0;
}

int CreateThreadsArrays(pthread_t** _prodThreads, pthread_t** _consThreads, int _cNum, int _pNum)
{
	*_prodThreads = (pthread_t*)malloc(sizeof(pthread_t)*_pNum);
	if(!_prodThreads)
	{
		return 0;
	}
	
	*_consThreads = (pthread_t*)malloc(sizeof(pthread_t)*_cNum);
	if(!_consThreads)
	{
		free(_prodThreads);
		return 0;
	}
	
	return 1;
}

int main(int argc, char* argv[])
{
	/* int numOfProd, numOfCons;*/
	/*int prodSleep, consSleep;*/
	int terminatorFlag = 1;
	pthread_t* prodThreads;
	pthread_t* consThreads;
	pthread_mutex_t lock;
	t_params params[THREADS_NUM]; /*TODO: create this array by malloc*/
	int status;
	int i;
	sem_t semFullID;
	sem_t semEmptyID;
	Queue* queue;
	GetOptParams gParams;
	
	if(!GetOptHandler(argc,argv,&gParams))
	{
		return -1;
	}
	
	if(!CreateThreadsArrays(&prodThreads, &consThreads, gParams.m_pNum, gParams.m_cNum))
	{
		return -1;
	}
	
	InitValues();
	
	if(0 != (status=InitSemaphores(&semFullID,&semEmptyID,gParams.m_qCapacity)))
	{
		perror("InitSemaphores");
		return status;
	}
	
	if(0 != pthread_mutex_init(&lock,NULL))
	{
		perror("pthread_mutex_init");
		return errno;
	}
	
	queue = Queue_Create(gParams.m_qCapacity);
	if(!queue)
	{
		puts("Queue_Create error");
		return -1;
	}
	
	/*TODO:divide to params for producers and consumers*/
	for(i=0;i<gParams.m_pNum;++i)
	{
		params[i].m_lock = &lock;
		params[i].m_semFullID = &semFullID;
		params[i].m_semEmptyID = &semEmptyID;
		params[i].m_numOfIter = gParams.m_nProduce;
		params[i].m_tNum = i+1;
		params[i].m_mSeconds = gParams.m_mSleep * 1000;
		params[i].m_queue = queue;
		params[i].m_terminator = &terminatorFlag;
	}
	
	for(i=0;i<gParams.m_pNum;++i)
	{
		
		status = pthread_create(&prodThreads[i],NULL,producer,(void*)&params[i]);
		if(status)
		{
			perror("pthread_create");
			return errno;
		}
	}
	
	for(i=0;i<gParams.m_cNum;++i)
	{
		status = pthread_create(&consThreads[i],NULL,consumer,(void*)&params[i]);
		if(status)
		{
			perror("pthread_create");
			return errno;
		}
	}
	
	for(i=0;i<gParams.m_pNum; ++i)
	{
		pthread_join(prodThreads[i],NULL);
	}
	
	pthread_mutex_lock(&lock);
		terminatorFlag = 0;
	pthread_mutex_unlock(&lock);
	
	/*for(i=0;i<THREADS_NUM;i++)
	{
		pthread_join(consThreads[i],NULL);
	}*/
	
	return 0;
}
