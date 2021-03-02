#include "scheduler.h"
#include "heap.h"
#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include "ADTDefs.h"
#include "ttime.h"
#include "task.h"
#include <stdio.h>
#include <unistd.h>

#define SCHEDULER_VALID 0xBEEFBEEF
#define SCHEDULER_DESTROYED 0xDEADBEEF
#define BLOCK_SIZE 15
#define INIT_SIZE 20
#define NDEBUG
#define TRUE 1
#define FALSE 0
#define OFF 0
#define ON 1

#define TERMINATE 0
#define RE_SCHEDULE 1




static int PAUSE_DISCRETE = OFF;

typedef Heap PriorityQ;


/******************************************************************************/
struct Scheduler{
	PriorityQ* 	m_PriorityQ;
};
/******************************************************************************/
PriorityQ* PriorityQCreate(void);
static void PriorityQDestroy(PriorityQ** _priQ);
size_t GetPriorityQSize(PriorityQ* _pq);
/******************************************************************************/
Scheduler* SchedulerCreate(void)
{
	Scheduler* _stpte = NULL;
	_stpte = (Scheduler*)malloc(sizeof(Scheduler));
	if(NULL == _stpte)
	{
		return NULL;
	}
	if (!(_stpte->m_PriorityQ = PriorityQCreate()))
	{
		free(_stpte);
		return NULL;
	}
	return _stpte;	
}
/******************************************************************************/
PriorityQ* PriorityQCreate(void)
{
	Vector* vec = NULL;
	PriorityQ* pq = NULL;
	/*create vector*/
	vec = VectorCreate(INIT_SIZE , BLOCK_SIZE);
	if(NULL == vec)
	{
		return NULL;
	}

	assert(vec != NULL);
	/*create heap*/
	pq = HeapBuild(vec, GetDueTimeCompareFunction());
	assert(pq != NULL);

	if(NULL == pq)
	{
		free(vec);
		return NULL;
	}
	return pq;
}
/******************************************************************************/
void SchedulerDestroy(Scheduler** _scheduler)
{

	if(NULL == _scheduler || NULL == *_scheduler )
	{
		return;
	}
	
	PriorityQDestroy(&(*_scheduler)->m_PriorityQ);
	free(*_scheduler);
	*_scheduler=NULL;
	return;
}
/******************************************************************************/
static void PriorityQDestroy(PriorityQ** _priQ)
{
	Vector* vec = NULL;
	
	vec = HeapDestroy(_priQ);
	
	VectorDestroy(&vec, GetTaskTerminatorPointer());

	/*
	while(VectorSize((*_stpte)->m_vector))
	{
		VectorRemove((*_stpte)->m_vector, &removed);
		rmtask = (Task*)removed;
		TaskDestroy(&rmtask);
	}
	VectorDestroy(&(*_stpte)->m_vector,NULL);*/
	return;
}
/******************************************************************************/



ADTStatus SchedulerAppendNewTask(Scheduler* _scheduler, size_t _taskPeriod,
int (*TaskFunction)(void *context), void *context)
{
	Task* task = NULL;

	/*if its the first task - set initial time*/
	/*
	if(!HeapSize(_scheduler->m_heap))
	{
		_scheduler->m_initialTime = TimeGetCurTime(); 
	}
	*/
	/*call task module*/
	/*the period time is normalized and referenced to initial time*/
	/*
	task = TaskCreate(_taskPeriod + TimeGetCurTime() - _scheduler->m_initialTime ,(*TaskFunction), context);
	if(task == NULL)
	{
		return ALLOCATION_ERROR; 
	}*/

	/*update due time*/
	/*
	TaskUpdateDueTime(task, _scheduler->m_initialTime);

	if(HeapInsert(_scheduler->m_heap, task) != HEAP_SUCCESS)
	{
		return ALLOCATION_ERROR;
	}
	*/
	
	task = TaskCreate(_taskPeriod,(*TaskFunction), context);
	if(task == NULL)
	{
		return ALLOCATION_ERROR; 
	}
	
	if(HeapInsert(_scheduler->m_PriorityQ, task) != HEAP_SUCCESS)
	{
		TaskDestroy(task);
		return ALLOCATION_ERROR;
	}
	
	return SUCCESS;
		
}
/******************************************************************************/
size_t GetPriorityQSize(PriorityQ* _pq)
{
	return HeapSize(_pq);
}

/******************************************************************************/
/*<< UNIT test only*/
size_t SchedulerSize(Scheduler* _scheduler)
{
	return GetPriorityQSize(_scheduler->m_PriorityQ);
}
/******************************************************************************/



ADTStatus SchedulerStartExecution(Scheduler* _scheduler)
{
	void* temp = NULL;
	size_t taskDueTime;
	size_t initTime=0; 

	TimeSetInitialRefTime();
	initTime = TimeGetInitialRefTime();

	#ifdef NDEBUG
	printf("init time::%lu cur time::%lu\n", initTime,TimeGetCurTime());
	sleep(5);
	#endif

/**Test**/
	#ifdef NDEBUG
	printf("sched->HeapSize::%lu\n",HeapSize(_scheduler->m_PriorityQ));
	#endif

	while (!PAUSE_DISCRETE &&  (temp = HeapExtract(_scheduler->m_PriorityQ)))
	{
		#ifdef NDEBUG
		printf("197\n");
		#endif
		taskDueTime = TaskGetDueTime((Task *)temp);
		/*TaskUpdateDueTime((Task *)temp, initTime + taskDueTime);*/
		TimeUpdateDueTime(((Task *)temp), TimeGetPeriodTime((Task *)temp));
		taskDueTime = TaskGetDueTime((Task*)temp);
	
		/*Do i need to sleep?*/
		if(taskDueTime - TimeGetCurTime() > 0)
		{
			TimeWait(taskDueTime - TimeGetCurTime()); /*wake me after due time sec*/
		}

		if(TaskExecution((Task*)temp) != RE_SCHEDULE) /*  call task.h for execution*/ 
		{
			/*destroy this task*/
			TaskDestroy((Task*)temp);
		}

		else
		{
			/*TimeUpdateDueTime(task, TaskGetPeriodTime(task));*/
			TimeUpdateDueTime((Task *)temp, TaskGetPeriodTime((Task *)temp) + TimeGetCurTime());
			HeapInsert(_scheduler->m_PriorityQ, (Task*)temp); 
			
		}
		

	}
	return SUCCESS;
}
/******************************************************************************/



/*

int __PauseSystemFunction__(void* context)
{
	PAUSE_DISCRETE = ON;
	puts("In  __PauseSystemFunction__ ");
	sleep(5);
	PAUSE_DISCRETE = OFF;
	return RE_SCHEDULE;
}




ADTStatus SchedulerPauseExecution(Scheduler *_scheduler)
{
	PAUSE_DISCRETE = ON;
	SchedulerAppendNewTask(_scheduler, 10,
						   int (*TaskFunction)(void *context), NULL); 
	return SUCCESS;
}
*/
/******************************************************************************/




