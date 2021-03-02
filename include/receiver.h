#ifndef __Receiver_H_
#define __Receiver_H_

#include "cdr.h"
#include "channel.h"
#include "distributor.h"
typedef enum Receiver_Status{
	RECEIVER_SUCCESS = 0,
	RECEIVER_NOT_INITIALIZED_ERROR,
	RECEIVER_ALLOCATION_ERROR,
	RECEIVER_CHANNEL_RECEIVING_DATA_ERROR,
	RECEIVER_THREAD_JOIN_ERROR

}Receiver_Status;


/** 
 *  @file Receiver.h
 *  @brief Creating and Implementing Receiver module.  
 *	
 *  @details  Receiver amodule is a MT module wich receives amsg from channel
 *  and sends the same received message to aggregators modules. this module is 
 *  responsible for creating aggregators modules and hold their pointers.
 *  threads num is configurable within config file.   
 *	 
 *  @author 
 * 
 *  @bug No known bugs! 
 */
 

typedef struct Receiver Receiver;

#include <stddef.h>

/** 
 * @brief Create and implement Receiver module.   
 * @param[in]	_configFile - relative path of config file respect to Receiver.c
 * @param[in]  _aggregatorsNum - num of aggregators to be created
 * @param[in]  _channel - channel pointer for communicating with transmiters.						   
 * @return     Receiver pointer on success or NULL on fail      
 */
/** Receiver* ReceiverCreate(const char* _configFile, size_t _aggregatorsNum) **/
Receiver* ReceiverCreate(const char* _channelName, const size_t _threadsNum, Distributor* _distributor);

/** 
 * @brief Destroy previous created _Receiver pointer and set its value to NULL   
 * @param[in]	_Receiver - address of _Receiver pointer 						   
 * @return    void    
 */
/** void ReceiverDestroy(Receiver** _receiver);*/

Distributor* ReceiverDestroy(Receiver** _receiver);

/** 
 * @brief Activating receiving messages on channel   
 * @param[in]	_Receiver - address of _Receiver pointer 						   
 * @return    Receiver_Status
 * @retval    	RECEIVER_SUCCESS on success
 *				RECEIVER_NOT_INITIALIZED_ERROR - null rec pointer
 *				RECEIVER_ALLOCATION_ERROR - memmory allocation error
 *				RECEIVER_CHANNEL_RECEIVING_DATA_ERROR - error in channel
 */
Receiver_Status ReceiverStart(Receiver* _receiver);



#endif /*__Receiver_H_*/

