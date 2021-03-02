#include "task.h"
#include <stdlib.h>
#include <assert.h>
#include "ADTDefs.h"
#include "mu_test.h"
#include <time.h>
#include "ttime.h"
#include <stdio.h>
#include <unistd.h>

#define SIZE 50
#define TRUE 1
#define SIZE 50


#define PERIOD1 1
#define PERIOD2 2
#define PERIOD3 3
#define PERIOD4 4


/******************************************************************************/
UNIT(ssssrand)
srand((unsigned int)time(NULL));
END_UNIT
/******************************************************************************/

int UserTaskFunction(void* _element)
{
	printf("%d\n", *((int*)_element));
	return TRUE;
}

/******************************************************************************/
/*Task* TaskCreate(size_t _period,TaskFunction _userFunction, void* _context)
*/
UNIT(Task_Create_Test)
	Task* ptr = NULL;
	ptr =  TaskCreate(1,UserTaskFunction,NULL);
	ASSERT_THAT(NULL!=ptr);
	TaskDestroy(&ptr);
	ASSERT_THAT(NULL==ptr);
END_UNIT
/******************************************************************************/
UNIT(Task_All_API_Test)
	int i;
	size_t t =0;
	Task* task1 = NULL;
	Task* task2 = NULL;
	Task* task3 = NULL;
	Task* task4 = NULL;
	
	int arr[4]={10,20,30,40};



	task1 =  TaskCreate(PERIOD1,UserTaskFunction,&arr[0]);
	task2 =  TaskCreate(PERIOD2,UserTaskFunction,&arr[1]);
	task3 =  TaskCreate(PERIOD3,UserTaskFunction,&arr[2]);
	task4 =  TaskCreate(PERIOD4,UserTaskFunction,&arr[3]);
	
	ASSERT_THAT(NULL!=task1);
	ASSERT_THAT(NULL!=task2);
	ASSERT_THAT(NULL!=task3);
	ASSERT_THAT(NULL!=task4);
	

	ASSERT_THAT(TaskGetPeriodTime(task1) == PERIOD1);
	ASSERT_THAT(TaskGetPeriodTime(task2) == PERIOD2);
	ASSERT_THAT(TaskGetPeriodTime(task3) == PERIOD3);
	ASSERT_THAT(TaskGetPeriodTime(task4) == PERIOD4);
	
	i=0;
	while(i<3)
	{
		ASSERT_THAT( TaskExecution(task1)==TRUE);
		ASSERT_THAT( TaskExecution(task2)==TRUE);
		ASSERT_THAT( TaskExecution(task3)==TRUE);
		ASSERT_THAT( TaskExecution(task4)==TRUE);
		++i;
		t = TimeGetCurTime();
		printf("Time::%lu\n",t);
		sleep(1);
	}

	
	TaskDestroy(&task1);
	TaskDestroy(&task2);
	TaskDestroy(&task3);
	TaskDestroy(&task4);
	

END_UNIT



/******************************************************************************/

TEST_SUITE(Scheduler_Test)
    TEST(ssssrand)
    TEST(Task_Create_Test)
	TEST(Task_All_API_Test)
END_SUITE

