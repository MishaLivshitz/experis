#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define MAX_MSG_LEN		1000
#define BAD_ARGS_ERR 	"No such option, usage: [i - <ip>; p - <port>]"
#define DEFAULT_PORT 8080

const char* ip	= "127.0.0.1";

int OpenSocket()
{
	
	int sock = socket(AF_INET,SOCK_STREAM,0);
	
	if(sock < 0)
	{
		perror("socket failed");
		return errno;
	}
	
	return sock;
}

int ClientConnect(int _sock, const char* _ip, int _port)
{
	struct sockaddr_in addr;
	
	memset(&addr,0,sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(_ip);
	addr.sin_port = htons(_port);
	
	if((connect(_sock,(struct sockaddr*)&addr, sizeof(addr))) < 0)
	{
		perror("connect failed");
		return -1;
	}
	
	return 0;
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

int main(int argc, char* argv[])
{
	
	int sock;
	int port = DEFAULT_PORT;
	int opt;
	char msg[MAX_MSG_LEN];
	
	while(-1 != (opt=getopt(argc,argv,"i:p:")))
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
	
	if( 0 > (sock = OpenSocket()))
	{
		return -1;
	}
	
	if(0 > (ClientConnect(sock, ip, port)))
	{
		return -1;
	}
	
	do	
	{
		puts("Write your message:");
		fgets(msg, MAX_MSG_LEN, stdin);
		
	}while(0<=ClientSend(sock,msg));
	
	close(sock);
	
	return 0;
}
