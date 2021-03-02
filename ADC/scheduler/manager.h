#ifndef __MANAGER_H_
#define __MANAGER_H_


/** 
 *  @file manager.h
 *  @brief Create a single thread periodic task executer application.
 * 
 *  @details Implemented single thread periodic task executer application.create 
 * 	a facility 
 * 	that can execute periodic recurrent tasks. This facility behaves like a 
 * 	single threaded scheduler for running repeating tasks
 * 
 *  @author Author Adham (faresadham@gmail.com) 
 * 
 *  @bug No known bugs.
 */ 




#include "ADTDefs.h"
#include <stddef.h> /*size_t*/

typedef struct Manager Manager;
typedef int (*function)(void* context);

/**  
 * @brief single thread periodic task executer application.create a facility 
 * that can execute periodic recurrent tasks. This facility behaves like a 
 * single threaded scheduler for running repeating tasks
 * @param[in] void 
 * @return manager* - On success / NULL on fail 
 */
Manager* ManagerCreate(void);

/**  
 * @brief Destroying periodic task executer completely and setting user pointer
 * to NULL. 
 * @param[in] user manager pointer address.
 * @return Void
 */
void ManagerDestroy(Manager** _manager);

/**  
 * @brief adding new task for scheduler. user can add anew task by calling this 
 * function and paasing pointer to his function and period time for execution.
 * @param[in] pointer to manager, period time and function pointer.
 * @return ADT status
 * @retval SUCCESS on success
 * @retval UNINITIALIZED_ERROR if the manager is not initialized
 * @retval ENVALID_FUNCTION_PARAMETER if NULL function pointer was passed or 
 * task period=0
 */
ADTStatus ManagerAppendTask(Manager* _manager, size_t _taskPeriod ,
int (*TaskFunction)(void* context), void* context);

/**  
 * @brief executing user tasks periodicly in respect to period time for each
 * task. 
 * @param[in] pointer to manager.
 * @return ADT status
 * @retval SUCCESS on success
 * @retval UNINITIALIZED_ERROR if the manager is not initialized
 */
ADTStatus ManagerExecuteTasks(Manager* _manager);

/**  
 * @brief pausing executing process. the facility will holds until next command 
 * arrival  
 * @param[in] pointer to manager.
 * @return ADT status
 * @retval SUCCESS on success
 * @retval UNINITIALIZED_ERROR if the manager is not initialized
 */
ADTStatus ManagerPauseExecution(Manager* _manager);
/**  
 * @brief returning tasks number wich have been added by user.  
 * @param[in] pointer to manager.
 * @return ADT status
 * @retval 0 retval in two cases, NULL manager pointer or zero tasks number.
 * @retval number of tasks.
 */
size_t ManagerTasksNum(Manager* _manager);



#endif /*__MANAGER_H_*/
