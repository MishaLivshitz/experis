#include "pingpong.h"

#define BAD_ARGS_ERR 	"No such option, usage: [v-verbose, s<miliSec>, f<file name>, i - isFirst]"
#define RAND_RANGE 100

const char* KeyGenFile = "KeyGenerator"; 

int main(int argc, char* argv[])
{
	int opt;
	int verbose = 0;
	int msSleep = 0;
	key_t key;
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
	
	if(-1==(key = ftok(KeyGenFile,PROJ_ID)))
	{
		perror("ftok error");
		return errno;
	}
		
	if(-1==(msgId = msgget(key,IPC_CREAT|PERMIS)))
	{
		perror("msgget error");
		return errno;
	}
	
	PingPongUpdate(msgId,1,PONG_COUNT_CHANNEL);
	
	msgSend.m_pid = pid;
	while(1)
	{
		usleep(msSleep);
		
		msgSend.m_intData = rand()%100 + 1;
		if(verbose)
		{
			printf("Ordering dish #%d\n",msgSend.m_intData);
		}
		
		if(-1 == msgsnd(msgId,&msgSend,sizeof(int)*2,0))
		{
			perror("msgsnd error");
			return errno;
		}
		
		if(verbose)
		{
			puts("Reading msg...");
		}
		
		if(-1 != msgrcv(msgId,&msgRcv,STR_SIZE+sizeof(int)*2, -TERMINATE_CHANNEL, 0))
		{
			if(msgRcv.m_type == TERMINATE_CHANNEL)
			{
				break;
			}
			printf("%s from:%d\n",msgRcv.m_text,msgRcv.m_pid);	
		}
	}
	
	if(PingPongUpdate(msgId, 0, PONG_COUNT_CHANNEL))
	{
		SendTerminations(msgId);		
	}
	
	puts("Thanks, Goodbye!");
	
	return 0;
}
