#define _POSIX_C_SOURCE 199309L
#include <sys/types.h>
#include <time.h>
#include "ttime.h"
#include <stddef.h>
#include <unistd.h>	/*sleep*/
#include "task.h"

#define TRUE 1
#define FALSE 0


static size_t InitialTime = 0;

size_t TimeGetCurTime(void)
{
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	return (size_t)tp.tv_sec;
}

void TimeUpdateDueTime(Task* _task, size_t _taskPeriodTime)
{
	size_t newDueTime=0;
	newDueTime = _taskPeriodTime + TimeGetCurTime(); 
	TaskUpdateDueTime(_task,newDueTime);
	return;
}

void TimeWait(size_t _time)
{
	sleep((unsigned)(_time));
	return;
}



int DueTimeComparator(const void *_firstTask, const void *_secondTask)
{

	if (TaskGetDueTime((Task *)_firstTask) > TaskGetDueTime((Task *)_secondTask))
	{
		return TRUE;
	}
	return FALSE;
}

DTC GetDueTimeCompareFunction(void)
{
	return DueTimeComparator;
}

size_t TimeGetDueTime(Task* _task)
{
	return TaskGetDueTime(_task);
}

size_t TimeGetPeriodTime(Task* _task)
{
	return TaskGetPeriodTime(_task);
}

/*void ResetDueTime(Task* _task);*/


void TimeSetInitialRefTime(void)
{
	InitialTime = TimeGetCurTime();
	return;
}

size_t TimeGetInitialRefTime(void)
{
	return InitialTime;
}