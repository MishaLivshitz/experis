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

int MyReceive(int sock, struct sockaddr_in sin);
int MySendTo(int sock,int ip, int port);


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


int MyReceive(int sock, struct sockaddr_in sin)
{

	socklen_t sinLen = sizeof(struct sockaddr);
	int readBytes;
	int ip;
	char buffer[4096];
	 
	readBytes = recvfrom(sock,buffer,sizeof(buffer), 0, (struct sockaddr*)&sin, &sinLen);
	buffer[readBytes]='\0';
	if(0>readBytes)
	{
		perror("recvfrom failed");
		return errno;
	}
	ip =  sin.sin_addr.s_addr;
	printf("Message received: %s\n",buffer);
	MySendTo(sock, ip, sin.sin_port);
	return 0;
}

int MySendTo(int sock,int ip, int port)
{
	struct sockaddr_in addr;
	int sent_bytes;
	char msg[MSG_LEN];
	memset(&addr,0,sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ip;
	addr.sin_port = htons(port);
	
	puts("Insert message:");
	fgets(msg, MSG_LEN, stdin);
	sent_bytes = sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&addr,sizeof(addr));
	
	if(sent_bytes<0)
	{
		perror("sendto failed");
		return errno;
	}
	
	MyReceive(sock ,addr);
	return 0;
}


int main(int argc, char* argv[])
{
	
	int sock;
	int ip;
	int port;
	int opt;
	
	if(argc<3)
	{
		puts(BAD_ARGS_ERR);
	}
	
	while(-1 != (opt=getopt(argc,argv,"i:p:")))
	{
		switch(opt)
		{
			case 'i':
				ip=inet_addr(optarg);
				break;
				
			case 'p':
				port = atoi(optarg);
				break;
	
			default:		 /* '?' */
				puts(BAD_ARGS_ERR);
				return 0;
		}
	}
		
	if(0 > (sock = OpenSocket()))
	{
		return sock;
	}
	
	if(0 > MySendTo(sock, ip, port))
	{
		return errno;
	}
	
	return 0;
}
