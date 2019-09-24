#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>

typedef struct sembuf SemBuf;

union semun 
{
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};


int main(int argc, char* argv[])
{
	int opt;
	int msgNum = 3;
	int semId;
	int i;
	SemBuf semBuff;
	union semun semNum;
	
	while(-1 != (opt=getopt(argc,argv,"v n: ")))
		{
			switch(opt)
			{
	
				case 'n':
					msgNum = atoi(optarg);
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
	
	semNum.val = 1;
	if(-1 == semctl(semId,0,SETVAL,semNum))
	{
		perror("semctl error");
		return errno;
	}
	
	semBuff.sem_num = 0;
	for(i=1;i<=msgNum;i++)
	{
		semBuff.sem_op = -1;
		if(-1 ==semop(semId,&semBuff,1))
		{
			perror("semop error");
			return errno;
		}
		
		printf("Hello i am print #:%d\n",i);
		sleep(1);
		semBuff.sem_op = 1;
		
		if(-1 ==semop(semId,&semBuff,1))
		{
			perror("semop error");
			return errno;
		}	
	}
	
	return 1;
}
