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
#include <fcntl.h>
#include "list.h"
#include "list_itr.h"

#define BACK_LOG_SIZE 					1000
#define BAD_ARGS_ERR 					"No such option, usage: [i - <ip>; p - <port> d - <Queue size>]"
#define BUFFER_SIZE 					4096
#define DEFAULT_PORT 					8080
#define ACK_MSG							"OK"
#define MAX_USERS						1000

typedef struct sigaction SigAction;
const char* ip	= "127.0.0.1";
int actionFlag = 1;

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

int SetNonBlocking(int sock)
{
	int flags;
	
	if(-1== (flags = fcntl(sock,F_GETFL)))
	{
		perror("fcntl.F_GETFL");
		return -1;
	}
	
	if(-1== (fcntl(sock,F_SETFL, flags|O_NONBLOCK)))
	{
		perror("fcntl.F_SETFL");
		return -1;
	}
	
	return sock;
}

int ServerAccept(int _port, int _listenSock, List* _connectedList)
{
	int clientSocket;
	struct sockaddr_in sin;
	socklen_t sockLen = sizeof(sin);
	
	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_port = htons(_port);
	
	clientSocket = accept(_listenSock, (struct sockaddr *)&sin, &sockLen);
	
	if(List_Size(_connectedList) >= MAX_USERS)
	{
		close(clientSocket);
	}
	else if(0 < clientSocket) 
	{
		if(-1 == (clientSocket = SetNonBlocking(clientSocket)))
		{
			perror("SetNonBlocking");
			return -1;
		}
		
		if(NULL == ListItr_Insert(ListItr_Begin(_connectedList), (void*)((size_t)clientSocket)))
		{
			perror("ListItr_Insert failed");
			return -1;
		}
		printf("sock connected = %d\n",clientSocket);
	}
	else if(errno != EAGAIN && errno != EWOULDBLOCK)
	{
		perror("accept failed");
		return -1;
	}
	
	return 0;
}

int ServerSend(int _sock)
{
	int sentBytes;

	sentBytes = send(_sock,ACK_MSG,strlen(ACK_MSG),0);
	if(0>sentBytes)
	{
		perror("send failed");
		return -1;
	}
	
	return 1;
}

int ServerRecv(List* _connectedClients)
{
	int readBytes;
	char buffer[BUFFER_SIZE];
	int expectedDataLen = sizeof(buffer);
	size_t clientSocket=0;
	ListItr itr;
	ListItr temp;
	
	if(NULL == _connectedClients)
	{
		kill(getpid(), SIGINT);
	}
	
	for(itr = ListItr_Begin(_connectedClients); itr != ListItr_End(_connectedClients); itr = ListItr_Next(itr))
	{
		clientSocket = (size_t)ListItr_Get(itr);
		readBytes = recv(clientSocket, buffer,expectedDataLen,0);
		if(0 == readBytes)
		{ 	
			temp = itr;
			itr = ListItr_Next(itr);
			ListItr_Remove(temp);
			close(clientSocket);
		} 			
		else if(readBytes > 0)		
		{ 			
			buffer[expectedDataLen] = '\0';			
			puts(buffer); 			
			memset(buffer,0,BUFFER_SIZE); 
					
			if(0>ServerSend(clientSocket))
			{
				return -1;
			}
		}
		else if(errno != EAGAIN && errno != EWOULDBLOCK) 		
		{ 			
			perror("recv failed"); 			
			return -1; 		
		} 	
	}
	
	return 0;
}

int Server_Up(int port, int _backLog)
{
	int sock;
	int optval = 1;
	struct sockaddr_in sin;
	
	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_port = htons(port);
	
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
	
	if(bind(sock,(struct sockaddr*)&sin,sizeof(sin)) < 0)
	{
		perror("bind failed");
		return sock;
	}
	
	if((listen(sock,_backLog))<0)
	{
		perror("listen failed");
		return sock;
	}
	
	if(-1 == (sock = SetNonBlocking(sock)))
	{
		perror("SetNonBlocking");
		return -1;
	}
	
	puts("Listening...");
	
	return sock;
}

int CleanUp(void* _socket)
{
		close((size_t)_socket);
		return 1;
}

int main(int argc, char* argv[])
{
	int opt=0;
	int listenSock;
	List* connectedList;
	int	port = DEFAULT_PORT;
	int backlog = BACK_LOG_SIZE;
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
	
	connectedList = List_Create();
	if(!connectedList)
	{
		return -1;
	}
	
	if(0>InitSigAction(&terminateSigAction,SIGINT))
	{
		return -1;
	}
	
	if((listenSock = Server_Up(port, backlog))<0)
	{
		return -1;
	}
	
	while(actionFlag)
	{	
		if(0 > ServerAccept(port, listenSock, connectedList))
		{
			break;
		}
	
		if(0 > ServerRecv(connectedList))
		{
			break;
		}
	}
	
	List_Destroy(connectedList,(AdtItemDestroy)CleanUp);
	close(listenSock);
	
	return 0;
}
