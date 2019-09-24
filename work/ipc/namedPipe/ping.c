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
#include <sys/stat.h>
#include <fcntl.h>

#define BAD_ARGS_ERR 	"No such option, usage: [v-verbose, n<num of messages>, s<miliSec>, c-isCreate, d-isDelete, f<file name>]"
#define DEFAULT_PIPE_NAME   "pingPong"
#define STR_SIZE 		100

const char* fileName = DEFAULT_PIPE_NAME;

int main(int argc, char* argv[])
{
	int opt;
	int verbose = 0;
	int msgNum = 3;
	int msSleep = 0;
	int isCreate = 0;
	int isDelete = 0;
	char msgWrite[STR_SIZE]={0};
	int fd;
	int i;
	int currPid = getpid();
	
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
				isCreate = 1;
				break;
			case 'd':
				isDelete = 1;
				break;
			case 'f':
				fileName = optarg;
				break;
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	if(isCreate)
	{
		
		if(-1 == mkfifo(fileName,S_IRWXU))
		{
			perror("mkfifo failed");
			return errno;
		}
	}
	
	if(-1==(fd=open(fileName,O_WRONLY)))
	{
		perror("open file failed");
		return errno;
	}
	
	switch(verbose)
	{
	
		case 0:
			for(i=1;i<=msgNum;i++)
			{
				sprintf(msgWrite,"Process #%d: This is write #%d\n", currPid, i);
				usleep(msSleep);
				write(fd,msgWrite,strlen(msgWrite));
			}
			break;
		case 1:
			for(i=1;i<=msgNum;i++)
			{
				sprintf(msgWrite,"Process #%d: This is write #%d\n", currPid, i);
				puts("Writing...");
				usleep(msSleep);
				
				write(fd,msgWrite,strlen(msgWrite));
				puts("Sent");
			}
			puts("Done writing");
			break;
	}
	close(fd);
		
	if(isDelete)
	{
		if(-1 == unlink(fileName))
		{
				perror("unlink file failed");
				return errno;
		}
	}
	
		
	return 0;
}
