#include "scheduler.h"
#include "heap.h"
#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include "ADTDefs.h"
#include "mu_test.h"
#include <time.h>
#include <stdio.h>
#include "task.h"
#include "ttime.h"
#include <unistd.h>
#define SIZE 2



#define TASK_1_PERIOD 10
#define TASK_2_PERIOD 1
#define TASK_3_PERIOD 2
#define TASK_4_PERIOD 15

int counter2=6;

int counter1=5;

int counter3=2;

int counter4=5;

/******************************************************************************/
UNIT(ssssrand)
srand((unsigned int)time(NULL));
END_UNIT
/******************************************************************************/
void taskDestroyer(void* _task)
{
	free(_task);
	return;
}

/*
typedef struct TasksBuffer*{
	int* arr[2];
}TasksBuffer;
*/
/*typedef int (*TaskFunction)(void* context);*/


/****************************************************/
int TaskFunc1(void* context)
{

	if(counter1 == 0)
	{
		return 0; /*stop rescheduling*/
	} 
	printf("Hellow I am Task 1!\n");
	--counter1;
	return 1;
}
/******************************************************/

int TaskFunc2(void* context)
{

	if(counter2 == 0)
	{
		return 0; /*stop rescheduling*/
	} 
	printf("Hellow I am Task 2!\n");
	--counter2;

	return 1;
}

/******************************************************/

int TaskFunc3(void* context)
{

	if(counter3 == 0)
	{
		return 0; /*stop rescheduling*/
	} 
	printf("Hellow I am Task 3!\n");
	--counter3;
	return 1;
}

int TaskFunc4(void *context)
{

	if (counter4 == 0)
	{
		return 0; /*stop rescheduling*/
	}
	printf("Hellow I am Task 4!\n");
	--counter4;
	return 1;
}

/******************************************************************************/

UNIT(Scheduler_Create_Test)
	Scheduler* ptr = NULL;
	ptr =  SchedulerCreate();
	ASSERT_THAT(NULL!=ptr);
	SchedulerDestroy(&ptr);
	ASSERT_THAT(NULL==ptr);
END_UNIT

/******************************************************************************/


UNIT(Scheduler_Append_New_Task_Test)
	Scheduler* ptr = NULL;
	ptr =  SchedulerCreate();
	ASSERT_THAT(NULL!=ptr);
	
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_1_PERIOD,TaskFunc1,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_2_PERIOD,TaskFunc2,NULL) == SUCCESS);
	/*SchedulerDestroy(&ptr);
	
	ASSERT_THAT(NULL==ptr);*/
END_UNIT

/******************************************************************************/


/******************************************************************************/



/******************************************************************************/

UNIT(Scheduler_Append_Real_Tasks_Test)
	Scheduler* ptr = NULL;
	ptr =  SchedulerCreate();
	ASSERT_THAT(NULL!=ptr);
	
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_1_PERIOD,TaskFunc1,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_2_PERIOD,TaskFunc2,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_3_PERIOD,TaskFunc3,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_4_PERIOD, TaskFunc4, NULL) == SUCCESS);

	/*
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_2_PERIOD,TaskFunc2,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_1_PERIOD,TaskFunc1,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_2_PERIOD,TaskFunc2,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_1_PERIOD,TaskFunc1,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_2_PERIOD,TaskFunc2,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_1_PERIOD,TaskFunc1,NULL) == SUCCESS);
	ASSERT_THAT(SchedulerAppendNewTask(ptr, TASK_2_PERIOD,TaskFunc2,NULL) == SUCCESS);*/

	ASSERT_THAT (SchedulerSize(ptr) == 4);

	SchedulerStartExecution(ptr);
	
	SchedulerDestroy(&ptr);
	
	ASSERT_THAT(NULL==ptr);
END_UNIT

/******************************************************************************/



TEST_SUITE(Scheduler_Test)
    TEST(ssssrand)
    TEST(Scheduler_Create_Test)
    TEST(Scheduler_Append_New_Task_Test)

    TEST(Scheduler_Append_Real_Tasks_Test)
END_SUITE

