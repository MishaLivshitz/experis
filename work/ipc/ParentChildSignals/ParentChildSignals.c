#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define STR_SIZE 50

typedef struct sigaction SigAction;

int pSignal = 10;

void ProdFunc(int sig)
{
	char* msg = "Received answer\n";
	write(0, msg, strlen(msg)+1);
}

void ConsFunc(int sig, siginfo_t* _sigInfo, void* _DoNotUse)
{
	char msg[STR_SIZE];
	sprintf(msg,"Consumer received signal #%d from process:%d\n",sig,_sigInfo->si_pid);
	write(0, msg, strlen(msg)+1);
	kill(_sigInfo->si_pid,pSignal);
}

void InitSigAction(	SigAction* _sigAction,
					void(*_handler)(int),
					void(*_action)(int _sig,siginfo_t* _info, void* _DoNotUse),
					int _flags, int _mask)
{

	if(_flags == SA_SIGINFO)
	{
		_sigAction->sa_sigaction = _action;
		_sigAction->sa_flags = _flags;
	}
	else
	{
		_sigAction->sa_handler = _handler;
	}
	if(_mask>-1)
	{
		sigemptyset(&_sigAction->sa_mask);
	}
	
}

int main(int argc, char	*argv[])
{
	SigAction prodSigAct, consSigAct;
	int pid;
	int status = 1;
	int option;
	int flags = -1;
	int	mask = -1;
	int cSignal = 12;
	
	while(-1!=(option = getopt(argc,argv,"c:p:m:f:")))
	{
		switch(option)
		{
			case 'c':
				cSignal = atoi(optarg);
				break;
				
			case 'p':
				pSignal = atoi(optarg);
				break;
				
			case 'f':
				flags = atoi(optarg);
				break;
				
			case 'm':
				mask = atoi(optarg);
				break;
				
			case '?':
				puts("No such option, try [-c<signum> -p<signum> -m<mask> -f<flags>]\n");
				return 0;
		}
	}
	
	InitSigAction(&prodSigAct,ProdFunc,NULL,flags,mask);
	if (sigaction(pSignal, &prodSigAct, NULL) == -1)
	{
        return errno;
    }
    
    InitSigAction(&consSigAct,NULL,ConsFunc,SA_SIGINFO,mask);
	if (sigaction(cSignal, &consSigAct, NULL) == -1) 
	{
		return errno;
	}
	
	if(-1!=(pid=fork()))
	{
		if(pid==0)	/*child proc*/
		{
			pause();
		}
		else 		/*father proc*/
		{
			printf("Send signal...\n");
			kill(pid,cSignal);
			wait(&status);
		}
	}	
}
