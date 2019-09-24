#include "pingpong.h"

#define BAD_ARGS_ERR 	"No such option, usage: [v - verbose, n<num of messages>, s<miliSec>, c - isCreate, f<file name>]"
#define PING_UPDATE_TIME 500*1000
#define ORDER_PREPARE_TIME 300*1000

const char* KeyGenFile = "KeyGenerator"; 

int MsgQueInit(int msgId, int _verbose)
{
	PingPongBuff pingBuff = {PING_COUNT_CHANNEL};
	PingPongBuff pongBuff = {PONG_COUNT_CHANNEL};
	
	pingBuff.m_counts = 1;
	pongBuff.m_counts = 0;
	
	if(_verbose)
	{
		puts("DAMN i'm first!");
	}
	
	if(-1 == msgsnd(msgId,&pingBuff,sizeof(int),0))
	{
		perror("msgsnd error");
		return errno;
	}
	
	if(-1 == msgsnd(msgId,&pongBuff,sizeof(int),0))
	{
		perror("msgsnd error");
		return errno;
	}
	
	return 1;
}

int main(int argc, char* argv[])
{
	int opt,i;
	int verbose = 0;
	int msgNum = DEFAULT_MSG_NUM;
	int msSleep = 0;
	key_t key;
	int msgId;
	int msgFlag = IPC_CREAT;
	MsgBuff msgRcv;
	MsgBuff msgSend = {PING_CHANNEL};
	int pid = getpid();
	
	
	while(-1 != (opt=getopt(argc,argv,"v n: s: c f: ")))
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
	if(-1==(msgId = msgget(key,msgFlag|PERMIS)))
	{
		perror("msgget error");
		return errno;
	}
	
	if(msgFlag == IPC_CREAT)
	{
		PingPongUpdate(msgId,1,PING_COUNT_CHANNEL);
	}
	else
	{
		MsgQueInit(msgId,verbose);
	}
	
	msgSend.m_pid = pid;
	for(i=1; i<=msgNum; i++)
	{
		if(verbose)
		{
			puts("Waiting for order...");
		}
		
		usleep(msSleep);
		
		if(-1 == msgrcv(msgId,&msgRcv,sizeof(int)*2, PONG_CHANNEL, 0))
		{
			perror("msgrcv error");
			return errno;
		}
		
		if(verbose)
		{
			printf("Order #%d recieved, Prepering...\n",msgRcv.m_intData);
			usleep(ORDER_PREPARE_TIME);
			puts("Order sent");
		}
		
		sprintf(msgSend.m_text,"dish #%d is ready", msgRcv.m_intData); 
		if(-1 == msgsnd(msgId,&msgSend,strlen(msgSend.m_text)+1 + sizeof(int)*2,0))
		{
			perror("msgsnd error");
			return errno;
		}
	}
	
	printf("Chef #%d - Went home!\n",pid);
	
	if(0 == PingPongUpdate(msgId, 0, PING_COUNT_CHANNEL))
	{
		SendTerminations(msgId);
		while(1)
		{
			if(!PingPongCount(msgId,PONG_COUNT_CHANNEL))
			{
				/*if(-1==msgctl(msgId,IPC_RMID,0))
				{
					perror("msgctl error");
				}*/
				
				printf("We are closed!\n");
				break;
			}
		}
	}
	
	return 0;
}
