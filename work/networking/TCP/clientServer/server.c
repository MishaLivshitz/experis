#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h> 
#include <arpa/inet.h>
#include <getopt.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>

#define BACK_LOG_SIZE 1
#define IP_LEN 12
#define BAD_ARGS_ERR 	"No such option, usage: [i - <ip>; p - <port> d - <Queue size>]"
#define BUFFER_SIZE 4096
#define DEFAULT_PORT 8080
#define ACK_MSG		"OK"

typedef struct sigaction SigAction;
const char* ip	= "127.0.0.1";
int actionFlag = 1;
int clientSocket;
int listenSock;

void Terminate(int sig)
{
	char* msg = "\nClosing server\n";
	write(1, msg, strlen(msg)+1);
	actionFlag = 0;
}

int InitSigAction(SigAction *_sigAction, int _sigNum)
{
	_sigAction->sa_handler = Terminate;
	if (sigaction(_sigNum, _sigAction, NULL) == -1)
	{
		perror("sigaction failed");
        return errno;
    }
    
    return 0;
}

/*int ServerSend(int _sock)
{
	int sentBytes;

	sentBytes = send(_sock,ACK_MSG,strlen(ACK_MSG),0);
	if(0>sentBytes)
	{
		perror("send failed");
		return -1;
	}
	
	return 1;
}*/

int Server_Up(struct sockaddr_in* _sin, int _back_log)
{
	int sock;
	int optval = 1;
	
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket failed");
		return sock;
	}
	
	if((setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))) < 0)
	{
		perror("setsockopt failed");
		return sock;
	}
	
	if(bind(sock,(struct sockaddr*) _sin,sizeof(struct sockaddr_in)) < 0)
	{
		perror("bind failed");
		return sock;
	}
	
	if((listen(sock,_back_log))<0)
	{
		perror("listen failed");
		return sock;
	}
	
	return sock;
}

int main(int argc, char* argv[])
{
	
	struct sockaddr_in addr;
	int	port = DEFAULT_PORT;
	int opt=0;
	int backlog = BACK_LOG_SIZE;
	int readBytes;
	char buffer[BUFFER_SIZE];
	int expectedDataLen = sizeof(buffer);
	socklen_t sockLen = sizeof(addr);
	SigAction terminateSigAction;

	while(-1 != (opt=getopt(argc,argv,"i: p: d: ")))
	{
		switch(opt)
		{
			case 'i':
				ip = optarg;
				break;
				
			case 'p':
				port = atoi(optarg);
				break;
				
			case 'd':
				backlog = atoi(optarg);
				break;
	
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	if(0>InitSigAction(&terminateSigAction,SIGINT))
	{
		return -1;
	}
	
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	
	if((listenSock = Server_Up(&addr,backlog))<0)
	{
		return -1;
	}
	puts("Listening...");
	
	clientSocket = accept(listenSock, (struct sockaddr *)&addr, &sockLen);
	if(clientSocket<0)
	{
		perror("accept failed");
		return -1;
	}
	
	while(actionFlag)
	{	
		readBytes = recv(clientSocket, buffer,expectedDataLen, 0);
		if(0 == readBytes)
		{
			actionFlag ^= actionFlag;
		}
		else if(0 > readBytes)
		{
			perror("recv failed");
			return -1;
		}
		else
		{
			buffer[expectedDataLen] = '\0';
			puts(buffer);
			memset(buffer,0,BUFFER_SIZE);
		}
		
		/*ServerSend(clientSocket);*/
	}
	close(clientSocket);
	close(listenSock);
	puts("hey there");
	return 0;
}
