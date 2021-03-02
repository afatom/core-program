#include "manager.h"
#include "task.h"
#include "scheduler.h"
#include <stdlib.h>

#define MANAGER_VALID 0xBEEFBEEF
#define MANAGER_DESTROYED 0xDEADBEEF
#define BLOCK_SIZE 15
#define NDEBUG
#define TRUE 1
#define FALSE 0
/******************************************************************************/
struct Manager{
	Scheduler* m_scheduler;
};
/******************************************************************************/
Manager* ManagerCreate(void)
{
	Manager* man = NULL;
	man = (Manager*)malloc(sizeof(Manager));
	if(man == NULL)
	{
		return NULL;
	}
	
	man->m_scheduler = SchedulerCreate();
	if(NULL == man->m_scheduler)
	{
		free(man);
		return NULL;
	}
	return man;	
}
/******************************************************************************/
/*void* first element and second is context(family of functions)*/
void ManagerDestroy(Manager** _manager)
{
	Scheduler* ptr = NULL;
	if(NULL == _manager || NULL == *_manager )
	{
		return;
	}
	ptr = (*_manager)->m_scheduler;
	SchedulerDestroy(&ptr);
	free(*_manager);
	*_manager=NULL;
	return;
}
/******************************************************************************/
ADTStatus ManagerAppendTask(Manager *_manager, size_t _taskPeriod, int (*TaskFunction)(void *context), void *context)
{
	Task* newTask= NULL;
	ADTStatus status;
	if(NULL == _manager)
	{
		return UNINITIALIZED_ERROR;
	}
	if (_taskPeriod ==0 || (*TaskFunction)==NULL)
	{
		return ENVALID_FUNCTION_PARAMETER;
	}
	
	return SchedulerAppendNewTask(_manager->m_scheduler, _taskPeriod ,(*TaskFunction),context);
}
/******************************************************************************/
ADTStatus ManagerExecuteTasks(Manager* _manager)
{
	if (NULL == _manager)
	{
		return UNINITIALIZED_ERROR;
	}
	return SchedulerStartExecution(_manager->m_scheduler);
}

/******************************************************************************/
ADTStatus ManagerPauseExecution(Manager* _manager)
{
	if (NULL == _manager)
	{
		return UNINITIALIZED_ERROR;
	}
	return SchedulerPauseExecution(_manager->m_scheduler);
}
/******************************************************************************/


