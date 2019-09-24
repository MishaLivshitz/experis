#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>  
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "clientServer.h"


#define BAD_ARGS_ERR 					"No such option, usage: [i - <ip>; p - <port>]"
#define IS_DISCONNECTED(C)				(!(C))	

#define DEFAULT_NUM_OF_CLIENT			100000
#define DEFAULT_PORT	 				8080
#define MAX_MSG_LEN						1000
#define RAND_RANGE						100
#define BUFFER_SIZE						100
#define CONNECT_CHANCE					30
#define SEND_RECV_CHANCE				80
#define DISCONNECT_CHANCE				80

typedef struct sigaction SigAction;

const char* ip	= "127.0.0.1";
int clientArr[DEFAULT_NUM_OF_CLIENT] = {0};
int loopCond = 1;

void CleanUp(int* _clients, int _size);

void Terminate(int sig)
{
	char* msg = "\nExiting from client\n";
	
	write(1, msg, strlen(msg)+1);
	loopCond = 0;
	CleanUp(clientArr, DEFAULT_NUM_OF_CLIENT);
	exit(0);
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

int OpenSocket()
{
	
	int sock = socket(AF_INET,SOCK_STREAM,0);
	
	if(sock < 0)
	{
		return -1;
	}
	
	return sock;
}

int ClientConnect(const char* _ip, int _port)
{
	struct sockaddr_in addr;
	int sock;
	
	if( 0 > (sock = OpenSocket()))
	{
		return sock;
	}
	
	memset(&addr,0,sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(_ip);
	addr.sin_port = htons(_port);
	
	if((connect(sock,(struct sockaddr*)&addr, sizeof(addr))) < 0)
	{
		perror("connect failed");
		return sock;
	}
	
	return sock;
}

int ClientSend(int _sock, char* _msg)
{
	int sentBytes;

	sentBytes = send(_sock,_msg,strlen(_msg),0);
	if(0>sentBytes)
	{
		perror("send failed");
		return -1;
	}
	
	memset(_msg,0,strlen(_msg));
	fflush(stdin);
	return 0;
}

int ClientRecv(int* _sock)
{
	int sentBytes;
	char buffer[BUFFER_SIZE];
	
	sentBytes = recv(*_sock,buffer,BUFFER_SIZE,0);
	if(0>sentBytes)
	{
		if(loopCond)
		{
			perror("recv failed");
			return -1;			
		}
		else
		{
			printf("Client #%d exiting\n", *_sock);
		}
	}
	else if(0==sentBytes)
	{
		close(*_sock);
		*_sock = 0;
	}
	else
	{		
		buffer[sentBytes] = '\0';
		puts(buffer);	
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

void CleanUp(int* _clients, int _size)
{
	int i;
	
	for(i=0; i<_size; i++)
	{
		if(!IS_DISCONNECTED(_clients[i]))
		{
			SetNonBlocking(_clients[i]);
			ClientRecv(&_clients[i]);
			close(_clients[i]);
		}
	}
}

int main(int argc, char* argv[])
{
	int i;
	int opt;
	int sock;
	int randNum;
	/*int numOfClients;*/
	char msg[MAX_MSG_LEN];
	int port = DEFAULT_PORT;
	SigAction terminateSigAction;
	
	while(-1 != (opt=getopt(argc,argv,"i: p: n: ")))
	{
		switch(opt)
		{
			case 'i':
				ip = optarg;
				break;
				
			case 'p':
				port = atoi(optarg);
				break;
				
			/*case 'n':
				numOfClients = atoi(optarg);
				break;*/
	
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	
	if(0>InitSigAction(&terminateSigAction,SIGINT))
	{
		return -1;
	}
	
	while(loopCond)
	{	
		for(i=0; i< DEFAULT_NUM_OF_CLIENT; i++)
		{		
			randNum = rand() % RAND_RANGE;
			if(IS_DISCONNECTED(clientArr[i]))
			{
				if(randNum < CONNECT_CHANCE)
				{
					if(0 > (sock = (ClientConnect(ip, port))))
					{	
						if(errno != EMFILE)
						{
							perror("socket failed");
							loopCond=0;				
							break;
						}	
					}
					else
					{
						clientArr[i] = sock; 						
					}
				}
			}
			else
			{
				if(randNum < SEND_RECV_CHANCE)
				{
					sprintf(msg,"I am client #%d\n" ,clientArr[i]);
					if(0>ClientSend(clientArr[i],msg))
					{
						loopCond=0;
						break;
					}
					
					if(0>ClientRecv(&clientArr[i]))
					{
						loopCond=0;
						break;
					}
				}
				else if(randNum > DISCONNECT_CHANCE)
				{
					close(clientArr[i]);
					clientArr[i] = 0;
				} 
			}
		}	
	}
	
	return 0;
}
