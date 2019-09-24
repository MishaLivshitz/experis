#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <getopt.h>

typedef struct sembuf SemBuf;

int main(int argc, char* argv[])
{
	int opt;
	int semId;
	int pause=0, resume=0;
	SemBuf semBuff;

	while(-1 != (opt=getopt(argc,argv,"r p")))
		{
			switch(opt)
			{
				case 'p':
					pause=1;
					break;
					
				case 'r':
					resume=1;
					break;
						
				default:		 /* '?' */
					puts("Bad Arguments!");
					return 0;
			}
		}

	semId = semget(17,1,IPC_CREAT|0666);	
	if(-1==semId)
	{
		perror("semget error");
		return errno;
	}
	
	semBuff.sem_num = 0;
	if(pause && resume)
	{
		semBuff.sem_op = 1;
		if(-1 ==semop(semId,&semBuff,1))
		{
			perror("semop error");
			return errno;
		}
		
		semBuff.sem_op = -1;
		if(-1 ==semop(semId,&semBuff,1))
		{
			perror("semop error");
			return errno;
		}
		return 1;	
	}
	
	if(pause)
	{
		semBuff.sem_op = -1;
		if(-1 ==semop(semId,&semBuff,1))
		{
			perror("semop error");
			return errno;
		}
		return 1;
	}
	
	if(resume)
	{
		semBuff.sem_op = 1;
		if(-1 ==semop(semId,&semBuff,1))
		{
			perror("semop error");
			return errno;
		}
		return 1;
	}
	
	return 1;
}
