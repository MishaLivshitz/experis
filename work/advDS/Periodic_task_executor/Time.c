#include "Time.h"
#define MILI_TO_NANO(MS)		MS*1000*1000
#define ACTIVE_MAGIC_NUM 		0xdefdef
#define MAX_NANO				0x3B9ACA00
#define IS_VALID(T)				((T) && (T)->m_magicNum == ACTIVE_MAGIC_NUM)

struct Time
{
	int 			m_magicNum;
	struct timespec m_nextExec;
	clockid_t 		m_clockID;
};

Time* Time_Create(clockid_t _clock, size_t _deltams)
{
	
	Time* time;
	
	time = (Time*)calloc(1,sizeof(Time));
	
	if(NULL == time)
	{
		return NULL;
	}
	
	time->m_clockID = _clock;
	time->m_magicNum = ACTIVE_MAGIC_NUM;
	
	return Time_SetTime(time,_deltams);
}

void Time_Destroy(Time* _time)
{
	if(!IS_VALID(_time))
	{
		return;
	}
	
	free(_time);
}

Time* Time_SetTime(Time* _time, size_t _deltams)
{

	if(!IS_VALID(_time))
	{
		return NULL;
	}

	if(-1==clock_gettime(_time->m_clockID,&_time->m_nextExec))
	{
		return NULL;
	} 
	
	_time->m_nextExec.tv_sec+=_deltams/1000;
	
	if((_time->m_nextExec.tv_nsec + MILI_TO_NANO(_deltams%1000)) > MAX_NANO)
	{
		_time->m_nextExec.tv_sec++;
	}
	
	_time->m_nextExec.tv_nsec = (_time->m_nextExec.tv_nsec + MILI_TO_NANO(_deltams%1000)) % MAX_NANO;
	
	return _time;
}

int Time_Compare(const Time* _a, const Time* _b)
{
	
	int second = _a->m_nextExec.tv_sec - _b->m_nextExec.tv_sec; 
	long nanoSeconds = _a->m_nextExec.tv_nsec - _b->m_nextExec.tv_nsec;
	
	if(second == 0)
	{
		return nanoSeconds < 0;
	}
	
	return second < 0;
}

int Time_GetCurrent(Time* _currTime)
{
	return clock_gettime(_currTime->m_clockID,&_currTime->m_nextExec);
}

void Time_Wait(Time* _until)
{
	Time* from;
	
	if(!IS_VALID(_until))
	{
		return;
	}
	
	from = Time_Create(_until->m_clockID,0);	
	Time_GetCurrent(from);
	
	if(!Time_Compare(_until, from))
	{
		if ((_until->m_nextExec.tv_nsec - from->m_nextExec.tv_nsec) < 0)
		{
			from->m_nextExec.tv_sec = _until->m_nextExec.tv_sec - from->m_nextExec.tv_sec - 1;
			from->m_nextExec.tv_nsec = _until->m_nextExec.tv_nsec - from->m_nextExec.tv_nsec + MAX_NANO;
		} 
		else 
		{
			from->m_nextExec.tv_sec = _until->m_nextExec.tv_sec - from->m_nextExec.tv_sec;
			from->m_nextExec.tv_nsec = _until->m_nextExec.tv_nsec - from->m_nextExec.tv_nsec;
		}	

		nanosleep(&from->m_nextExec, &_until->m_nextExec);
	}
	
	Time_Destroy(from);
	
}
