#ifndef __TASK_H_
#define __TASK_H_


/** 
 *  @file task.h
 *  @brief Creating and Implemnting task Creator and Destroyer.
 * 
 *  @details Implemented task module. the task API
 *  allows these functionality:
 *	1)creating new task	   
 * 	2)Dstroying existing task.
 *	3)Update task next excution time. 
 *  @author Author Adham (faresadham@gmail.com) 
 * 
 *  @bug No known bugs.
 */ 



#include <stddef.h>



typedef struct Task Task;


typedef int (*TaskFunction)(void* context);
typedef void (*TaskTerminator)(void* _task);


Task* TaskCreate(size_t _period,TaskFunction _userFunction, void* _context);


void TaskDestroy(void* _task);


void TaskUpdateDueTime(Task* _task, size_t _newDueTime);

size_t TaskGetDueTime(Task* _task);

size_t TaskGetPeriodTime(Task* _task);

TaskTerminator GetTaskTerminatorPointer(void);



int TaskExecution(Task* _task);

/*
int DueTimeCompare(const Task *_firstTask, const Task *_secondTask);
*/

#endif /*__TASK_H_*/ 
