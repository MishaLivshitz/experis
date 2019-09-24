
#include "pingpong.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

const char* KeyGenFile = "KeyGenerator"; 

#define BAD_ARGS_ERR 	"No such option, usage: [v - verbose, n<num of messages>, s<miliSec>, c - isCreate, d - isDelete,e - actuvate terminator f<file name>]"

int main(int argc, char* argv[])
{
	int opt;
	int verbose = 0;
	int msgNum = 3;
	int msSleep = 0;
	int isDelete = 0;
	int key;
	int semId;
	int memId;
	int pid;
	int msgFlag = IPC_CREAT;
	SharedMemBuff *memBuff;
	SemBuf semBuffArr[2];
	int i;
	
	while(-1 != (opt=getopt(argc,argv,"v n: s: c d f: ")))
	{
		switch(opt)
		{
			case 'v':
				verbose = 1;
				break;
				
			case 'n':
				msgNum = atoi(optarg);
				break;
				
			case 's':
				msSleep = atoi(optarg) * 1000;
				break;
				
			case 'c':
				msgFlag |= IPC_EXCL;
				break;
				
			case 'f':
				KeyGenFile = optarg;
				
				break;
			case 'd':
				isDelete = 1;
				break;
				
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	if(-1==(key = ftok(KeyGenFile,PROJ_ID)))
	{
		perror("ftok error");
		return errno;
	}
	if(-1==(memId = shmget(key,DEFAULT_MEM_SIZE, msgFlag|0666)))
	{
		perror("shmget error");
		return errno;
	}
	
	if((void*)-1 ==(memBuff = (SharedMemBuff*)shmat(memId,NULL,0)))
	{
		perror("shmat error");
		return errno;
	}
	
	if(-1==(semId = semget(key,SEM_AMOUNT,IPC_CREAT|0666)))
	{
		perror("semget error");
		return errno;
	}
	
	pid = getpid();
	
	
	/*init ping semaphore*/
	if(-1 == semctl(semId,PING_SEM_NUM,SETVAL,0))
	{
		perror("semctl error");
		return errno;
	}
	
	/*init pong semaphore*/
	if(-1 == semctl(semId,PONG_SEM_NUM,SETVAL,1))
	{
		perror("semctl error");
		return errno;
	}
	
	semBuffArr[PONG_SEM_NUM].sem_num = PONG_SEM_NUM;
	semBuffArr[PING_SEM_NUM].sem_num = PING_SEM_NUM;	
	
	memBuff->m_msgCount = msgNum;
	while(memBuff->m_msgCount)
	{
		usleep(msSleep);
			
		semBuffArr[PONG_SEM_NUM].sem_op = -1; 		/*down: stop if pong isn't ready*/
		if(-1 ==semop(semId,&semBuffArr[PONG_SEM_NUM],1))
		{
			perror("semop error");
			return errno;
		}
		
		if(verbose)
		{
			puts("Sending message...");
		}
		
		sprintf(memBuff->m_text,"You got %.2f seconds until EXPLOSION!! from:%d", msSleep/(1000.0*1000) * memBuff->m_msgCount,pid); 
				
		semBuffArr[PING_SEM_NUM].sem_op = 1;	   /*up: signal when done to write*/
		if(-1 ==semop(semId,&semBuffArr[PING_SEM_NUM],1))
		{
			perror("semop error");
			return errno;
		}
		
		memBuff->m_msgCount--;
	}
	
	puts("Done sending");
	
	
	if(isDelete)
	{
		semBuffArr[PONG_SEM_NUM].sem_op = -1; 		/*down: stop if pong isn't ready*/
		if(-1 ==semop(semId,&semBuffArr[PONG_SEM_NUM],1))
		{
			perror("semop error");
			return errno;
		}
		
		if(-1 == shmctl(memId,IPC_RMID,0))
		{
			perror("shmctl error");
			return errno;
		}
		
		for(i=SEM_AMOUNT-1;i>=0;i--)
		{
			if(-1 == semctl(semId,i,IPC_RMID,0))
			{
				perror("semctl error");
				return errno;
			}
		}
	}
	
	
	return 0;
}
