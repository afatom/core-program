#ifndef __MMALLOC_H_
#define __MMALLOC_H_

#include <stddef.h>



/** 
 * @brief create and implement private malloc function
 * @details  allocating buffer with afixed size wich will be given by 
 * user in create function. buffers are limited with respect to this 
 * fixedsize.  
 * 
 * @Warning: For reasons of efficiency and performance, pool pointer, 
 * will be not tested in each free or malloc call, Therefore, the user 
 * is responsible for pool pointer validity.
 * calling these functions with invalid pool pointer will cause 
 * unpredectable app behavior.
 * 
 * Autor: farisadham   Mailbox: farisadham@gmail.com
 * 
 * last update: 06.04.2018 20:49:28 
 *  
 */


typedef struct Pool Pool;

/** 
 * @brief create a new pool for maymalloc usage.
 *
 * @params[in] 	_buffSize - user buffer capacity/size
 				_numofBufs - tottal buffer num to be allocated
 *
 * @returns in success pool pointer will be returned, NULL in failure.
 */
Pool* MmallocCreate(size_t _buffSize, size_t _numOfBuffs);

/** 
 * @brief allocate a new buffer pointer wich points to fixedsize capacity
 * as mentioned before.
 *
 * @params[in] 	_pool pointer.
 *
 * @returns in success buffer pointer will be returned, NULL in failure.
 */

void* MyMalloc(Pool* _pool);

/** 
 * @brief free aprevious aloocated pointer.
 *
 * @params[in] 	_pool - pointer.
 * 				_pBuffer - buffer pointer to be freed
 *
 * @returns void
 */

void MyFree(Pool* _pool, void* _pBuffer);

/** 
 * @brief Destroy pool pointer and free all memory allocations and set
 * its value to NULL
 *
 * @params[in] 	_pool - adress of pool pointer.
 *
 * @returns void
 */
void MmallocDestroy(Pool** _pool);



/** UNIT test funcs only */
void PrintPool(Pool* _pool);
size_t FreeBufsNum(Pool* _pool);


#endif  /*__MMALLOC_H_*/
