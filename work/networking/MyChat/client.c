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
#include <sys/select.h>

#define BAD_ARGS_ERR 					"No such option, usage: [i - <ip>; p - <port>]"
#define IS_DISCONNECTED(C)				(!(C))	

#define CLIENT_NAME						"Jackson"
#define DEFAULT_PORT	 				8080
#define DEFAULT_SELECT_MAX				1024
#define BUFFER_SIZE						100
#define MAX_MSG_LEN						255
#define NAME_TAG						1
#define MAX_TOTAL_MSG_LEN 				4 + MAX_MSG_LEN * 2

#define MSG_POS(B)						 4 + (B);

typedef struct {
	
	unsigned char m_tag;
	unsigned char m_len;
	char		  m_msg[MAX_MSG_LEN];
	
}Msg;

const char* ip	= "127.0.0.1";

int OpenSocket()
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	
	if(sock < 0)
	{
		return -1;
	}
	
	return sock;
}

int ClientConnect(const char* _ip, int _port, fd_set* _readSet)
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
	
	FD_ZERO(_readSet);
	FD_SET(sock, _readSet);
	FD_SET(0, _readSet);
	
	return sock;
}

void BuildMessage(Msg* _message, Msg* _msgName, char* _finalMsg)
{
	sprintf(_finalMsg, "%c%c%s%c%c%s",_msgName->m_tag,_msgName->m_len,_msgName->m_msg,_message->m_tag,_message->m_len,_message->m_msg);
}

int ClientSend(int _sock, fd_set* _workSet ,Msg* _msgName)
{
	int sentBytes;
	Msg message;
	char finalMessage[MAX_TOTAL_MSG_LEN];
	
	memset(message.m_msg, '\0', MAX_MSG_LEN);
	
	if(FD_ISSET(0, _workSet))
	{
		fgets(message.m_msg, MAX_MSG_LEN, stdin);
		message.m_len = strlen(message.m_msg);
		message.m_msg[message.m_len] = '\0';
		
		BuildMessage(&message, _msgName, finalMessage);
		
		sentBytes = send(_sock, finalMessage ,strlen(finalMessage) , 0);
		if(0>sentBytes)
		{
			perror("send failed");
			return -1;
		}
	}
	
	fflush(stdin);	
		
	return 0;
}

void ReadMessage(char* _buffer)
{
	char name[MAX_MSG_LEN] = {0};
	char msg[MAX_MSG_LEN]= {0};
	int namePos = 2;
	int nameLen = _buffer[1];
	int msgLen;
	int msgPos = MSG_POS(_buffer[1]);

	msgLen = _buffer[msgPos-1];
	
	memcpy(name, &_buffer[namePos], nameLen);
	memcpy(msg, &_buffer[msgPos], msgLen);
	
	name[nameLen] = '\0';
	msg[msgLen] = '\0';
	
	printf("%s: %s\n",name, msg);
}

int ClientRecv(int _sock,fd_set* _workSet)
{
	int sentBytes;
	char buffer[BUFFER_SIZE];

	if(FD_ISSET(_sock, _workSet))
	{
		sentBytes = recv(_sock,buffer,BUFFER_SIZE,0);
		if(0>sentBytes)
		{
			perror("recv failed");
			return -1;			
		}
		else if(0==sentBytes)
		{
			close(_sock);
		}
		else
		{		
			buffer[sentBytes] = '\0';
			ReadMessage(buffer);
		}
	}
	
	fflush(stdin);
	return 0;
}

int main(int argc, char* argv[])
{
	int opt;
	int sock;
	int activity;
	fd_set readSet;
	fd_set tempSet;
	int port = DEFAULT_PORT;
	Msg msgName = {NAME_TAG};

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
	
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	puts("Insert Name:");
	fgets(msgName.m_msg,MAX_MSG_LEN,stdin);
	msgName.m_len = strlen(msgName.m_msg) - 1;
	msgName.m_msg[msgName.m_len] = '\0';
	fflush(stdin);
	
	if(0 > (sock = (ClientConnect(ip, port, &readSet))))
	{	
		perror("socket failed");
		return -1;
	}	
		
	while(1)
	{	
		puts("Insert message:");
		tempSet = readSet;
		activity = select(DEFAULT_SELECT_MAX, &tempSet, NULL, NULL, NULL);	

		if(0 > activity)
		{
			perror("select failed");
			return -1;
		}
		else
		{			
			if(0>ClientSend(sock, &tempSet, &msgName))
			{
				return -1;
			}
			
			if(0>ClientRecv(sock, &tempSet))
			{
				return -1;
			}
		}
	}
	return 0;
}
