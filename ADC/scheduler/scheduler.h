#ifndef __SCHEDULER_H_
#define __SCHEDULER_H_


/** 
 *  @file scheduler.h
 *  @brief Creating and Implemnting scheduler task executer.
 * 
 *  @details Implemented task timing and execution machine. the scheduler API
 *  allows these functionality:
 *	1)Adding a task to the executor specifying its period	   
 * 	2)Run the executor - this call will start the periodic execution of the 
 *	tasks.
 *	3)Pause the execution. 
 *  @author Author Adham (faresadham@gmail.com) 
 * 
 *  @bug No known bugs.
 */ 




#include "ADTDefs.h"
#include <stddef.h>

typedef struct Scheduler Scheduler;

/**  
 * @brief Creating pointer for tasks scheduler and executer. 
 * @param[in]  Void
 * @return scheduler pointer - On success / NULL on fail 
 */
Scheduler* SchedulerCreate(void);
/**  
 * @brief Destroying periodic task executer and scheduler completely and setting 
 * user pointer to NULL. 
 * @param[in] user scheduler pointer address.
 * @return Void
 */
void SchedulerDestroy(Scheduler** _scheduler);

/**  
 * @brief adding new task for scheduler. user can add anew task by calling this 
 * function and paasing pointer to Created task.
 * @param[in] pointer to manager, period time and function pointer.
 * @return ADT status
 * @retval SUCCESS on success
 * @retval UNINITIALIZED_ERROR if the manager is not initialized
 * @retval ENVALID_FUNCTION_PARAMETER if NULL function pointer was passed or 
 * task period=0
 */
/*ADTStatus SchedulerAppendNewTask(Scheduler* _scheduler, void* _newTask);*/
ADTStatus SchedulerAppendNewTask(Scheduler* _scheduler, size_t _taskPeriod ,
int (*TaskFunction)(void *context), void *context);

/**  
 * @brief Starting Execution process.
 * @param[in] pointer to scheduler 
 * @return ADT status
 * @retval SUCCESS on success
 * @retval UNINITIALIZED_ERROR if the manager is not initialized
 * @retval  
 * task period=0
 */
ADTStatus SchedulerStartExecution(Scheduler* _scheduler);


size_t SchedulerSize(Scheduler* _scheduler);


/**  
 * @brief Pausing Execution process.
 * @param[in] pointer to scheduler 
 * @return ADT status
 * @retval SUCCESS on success
 * @retval UNINITIALIZED_ERROR if the manager is not initialized
 * @retval  
 * task period=0
 */
ADTStatus SchedulerPauseExecution(Scheduler* _scheduler);




#endif	/*__SCHEDULER_H_*/
