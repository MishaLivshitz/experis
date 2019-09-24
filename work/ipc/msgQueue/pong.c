
#include "pingpong.h"

#define BAD_ARGS_ERR 	"No such option, usage: [v-verbose, s<miliSec>, f<file name>]"

int main(int argc, char* argv[])
{
	int opt;
	int verbose = 0;
	int msSleep = 0;
	
	int key;
	int msgId;
	MsgBuff msgRcv;
	MsgBuff msgSend = {PONG_CHANNEL};
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
	if(-1==(msgId = msgget(key,IPC_CREAT)))
	{
		perror("msgget error");
		return errno;
	}
	msgSend.m_pid = pid;
	while(1)
	{
		if(-1 != msgrcv(msgId,&msgRcv,STR_SIZE+sizeof(int), -TERMINATE_CHANNEL, 0))
		{
			if(!strcmp(msgRcv.m_text,TERMINATE_MSG) || msgRcv.m_type == TERMINATE_CHANNEL)
			{
				break;
			}
			
			if(verbose)
			{
				puts("Reading msg...");
			}
			
			usleep(msSleep);
			printf("%s from:%d\n",msgRcv.m_text,msgRcv.m_pid);
			
			if(-1 == msgsnd(msgId,&msgSend,0,0))
			{
				perror("msgsnd error");
				return errno;
			}
		}
	}
	
	puts(msgRcv.m_text);
	
	return 0;
}
