#include "AppDiary.h"
#include "meeting.h"


static void swap(MeetingPtr* a ,MeetingPtr* b)
{
	MeetingPtr temp = *a;
	*a=*b;
	*b=temp;
}


static void ShiftMeetingsRight(DiaryPtr _diary,int startIndex)
{
	while(startIndex < _diary->m_meetingCurrSize)
	{
		swap(&(_diary->m_meetings[startIndex]),&(_diary->m_meetings[startIndex+1]));
		startIndex++;
	}	
}

static void ShiftMeetingsLeft(DiaryPtr _diary,int startIndex)
{
	int i;
	for(i=startIndex;i<_diary->m_meetingCurrSize;i++)
	{
		swap(&(_diary->m_meetings[i]),&(_diary->m_meetings[i-1]));
	}
}

static status AdReallocation(const DiaryPtr _diary, int resizeFlag)
{
	MeetingPtr* tempMeetingsArr = NULL;
	int newSize;
	if(resizeFlag == INCREASE_FLAG)
	{
		newSize=_diary->m_diarySize * DEFAULT_RESIZE_MULTIPLIER;
	}
	else
	{
		newSize=_diary->m_diarySize / DEFAULT_RESIZE_DIVIDER;
	}
	
	tempMeetingsArr = (MeetingPtr*)realloc(_diary->m_meetings,sizeof(MeetingPtr)*newSize);
	
	if(NULL!=tempMeetingsArr)
	{
		_diary->m_meetings = tempMeetingsArr;
		_diary->m_diarySize = newSize;
	}
	else 
	{
		return REALLOCATION_FAILED;
	}

	return STATUS_SUCCES;
}

static status CheckOverLap(const DiaryPtr _diary, const MeetingPtr newMeeting, int index)
{	
	if(0 == _diary->m_meetingCurrSize)
	{
		return STATUS_SUCCES;
	}
	
	if(0 == index && _diary->m_meetings[index]->m_end <= newMeeting->m_begin)
	{
		return STATUS_SUCCES;
	}

	if(index == _diary->m_meetingCurrSize && _diary->m_meetings[index-1]->m_end <= newMeeting->m_begin)
	{
		return STATUS_SUCCES;
	}

	if(_diary->m_meetings[index-1]->m_end <= newMeeting->m_begin && _diary->m_meetings[index]->m_begin >= newMeeting->m_end)
	{
		return STATUS_SUCCES;
	}

	return OVERLAP_ERR;
}

static int FindPlaceToInsert(const DiaryPtr _diary, const MeetingPtr _newMeeting)
{
	int i;
	for(i=0;i<_diary->m_meetingCurrSize;i++)
	{
		if(_newMeeting->m_end <= _diary->m_meetings[i]->m_begin)
		{
			break;
		}
	}

	if(0 != _diary->m_meetingCurrSize && OVERLAP_ERR==CheckOverLap(_diary,_newMeeting,i))
	{
		return INVALID_TIME;
	}

	return i;
}

DiaryPtr CreateAd(int _defaultSize)
{
  	DiaryPtr diaryPtr = (DiaryPtr)malloc(sizeof(Diary)); 
	
  	if(NULL == diaryPtr)
	{
		return NULL;
	}
	
	diaryPtr->m_meetings = (MeetingPtr*)calloc(_defaultSize,sizeof(MeetingPtr));

	if(NULL==diaryPtr->m_meetings)
	{	
		free(diaryPtr);
		return NULL;
	}

	diaryPtr->m_diarySize=_defaultSize;
	diaryPtr->m_meetingCurrSize=0;
	
	return diaryPtr;
}

status RemoveMeeting(const DiaryPtr _diary,float _begin)
{

	int index;
	
	index=FindAppointmentMeeting(_diary,_begin);
	if(MEETING_NOT_FOUND!=index)
	{	
		DestroyMeeting(_diary->m_meetings[index]);
		_diary->m_meetings[index]=NULL;
		ShiftMeetingsLeft(_diary,index+1);
		_diary->m_meetingCurrSize--;
		
		if(_diary->m_diarySize/_diary->m_meetingCurrSize>=DECREASE_CONDITION)
		{
			if(REALLOCATION_FAILED==AdReallocation(_diary,INCREASE_FLAG))
			{
				return REALLOCATION_FAILED;
			}
		}

		return REMOVE_SUCCES;
	}	
	
	return MEETING_NOT_FOUND;
}

status InsertMeeting(const DiaryPtr _diary , MeetingPtr _newMeeting)
{
	int indexToInsert=0;
	
	if(NULL ==_diary||NULL==_newMeeting)
	{
		return NULL_POINTER_ARR;
	}

	if(_diary->m_diarySize <= _diary->m_meetingCurrSize)
	{
		if(REALLOCATION_FAILED==AdReallocation(_diary,INCREASE_FLAG))
		{
			return REALLOCATION_FAILED;
		}
	}

	if(NULL!=_diary->m_meetings && NULL!= _newMeeting)
	{	
		indexToInsert = FindPlaceToInsert(_diary,_newMeeting);
		if(INVALID_TIME==indexToInsert)
		{
			return INVALID_TIME;
		}
		if(0!=indexToInsert && _diary->m_meetingCurrSize > 0)
		{
			ShiftMeetingsRight(_diary,indexToInsert);
		}

		_diary->m_meetings[indexToInsert] = _newMeeting;
		_diary->m_meetingCurrSize++;
		return STATUS_SUCCES;
	}
	
	return MEMORY_ALLOCATION_FAILED;
	
}

int FindAppointmentMeeting(const DiaryPtr _diary , float _begin)
{
	int i;

	if(NULL==_diary)
	{
		return ERROR;
	}

	for(i=0;i<_diary->m_meetingCurrSize;i++)
	{
		if(_begin == _diary->m_meetings[i]->m_begin)
		{
			return i;
		}
	}

	return MEETING_NOT_FOUND;
}

status PrintAppDiary(const DiaryPtr _diary)
{
	int i;

	if(NULL!=_diary && _diary->m_meetingCurrSize>0)
	{
		for(i=0;i<_diary->m_meetingCurrSize;i++)
		{	printf("meeting #%d:\n",i+1);
			PrintMeeting(_diary->m_meetings[i]);
		}

		return STATUS_SUCCES;
	}

	return EMPTY_DIARY;
}

void DestroyAd(DiaryPtr* _diary)
{
	int i;

	if(NULL==_diary)
	{
		return;
	}

	for (i=0;i<(*_diary)->m_meetingCurrSize;i++)
	{
		DestroyMeeting((*_diary)->m_meetings[i]);
		(*_diary)->m_meetings[i]=NULL;
	}

	free(*_diary);
	*_diary = NULL;
}


