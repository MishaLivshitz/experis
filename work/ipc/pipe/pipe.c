
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>


#define BAD_ARGS_ERR 	"No such option, usage: [v-verbose, n<num of messages>, p<miliSec>, c<miliSec>,r<read size>]"
#define READ_SIDE 		0
#define WRITE_SIDE		1
#define BUFF_SIZE 		50

int main(int argc, char* argv[])
{
	int opt;
	int verbose = 0;
	int msgNum = 3;
	int pSleep = 0;
	int cSleep = 0;
	int readSize = 20;
	int pfd[2];
	int pid;
	char msgWrite[BUFF_SIZE];
	char* msgRead;
	int i;
	
	while(-1 != (opt=getopt(argc,argv,"v n: p: c: r:")))
	{
		switch(opt)
		{
			case 'v':
				verbose = 1;
				break;
			case 'n':
				msgNum = atoi(optarg);
				break;
			case 'p':
				pSleep = atoi(optarg) * 1000;
				break;
			case 'c':
				cSleep = atoi(optarg) * 1000;
				break;
			case 'r':
				readSize = atoi(optarg);
				break;
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	 if (pipe(pfd) == -1) 
	 { 
		 perror("pipe"); 
		 return errno;
	 }
	
	if(-1 == (pid=fork()))
	{
		 perror("fork"); 
		 return errno;
	}
	
	if(pid==0)				/*child proc*/
	{
		close(pfd[WRITE_SIDE]);
		msgRead = malloc(strlen(msgWrite));
		
		if(!msgRead)
		{
			perror("malloc"); 
			return errno;
		}
		
		while(read(pfd[READ_SIDE],msgRead,readSize)>0)
		{
			switch(verbose)
			{
				case 0:
					usleep(cSleep);
					printf("Message received:%s\n\n",msgRead);
					break;
					
				case 1:
					puts("Reading message...");
					usleep(cSleep);
					printf("Message received:%s\n\n",msgRead);
					break;
			}
			
		}
		close(pfd[READ_SIDE]);
		free(msgRead);
		
	}
	else 					/*parent proc*/
	{
		close(pfd[READ_SIDE]);
		for(i=1;i<=msgNum;i++)
		{
			
			switch(verbose)
			{
				case 0:
					sprintf(msgWrite, "Messege #%d\n", i);
					usleep(pSleep);
					write(pfd[WRITE_SIDE],msgWrite,strlen(msgWrite));
					break;
					
				case 1:
					sprintf(msgWrite, "Messege #%d\n", i);
					puts("Writing message...");
					usleep(pSleep);
					write(pfd[WRITE_SIDE],msgWrite,strlen(msgWrite));
					puts("Message sent");
					break;
			}
			
		}
		close(pfd[WRITE_SIDE]);
		wait(NULL);
	}
	
	
	
	
	return 0;
}
