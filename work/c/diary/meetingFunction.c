#include "meeting.h"

#define MAX_TIME 24.0
#define MIN_TIME 0.0

static int CheckTime(float _begin,float _end)
{

	if(_begin >= MAX_TIME || _begin < MIN_TIME || _end<MIN_TIME ||_end >= MAX_TIME)
		{
			return TIME_ERROR;
		}

	return STATUS_SUCCES;
}

MeetingPtr CreateMeeting(float _begin, float _end ,const char* const _subject)
{
	
	MeetingPtr meetingPtr = (MeetingPtr)malloc(sizeof(Meeting));
	
	if(NULL == meetingPtr || _end <= _begin, TIME_ERROR == CheckTime(_begin,_end))
		{
		return NULL;
		}
	
		strcpy(meetingPtr->m_subject,_subject);
		meetingPtr->m_begin=_begin;
		meetingPtr->m_end=_end;
		
	return meetingPtr;
}

void DestroyMeeting(MeetingPtr _meetingPtr)
{
	free(_meetingPtr);
}

void PrintMeeting(MeetingPtr _meetingPtr)
{	
	printf("Begining time:%.2f\n",_meetingPtr->m_begin);
	printf("End time:%.2f\n",_meetingPtr->m_end);
	printf("Subject:%s\n",_meetingPtr->m_subject);
}



