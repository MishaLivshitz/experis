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
	int msSleep = 0;
	char msgRead[STR_SIZE]={0};
	int fd;
	
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
				fileName = optarg;
				break;
				
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	if(-1==(fd=open(fileName,O_RDONLY)))
		{
			perror("open file failed");
			return errno;
		}
	
	switch(verbose)
		{
			case 0:
				while(read(fd,msgRead,STR_SIZE))
				{
					
					usleep(msSleep);
					puts(msgRead);
				}
				break;
				
			case 1:
				while(read(fd,msgRead,STR_SIZE))
				{
					puts("Reading...");
					usleep(msSleep);
					puts(msgRead);
				}
				puts("Done reading");
				break;
		}
		
	close(fd);
	return 0;
}
