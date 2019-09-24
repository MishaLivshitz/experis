#ifndef _PINGPONG_H
#define _PINGPONG_H

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif




#define PING_SEM_NUM		 0
#define PONG_SEM_NUM		 1

#define DEFAULT_MSG_NUM 	 3
#define STR_SIZE 			 90
#define DEFAULT_MEM_SIZE     200		

#define PROJ_ID				 17

#define SEM_AMOUNT			 2

typedef struct sembuf SemBuf;

typedef struct SharedMemBuff 
{
	int m_msgCount;
	char m_text[STR_SIZE];    /* message data */
}SharedMemBuff;

#endif
