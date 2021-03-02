#include "task.h"
#include <stdlib.h> 	/*malloc*/


/******************************************************************************/
struct Task {
size_t 			m_periodTime;
size_t 			m_dueTime;
TaskFunction 	m_userFunction;
void*			m_functionContext;
};
/******************************************************************************/

#define FALSE 0
#define TRUE 1


/*
int DueTimeCompare(const Task *_firstTask, const Task *_secondTask);
*/

/******************************************************************************/
Task* TaskCreate(size_t _period,TaskFunction _userFunction, void* _context)
{
	Task* task = NULL;
	task=(Task*)malloc(sizeof(Task));
	if(NULL == task)
	{
		return NULL;
	}
	task->m_periodTime=_period;
	task->m_dueTime = _period;
	task->m_userFunction = _userFunction;
	task->m_functionContext = _context;
	return task;
}
/******************************************************************************/
void TaskDestroy(void* _task)
{
	if(NULL == _task)
	{
		return;
	}
	free(_task);
	return;
}
/******************************************************************************/
TaskTerminator GetTaskTerminatorPointer(void)
{
	return TaskDestroy;
}
/******************************************************************************/
/*task execution cpu end time - when misiion finish its job*/

void TaskUpdateDueTime(Task* _task, size_t _newDueTime)
{
	_task->m_dueTime = _newDueTime;
	return;
}

/******************************************************************************/
size_t TaskGetDueTime(Task* _task)
{
	return _task->m_dueTime;
}
/******************************************************************************/
size_t TaskGetPeriodTime(Task* _task)
{
	return _task->m_periodTime;
}



/******************************************************************************/
int TaskExecution(Task* _task)
{
	return _task->m_userFunction(_task->m_functionContext);
}
/******************************************************************************/






