
#ifndef __AD__H__ 
#define __AD__H__ 

#include<stdio.h>
#include<stdlib.h>
#include "meeting.h"

#define MEMORY_ALLOCATION_FAILED -1
#define REMOVE_SUCCES 1
#define MEETING_NOT_FOUND -1
#define EMPTY_DIARY 0
#define DEFAULT_RESIZE_MULTIPLIER 2
#define DEFAULT_RESIZE_DIVIDER 2
#define DECREASE_CONDITION 4
#define INVALID_TIME -1
#define OVERLAP_ERR -1
#define REALLOCATION_FAILED -1
#define INCREASE_FLAG 1
#define DECREASE_FLAG -1

typedef struct diary{

	MeetingPtr* m_meetings;
	int m_meetingCurrSize;
	int m_diarySize;

}Diary,*DiaryPtr;
/*
Creating appointment diary

params:
	_defaultSize: defalut size given by the user

return pointer to pointers to meetings if succes else NULL
*/

extern DiaryPtr CreateAd(int _defaultSize); 

/*
Removes meeting from the diary by begin hour

params :
	_diary : diary
	_begin: begin hour
	_diarySize: size of the diary
return REMOVE_SUCCES if succes else MEETING_NOT_FOUND
*/
extern int RemoveMeeting(const DiaryPtr _diary,float _begin);

/*
Inserts a meeting to appointment diary
params :
	_diary : diary
	_newMeeting: new meeting

return STATUS_SUCCES if succes else INSERT_ERROR (memory allocation failed) or INVALID_TIME
*/

extern int InsertMeeting(const DiaryPtr _diary , MeetingPtr _newMeeting);

/*
Finds meeting from the diary by begin hour

params :
	_diary : diary
	_begin: begin hour
	_diarySize: size of the diary
return index of meeting if succes else return NULL
*/
extern int FindAppointmentMeeting(const DiaryPtr _diary , float _begin);

/*
Destroys the diary

params:_diary : diary
	_diarySize: size of the diary
*/
extern void DestroyAd(DiaryPtr* _diary);

/*
prints the diary

params: _diary : diary
	diarySize: size of the diary
return STATUS_SUCCES if succes else EMPTY_DIARY
*/
extern int PrintAppDiary(const DiaryPtr _diary);

#endif

