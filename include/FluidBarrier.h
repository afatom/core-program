#ifndef __FLUIDBARRIER_H_
#define __FLUIDBARRIER_H_

/** 
 *  @file barrier.h
 *  @brief Create and implements the "fluid barrier" synchronization ADT.
 * 
 *  @details Implemented A fluid barrier wich causes N threads to wait 
 *  until a set of threads has "reached" the barrier and then realeasing,
 *  K threads. K is unsigned num wich is smaaler or equal to N (K<=N)!  
 *  The number of threads (N,K)required is
 *  set when the barrier is initialized, and cannot be changed
 *  except by reinitializing, on other words synchronize threads at a 
 *  specified barrier. The calling thread blocks until the required 
 *  number of threads have called BarrierWait() specifying the 
 *  barrier.
 * 
 *  @author Author Adham faris (faresadham@gmail.com) 
 * 
 *  @bug No known bugs.
 *  @warning_1 		if k>N NULL barrier pointer will be returned.
 *  @warning_2 		For reasons of efficiency and performance, barrier pointer, 
 * 					will be not tested in each API call, Therefore, the user 
 * 					is responsible for calling with valid barrier pointer.
 */ 


#include <stddef.h>


typedef struct Barrier Barrier;

typedef enum Barrier_Result{
	BARRIER_SUCCESS,
	BARRIER_NOT_INITIALIZED_ERROR,
	BARRIER_ALLOCATION_FAIL_ERROR,
	BARRIER_INTERNAL_ERROR,
	BARRIER_INVALID_ARGS_ERROR
	}Barrier_Result;
	
 	
/** 
 * @brief Barrier creating and intializing.
 * @params[in] _n, apositive size wich will cause the first _n 
 * threads to wait on barrier.
 * @params[in] _k, apositive size (k<=n) wich will cause k threads to keep
 * and wait on barrier num 2 (with param k). 
 * @returns a pointer to the created barrier.
 * @retval NULL on failure due to allocation failure,or _k=0 or _n=0 or
 * _k>n
 */
Barrier* BarrierCreate(const size_t _threadsNumAtFirstBarrier, const size_t _threadsNumAtSecBarrier);


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


#endif /*__FLUIDBARRIER_H_*/
