#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define MSG_LEN 100
#define BAD_ARGS_ERR 	"No such option, usage: [i - <ip>; p - <port>]"

int MyReceive(int sock, struct sockaddr_in addr);
int MySendTo(int sock, struct sockaddr_in addr);

int OpenSocket()
{
	
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	
	if(sock < 0)
	{
		perror("socket failed");
		return errno;
	}
	
	return sock;
}

int MyReceive(int sock, struct sockaddr_in addr)
{
	socklen_t sinLen = sizeof(addr);
	int readBytes;
	char buffer[4096];

	readBytes = recvfrom(sock,buffer,sizeof(buffer), 0, (struct sockaddr*)&addr, &sinLen);
	buffer[readBytes]='\0';
	if(0>readBytes)
	{
		perror("recvfrom failed");
		return errno;
	}
	
	printf("Message received: %s\n",buffer);
	
	return MySendTo(sock,addr);;
}

int MySendTo(int sock, struct sockaddr_in addr)
{

	int sent_bytes;
	char msg[MSG_LEN];
	
	puts("Insert message:");
	fgets(msg, MSG_LEN, stdin);
	sent_bytes = sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&addr,sizeof(addr));
	
	if(sent_bytes<0)
	{
		perror("sendto failed");
		return errno;
	}

	return MyReceive(sock,addr);;
}

int main(int argc, char* argv[])
{
	
	int sock;
	struct sockaddr_in addr;
	char ip[12];
	int	port;
	int opt=0;
	
	if(argc<3)
	{
		puts(BAD_ARGS_ERR);
	}
	
	while(-1 != (opt=getopt(argc,argv,"i:p:")))
	{
		switch(opt)
		{
			case 'i':
				strcpy(ip,optarg);
				break;
				
			case 'p':
				port = atoi(optarg);
				break;
	
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
	
	memset(&addr,0,sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	
	if(0 > (sock = OpenSocket()))
	{
		return sock;
	}
	
	if(bind(sock,(struct sockaddr*) &addr,sizeof(addr)) < 0)
	{
		perror("bind failed");
		return errno;
	}
	
	if(0 > MyReceive(sock,addr))
	{
		return errno;
	}
	
	return 0;
}
