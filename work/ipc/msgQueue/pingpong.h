#ifndef _PINGPONG_H
#define _PINGPONG_H

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define PING_CHANNEL		 5
#define PONG_CHANNEL		 7
#define TERMINATE_CHANNEL	 6
#define DEFAULT_MSG_NUM 	 3
#define STR_SIZE 			 90

#define PROJ_ID				 17
#define TERMINATE_MSG 		"BOOM!!!"

const char* KeyGenFile = "KeyGenerator"; 

typedef struct MsgBuff 
{
	long m_type;       /* message type, must be > 0 */
	int m_pid;
	char m_text[STR_SIZE];    /* message data */
}MsgBuff;

#endif
