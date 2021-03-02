#ifndef __BARRIER_H_
#define __BARRIER_H_

/** 
 *  @file barrier.h
 *  @brief Create implements the "barrier" synchronization ADT.
 * 
 *  @details Implemented A barrier wich causes threads to wait until 
 *  a set of threads has
 *  all "reached" the barrier. The number of threads required is
 *  set when the barrier is initialized, and cannot be changed
 *  except by reinitializing, on other words synchronize threads at a 
 *  specified barrier. The calling thread blocks until the required 
 *  number of threads have called BarrierWait() specifying the 
 *  barrier.
 * 
 *  @author Author Adham faris (faresadham@gmail.com) 
 * 
 *  @bug No known bugs.
 */ 


#include <stddef.h>


typedef struct Barrier Barrier;

typedef enum Barrier_Result{
	BARRIER_SUCCESS,
	BARRIER_NOT_INITIALIZED,
	BARRIER_ALLOCATION_FAIL,
	BARRIER_INTERNAL_ERROR,
	BARRIER_INVALID_ARGS
	}Barrier_Result;
	
 	
/** 
 * @brief Barrier creating and intializing.
 * @params[in]: _count, apositive size wich will cause the first _count 
 * threads to wait on barrier.
 * @returns a pointer to the created barrier.
 * @retval NULL on failure due to allocation failure or size 0.
 */
Barrier* BarrierCreate(const size_t _count);


/** 
 * @brief Destroy the previous barrier and set its pointer to NULL
 * @params[in]: address of the allocated barrier pointer.
 * @returns void
 * @retval NULL .
 */
void BarrierDestroy(Barrier** _barrier);



/** 
 * @brief The BarrierWait() function allows a thread to wait for a
 * barrier to be completed.
 * @params[in]: previous allocated barrier pointer.
 * @returns Barrier_Result status
 * @retval BARRIER_SUCCESS on success.
 * BARRIER_NOT_INITIALIZED on adamaged barrier pointer or NULL pointer
 */
Barrier_Result BarrierWait(Barrier* _barrier);


#endif /*__BARRIER_H_*/
