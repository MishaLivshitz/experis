#include "meeting.h"
#include "AppDiary.h"
#define FALSE 0
#define TRUE 1

int main()
{
	int avgAppointmentAmount;
		DiaryPtr diary = NULL;
		MeetingPtr meeting= NULL;
		float begin,end;
		char subject[MAX_SUBJECT_SIZE];
		int exitFlag=FALSE, meetingIndex;
		char option;

	while(FALSE==exitFlag){
		
		puts("Options:\n");
		puts("	1: Create Ad");
		puts("	2: Create Meeting");
		puts("	3: Insert Appointment");
		puts("	4: Remove Appointment");
		puts("	5: Find Appointment");
		puts("	6: Print AppDiary");
		puts("	7: Destroy AppDiary");
		puts("	Q or q: Quit");

		puts("\nInsert your selection and press Enter:\n");
		option = getchar();
		getchar();
		switch(option){
			case '1':
			if(NULL==diary)
			{	
				printf("Insert an avarage of apointments per day:");
				scanf("%d",&avgAppointmentAmount);
				getchar();			
				diary = CreateAd(avgAppointmentAmount);
			}
			break;
			case '2':
			printf("Insert begin and end meeting time:\n\n");
			scanf("%f %f",&begin,&end);
			getchar();
			printf("Insert subject:");
			gets(subject);
			meeting = CreateMeeting(begin,end,subject);
			break;
			case '3':
			if(NULL==meeting)
			{
				printf("\nNo meeting was created\n\n");
				break;
			}
			if(INVALID_TIME==InsertMeeting(diary,meeting))
			{
				printf("\nInvalid time\n\n");
			}
			break;
			case '4':
			printf("Insert begin appointment time:\n\n");
			scanf("%f",&begin);
			getchar();
			if(MEETING_NOT_FOUND==RemoveMeeting(diary,begin))
			{
				printf("No meeting startin at: %f\n\n",begin);
			}
			break;
			case '5':
			printf("Insert begin appointment time:\n\n");
			scanf("%f",&begin);
			getchar();
			meetingIndex=FindAppointmentMeeting(diary,begin);
			if(MEETING_NOT_FOUND==meetingIndex)
			{
				printf("No meeting starting at: %f\n\n",begin);
			}
			else
			{
				PrintMeeting(diary->m_meetings[meetingIndex]);
			}
			break;
			case '6':
			if(EMPTY_DIARY==PrintAppDiary(diary))
			{
				printf("Empty diary\n\n");
			}
			break;
			case '7':
			DestroyAd(&diary);
			diary=NULL;
			break;
			case 'q':
			case 'Q':
			DestroyAd(&diary);
			DestroyMeeting(meeting);
			exitFlag=TRUE;
			break;
			default:
			printf("Please insert ");
			}
	}
}	
