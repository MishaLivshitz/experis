
#include "pingpong.h"


int PingPongCount(int _msgId,int _channel)
{
	PingPongBuff pBuff;

	if(-1 == msgrcv(_msgId,&pBuff,sizeof(int), _channel, 0))
	{
		perror("msgrcv error");
		return errno;
	}
	
	
	if(-1 == msgsnd(_msgId,&pBuff,sizeof(int),0))
	{
		perror("msgsnd error");
		return errno;
	}
	
	
	return pBuff.m_counts;
}

int PingPongUpdate(int _msgId,int _isNew, int _channel)
{
	PingPongBuff pBuff;
	
	if(-1 == msgrcv(_msgId,&pBuff,sizeof(int), _channel, 0))
	{
		perror("msgrcv error");
		return errno;
	}
	
	_isNew ? pBuff.m_counts++: pBuff.m_counts--;
	
	if(!pBuff.m_counts && _channel == PING_COUNT_CHANNEL)
	{
		return 0;
	}
	
	if(-1 == msgsnd(_msgId,&pBuff,sizeof(int),0))
	{
		perror("msgsnd error");
		return errno;
	}

	return pBuff.m_counts;
	
}

int SendTerminations(int _msgId)
{
	MsgBuff msgSend = {TERMINATE_CHANNEL};
	
	sprintf(msgSend.m_text,"We are closed!");
	if(-1 == msgsnd(_msgId,&msgSend,STR_SIZE+sizeof(int)*2,0))
	{
		perror("msgsnd error");
		return errno;
	}
	
	return 0;
}
