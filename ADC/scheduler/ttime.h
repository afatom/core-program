#ifndef __TTIME_H_
#define __TTIME_H_

#include "task.h"
#include <time.h>
#include <stddef.h>
/**  
 * @brief Returns the processor time consumed by the program in float structure.  
 * @param[in] void
 * @return time consumed by cpu for executing aprogram/task.
 * @retval  On failure, the function returns a value of -1.
 * @call this func twice for calculating cpu time consumption.
 */


typedef int (*DTC)(const void *_firstTask, const void *_secondTask);


size_t TimeGetCurTime(void);

void TimeUpdateDueTime(Task* _task, size_t _taskPeriodTime);

void TimeWait(size_t _time);


/*void TaskUpdateDueTime(Task** _task, size_t _taskExecutionEndTime);*/


size_t TimeGetDueTime(Task* _task);

size_t TimeGetPeriodTime(Task* _task);

void TimeResetDueTime(Task* _task);

DTC GetDueTimeCompareFunction(void);


void TimeSetInitialRefTime(void);

size_t TimeGetInitialRefTime(void);

#endif /*__TTIME_H_*/
