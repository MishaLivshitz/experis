
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

#define BAD_ARGS_ERR 	"No such option, usage: [v-verbose, s<miliSec>, f<file name>]"

int main(int argc, char* argv[])
{
	int opt;
	int verbose = 0;
	int msSleep = 0;
	int key;
	int semId,memId;
	int msgFlag = IPC_CREAT;
	SharedMemBuff *memBuff;
	SemBuf semBuffArr[2];
	int pid = getpid();
	
	while(-1 != (opt=getopt(argc,argv,"v s: f: ")))
	{
		switch(opt)
		{
			case 'v':
				verbose = 1;
				break;
		
			case 's':
				msSleep = atoi(optarg) * 1000;
				break;
			
			case 'f':
				KeyGenFile = optarg;
				break;
				
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	key = ftok(KeyGenFile,PROJ_ID);	
	
	if(-1==(memId = shmget(key,DEFAULT_MEM_SIZE, msgFlag|0666)))
	{
		perror("shmget error");
		return errno;
	}
	
	if((void*)-1 ==(memBuff = shmat(memId,NULL,0)))
	{
		perror("shmat error");
		return errno;
	}
	
	if(-1==(semId = semget(key,SEM_AMOUNT,IPC_CREAT|0666)))
	{
		perror("semget error");
		return errno;
	}
	
	semBuffArr[PONG_SEM_NUM].sem_num = PONG_SEM_NUM;
	semBuffArr[PING_SEM_NUM].sem_num = PING_SEM_NUM;
	semBuffArr[PONG_SEM_NUM].sem_flg = 0;
	semBuffArr[PING_SEM_NUM].sem_flg = 0;
	
	while(memBuff->m_msgCount)
	{
		usleep(msSleep);
		
		semBuffArr[PING_SEM_NUM].sem_op = -1; 		/*down: stop if ping isn't ready*/
		if(-1 ==semop(semId,&semBuffArr[PING_SEM_NUM],1))
		{
			perror("semop error 1");
			return errno;
		}
		
		if(verbose)
		{
			puts("Reading message...");
		}
		
		printf("Process #%d received: ---%s---\n",pid, memBuff->m_text);
		
		semBuffArr[PONG_SEM_NUM].sem_op = 1;	   /*up: signal when done to read*/
		if(-1 ==semop(semId,&semBuffArr[PONG_SEM_NUM],1))
		{
			perror("semop error 2");
			return errno;
		}
	}
	
	puts("BOOOOOOMMMMMM!!!!");
	
	return 0;
}
