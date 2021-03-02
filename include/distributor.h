#ifndef __DISTRIBUTOR_H_
#define __DISTRIBUTOR_H_



typedef enum Distributor_Status{
	DISTRIBUTOR_SUCCESS = 0,
	DISTRIBUTOR_NOT_INITIALIZED_ERROR,
	DISTRIBUTOR_NULL_DATA_INPUT,
	DISTRIBUTOR_RECEIVED_ERROR_WHILE_DATA_PASSING,
	DISTRIBUTOR_THREAD_SAFETY_ERROR

}Distributor_Status;


/** 
 *  @file distributor.h
 *  @brief Creating and Implementing distributor module.  
 *	
 *  @details  distributor amodule is a MT safe module wich receives 
 *  amsg/cdr from various num of threads. 
 *  distributor passes/shift received message/cdr to aggregators modules. 
 *  Data Manager/caller is responsible for supplying aggregators array.    
 *	This module is Multi-Threaded safe! 
 *  @author 
 * 
 *  @bug No known bugs! 
 */
 
typedef struct Distributor Distributor;

#include <stddef.h>
#include "aggregator.h"
/** 
 * @brief Creating and implementing Distributor pointer.   
 * @param[in] 	_aggregatorsNum  	- number of aggregators to communicate with.
 * @param[in]  	_aggregatorsArray 	- previously Created aggregators array.					   
 * @return     	Distributor pointer on success or NULL on fail.      
 */
 Distributor* DistributorCreate(Aggregator** _aggregatorsArray, size_t _aggregatorsNum);

void DistributorDestroy(Distributor** _distributor, Aggregator*** _retvalAggregatorsArray);





Distributor_Status DistributorInsert(Distributor* _distributor, void* _data);







#endif /** __DISTRIBUTOR_H_*/
