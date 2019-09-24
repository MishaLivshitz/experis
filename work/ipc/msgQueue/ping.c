
#include "pingpong.h"

#define BAD_ARGS_ERR 	"No such option, usage: [v - verbose, n<num of messages>, s<miliSec>, c - isCreate, d - isDelete,e - actuvate terminator f<file name>]"

int main(int argc, char* argv[])
{
	int opt;
	int verbose = 0;
	int msgNum = 3;
	int msSleep = 0;
	int isDelete = 0;
	int isEof = 0;
	int key;
	int msgId;
	int msgFlag = IPC_CREAT;
	MsgBuff msgRcv;
	MsgBuff msgSend = {PING_CHANNEL};
	
	while(-1 != (opt=getopt(argc,argv,"v n: s: c d f: e")))
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
				
			case 'd':
				isDelete = 1;
				break;
				
			case 'f':
				KeyGenFile = optarg;
				break;
				
			case 'e':
				isEof = 1;
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
	if(-1==(msgId = msgget(key,msgFlag|0666)))
	{
		perror("msgget error");
		return errno;
	}
	
	msgSend.m_pid = getpid();
	while(msgNum)
	{
		if(verbose)
		{
			printf("Sending message via channel #%d\n",PING_CHANNEL);
		}
		
		sprintf(msgSend.m_text,"You got %.2f seconds until EXPLOSION!!", msSleep/(1000.0*1000) * msgNum--); 
		usleep(msSleep);
		if(-1 == msgsnd(msgId,&msgSend,strlen(msgSend.m_text) + sizeof(int),0))
		{
			perror("msgsnd error");
			return errno;
		}
		
		if(-1 == msgrcv(msgId,&msgRcv,sizeof(int), PONG_CHANNEL, 0))
		{
			perror("msgrcv error");
			return errno;
		}
	}
	
	puts("Done sending");
	sprintf(msgSend.m_text,"BOOM!!!"); 
	
	if(isEof)
	{
		msgSend.m_type = TERMINATE_CHANNEL;
		sprintf(msgSend.m_text,"BOOM!!!"); 
	}
	
	if(-1 == msgsnd(msgId,&msgSend,STR_SIZE + sizeof(int),0))
	{
		perror("msgsnd error");
		return errno;
	}
	
	if(isDelete)
	{
		if(-1==msgctl(msgId,IPC_RMID,0))
		{
			perror("msgctl error");
			return errno;
		}
	}
	
	return 0;
}
