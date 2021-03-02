#include <stdio.h>
#include <stdlib.h>
#include "manager.h"
#include "scheduler.h"
#include "task.h"
#include "ttime.h"
#include "mu_test.h"

#define DELAY_TIME 5 /* seconds */

#define PERIOD_1 4
#define PERIOD_2 3
#define PERIOD_3 7
#define PERIOD_4 10
#define PAUSE_PERIOD 0

static size_t run_times1 = 3;
static size_t run_times2 = 5;
static size_t run_times3 = 8;
static size_t run_times4 = 6;

/*static size_t newRun_times = 3;*/

static size_t pauseTime = DELAY_TIME;
static Manager *manager;
/*
static int NewPrintFunc()
{
    char *str = "Hi, I am a NewPrintFunc !";
    printf("%s\n", str);
    return (!--newRun_times) ? 0 : 1;
}*/
/*
static int Restart()
{
 
    ManagerExecuteTasks(manager);

    return 0;
}*/
/*
static int PauseFunc(void *_contex)
{
    char *str = "Pause";

    if (*((size_t *)_contex) <= GetCurTime())
    {
        printf("%s\n", str);

        ManagerPauseExecution(manager);

        ManagerAppendTask(manager, PERIOD_1, NewPrintFunc, NULL);

        Restart();

        return 0; 
    }

    return 1;
}
*/
static int Print1()
{
    char *str = "Hi, I am a Number 1 !";
    printf("%s\n", str);
 

    return (!--run_times1) ? 0 : 1;
}

static int Print2()
{
    char *str = "Hi, I am a Number 2 !";
    printf("%s\n", str);

    return (!--run_times2) ? 0 : 1;
}

static int Print3()
{
    char *str = "Hi, I am a Number 3 !";
    printf("%s\n", str);
 

    return (!--run_times3) ? 0 : 1;
}

static int Print4()
{
    char *str = "Hi, I am a Number 4 !";
    printf("%s\n", str);
  

    return (!--run_times4) ? 0 : 1;
}


UNIT(Test_create_manager)

pauseTime += GetCurTime();

ASSERT_THAT((manager = ManagerCreate()) != NULL);

ASSERT_THAT(ManagerAppendTask(manager, PERIOD_1, Print1, NULL) == SUCCESS);
/*
ASSERT_THAT(ManagerAppendTask(manager, PERIOD_2, Print2, NULL) == SUCCESS);
ASSERT_THAT(ManagerAppendTask(manager, PERIOD_3, Print3, NULL) == SUCCESS);
ASSERT_THAT(ManagerAppendTask(manager, PERIOD_4, Print4, NULL) == SUCCESS);*/
/*ASSERT_THAT(AddTask(manager, PauseFunc, (void *)&(pauseTime), PAUSE_PERIOD) == ERR_OK);*/

ManagerExecuteTasks(manager);

ManagerDestroy(&manager);
END_UNIT



TEST_SUITE(Manager test)

TEST(Test_create_manager)

END_SUITE
