/*
 * This file describes the functionality of Time module
 * 
 * Author: Michael Livshitz
 * Date: 15/5/19
 * 
 * */


#ifndef _TIME_H_
#define _TIME_H_

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

typedef struct Time Time;


/*
 * @brief: This method creates a new Time instance
 * @params[in]: _clock: clock id
 * 				_deltams: the interval time
 *
 * @return: new Time when success else NULL
 * */

Time* Time_Create(clockid_t _clock, size_t _deltams);

/*
 * @brief: This method destroys a given time 
 * @params: _time: time
 *
 * */

void Time_Destroy(Time* _time);
/*
 * @brief: This method compares between 2 times
 * @params[in]: _a
 * 				_b
 *
 * @return: 0 when _a greater then _b else 1
 * */

int Time_Compare(const Time* _a, const Time* _b);


/*
 * @brief: This method returns the current time 
 * @params: _currTime: place to return the current time 
 *
 * */
int Time_GetCurrent(Time* _currTime);

/*
 * @brief: This method sets a given time 
 * @params: _time: time
 * 			_deltams: ms to add
 *
 * returns updated time when success else return NULL
 * */
Time* Time_SetTime(Time* _time, size_t _deltams);


/*
 * @brief: This method sleeps until requested time
 * 
 * @params:
 * 			_until: the time to wake up
 * */
void Time_Wait(Time* _until);
#endif
