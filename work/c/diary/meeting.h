#ifndef __MEETING_H__
#define __MEETING_H__

#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define HOUR 24
#define MINUTE 60
#define STATUS_SUCCES 1
#define NULL_POINTER_ARR -1
#define ERROR -1
#define TIME_ERROR 2
#define MAX_SUBJECT_SIZE 100

typedef int status;
typedef struct meeting
{
	float m_begin;
	float m_end;
	char m_subject[MAX_SUBJECT_SIZE];

}Meeting, *MeetingPtr;

/*

Creates a single meeting


params:
		_begin: begining of a meeting
		_end: end of a meeting
		_subject: subject of a meeting
ATTENTION: end time shuold be less then start time
return poniter to meeting structure if Success else NULL;
*/

extern MeetingPtr CreateMeeting(float _begin, float _end ,const char* const _subject);

/*
Clears the meeting details

params :
		_meetingPtr: ponter to a meeting

*/
extern void DestroyMeeting(MeetingPtr _meetingPtr);

/*
print the meeting details

params :
		_meetingPtr: meeting pointer to print
*/

extern void PrintMeeting(const MeetingPtr _meetingPtr);
#endif

