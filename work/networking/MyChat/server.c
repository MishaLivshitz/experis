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
#include <sys/select.h>
#include <sys/time.h>
#include "list.h"
#include "list_itr.h"
#include "clientServer.h"

#define BACK_LOG_SIZE 					1000
#define BAD_ARGS_ERR 					"No such option, usage: [i - <ip>; p - <port> d - <Queue size>]"
#define BUFFER_SIZE 					4096
#define DEFAULT_PORT 					8080
#define ACK_MSG							"OK"
#define MAX_USERS						1000
#define DEFAULT_SELECT_MAX				1024
#define DEFAULT_TIMEOUT_SEC				60

typedef struct sigaction SigAction;

typedef struct
{
	int m_fd;
	struct timeval m_timeVal;
	
}ListItem;


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

ListItem* CreateListItem(int _fd, struct timeval* _timeOut)
{
	ListItem* item;
	
	item = (ListItem*)malloc(sizeof(ListItem));
	if(!item)
	{
		return NULL;
	}
	
	item->m_fd = _fd;
	gettimeofday(&item->m_timeVal, NULL);
	item->m_timeVal.tv_sec += _timeOut->tv_sec;
	item->m_timeVal.tv_usec += _timeOut->tv_usec;
	
	return item;
}

void SetSelect(int _listenSock, fd_set* _listenSet, struct timeval* _timeOut)
{
	FD_ZERO(_listenSet);
	FD_SET(_listenSock, _listenSet);
	_timeOut->tv_sec = DEFAULT_TIMEOUT_SEC;
	_timeOut->tv_usec = 0;
}

int ServerAccept(int _port, int _listenSock, List* _connectedList, fd_set* _readSet, fd_set* _tempSet, struct timeval* _timeOut ,int _activity)
{

	int clientSocket;
	struct sockaddr_in sin;
	ListItem* item = NULL;
	socklen_t sockLen = sizeof(sin);
	
	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_port = htons(_port);
	
	if(FD_ISSET(_listenSock, _tempSet))
	{
		clientSocket = accept(_listenSock, (struct sockaddr *)&sin, &sockLen);
		
		if(List_Size(_connectedList) >= MAX_USERS)
		{
			close(clientSocket);
		}
		else if(0 < clientSocket) 
		{
			if(NULL == (item = CreateListItem(clientSocket, _timeOut)))
			{
				perror("CreateListItem failed");
				return -1;
			}
			
			FD_SET(clientSocket, _readSet);
	
			if(LIST_NOT_INITIALIZED == List_PushTail(_connectedList, item))
			{
				perror("ListItr_Insert failed");
				return -1;
			}
			printf("sock connected = %d\n",clientSocket);
		}
		else
		{
			perror("accept failed");
			return -1;
		}
	}
	return 0;
}

int ServerSend(int _sock,List* _connectedClients, char* _buffer)
{
	int sentBytes;
	int clientToSend;
	ListItr itr;
	
	for(itr = ListItr_Begin(_connectedClients); itr != ListItr_End(_connectedClients); itr = ListItr_Next(itr))
	{
		clientToSend = ((ListItem*)ListItr_Get(itr))->m_fd;
		
		if(clientToSend == _sock)
		{
			continue;
		}
		
		sentBytes = send(clientToSend,_buffer,strlen(_buffer),0);
		
		if(0>sentBytes)
		{
			perror("send failed");
			return -1;
		}
	}

	return 1;
}

int ServerRecv(List* _connectedClients, fd_set* _readSet, fd_set* _tempSet, int _activity)
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
	
	for(itr = ListItr_Begin(_connectedClients); itr != ListItr_End(_connectedClients) && _activity; itr = ListItr_Next(itr))
	{
		clientSocket = ((ListItem*)ListItr_Get(itr))->m_fd;
		
		if(FD_ISSET(clientSocket, _tempSet))
		{
			readBytes = recv(clientSocket, buffer, expectedDataLen,0);
			if(0 == readBytes)
			{ 	
				temp = itr;
				itr = ListItr_Next(itr);
				ListItr_Remove(temp);
				close(clientSocket);
				FD_CLR(clientSocket, _readSet);	
			} 			
			else if(readBytes > 0)		
			{ 					
				if(0>ServerSend(clientSocket,_connectedClients,(void*)buffer))
				{
					return -1;
				}
			}
			else
			{ 			
				perror("recv failed"); 			
				return -1; 		
			}
			
			_activity--; 	
		}
	}

	return 0;
}

int Server_Up(int port, int _backLog, fd_set* _listenSet, struct timeval* _timeOut)
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
	
	SetSelect(sock, _listenSet, _timeOut);

	puts("Listening...");
	
	return sock;
}

int CleanUp(void* _socket)
{
		close((size_t)_socket);
		return 1;
}

int IsPassedTime(struct timeval* _time)
{
	struct timeval curr;
	
	gettimeofday(&curr, NULL);
	
	if(curr.tv_sec > _time->tv_sec || curr.tv_usec > _time->tv_usec)
	{
		return 1;
	}
	
	return 0;
}

int ClearZombies(List* _connected, fd_set* _readSet)
{
	ListItr temp = NULL;
	ListItem* item;
	ListItr itr = ListItr_End(_connected);
	
	itr = ListItr_Prev(itr);		
	while(List_Size(_connected))
	{
		item = ListItr_Get(itr);
		if(IsPassedTime(&item->m_timeVal))
		{
			temp = itr;
			itr = ListItr_Prev(itr);
			ListItr_Remove(temp);
			close(item->m_fd);
			FD_CLR(item->m_fd, _readSet);
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int opt=0;
	int listenSock;
	fd_set	readSet;
	fd_set	tempSet;
	int activity = 0;
	struct timeval timeOut;
	struct timeval tempTimeOut;
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
	
	if((listenSock = Server_Up(port, backlog, &readSet, &timeOut))<0)
	{
		return -1;
	}
	
	while(actionFlag)
	{	
		
		tempSet = readSet;
		tempTimeOut = timeOut;
		activity = select(DEFAULT_SELECT_MAX, &tempSet, NULL, NULL, &tempTimeOut);	
		
		if(0>activity)
		{
			perror("select failed");
			return -1;
		}
		
		if(0 == activity)
		{
			ClearZombies(connectedList,&readSet);
		}
		
		if(0 > ServerAccept(port, listenSock, connectedList, &readSet, &tempSet, &tempTimeOut, activity))
		{
			break;
		}
	
		if(0 > ServerRecv(connectedList, &readSet, &tempSet, activity))
		{
			break;
		}
	}
	
	List_Destroy(connectedList,(AdtItemDestroy)CleanUp);
	FD_CLR(listenSock, &readSet);
	close(listenSock);
	
	return 0;
}
