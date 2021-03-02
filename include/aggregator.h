#ifndef __AGGREGATOR_H_
#define __AGGREGATOR_H_

#include "cdr.h"

/** 
 *  @file aggregator.h
 *  @brief Creating and Implementing MT generic aggregator module.
 *	
 *  @details  The Generic MT aggregator ADT is adata and message proccessor
 * unit wich receives data (in generic form) by communicating with multi thread
 * facility. this data contains, details about subscribers and cellular operators. 
 * for example message includes call time, sms and data that was consumed by subscriber
 * in one event.
 * data about operators and subscribers will be saved in defferent DS's(Data Stores)
 * this data will allow billing domain facility for special calculations in the future.    
 *
 *  @author 
 * 
 *  @bug No known bugs! 
 */

typedef enum Aggregator_Result{
	AGGREGATOR_SUCCESS = 0,
	AGGREGATOR_UNINITIALIZED_ERROR=1,
	AGGREGATOR_ALLOCATION_ERROR=2,
	AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR=3,
	AGGREGATOR_SUBSCRIBER_OR_OPERATOR_NOT_FOUND_ERROR=4
	
}Aggregator_Result;

/*
typedef size_t (*HashFunction)(const void* _key);
typedef int (*EqualityFunction)(const void* _firstKey, const void* _secondKey);
typedef int	(*KeyValueActionFunction)(const void* _key, void* _value, void* _context);
*/


#include <stddef.h> /*size_t*/
typedef struct Aggregator Aggregator;

/*typedef int (*EqualityFunction)(const void* _firstKey, const void* _secondKey);*/

/** 
 * @brief Create a new Aggregator with an estimated max providers and 
 * subscribers number.
 * @param[in] _subscribersNum - Expected max _subscribers number.
 * 			  _providersNum -  Expected max _providers number.
 * 						   
 * @return on success, Aggregator pointer or NULL on failure
 */
 
Aggregator* AggregatorCreate(const size_t _subscribersNum, const size_t _operatorsNum,
 size_t (*OperatorsHashFunction)(const void* _key), size_t (*SubscribersHashFunction)(const void* _key));


Aggregator* AggregatorNewCreate(const size_t _initialSubscribersNum, const size_t _newCapacityInGrowthCondition);


/** 
 * @brief Destroy previous allocated Aggregator and set the pointer to NULL also,
 * in destroy operation, all aggregated data for operators and for subscribers 
 * will be saved in txt files in aceratain full path. caller responsibilty
 * for calling with correct path.  
 * @param[in] 	_pAggregator - address of previous allocated aggregator pointer
 * 				_subscribersReportFilePath - full path to directory for saving DS subscribers reports
 * 				_operatorsReportFilePath - full path to directory for saving DS operators reports
 * 						   
 * @return Aggregator_Result: 	AGGREGATOR_SUCCESS - on success
 * 							 	AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR - on incorrect paths name
 */
Aggregator_Result AggregatorDestroy(Aggregator** _pAggregator, const char* _subscribersReportFilePath, const char* _operatorsReportFilePath);

/** 
 * @brief Inserting one cdr message in each call. cdr is ageneric predetermined message  
 * @param[in] 	_pAggregator - previous allocated aggregator pointer
 * 				_msg - pointer/address of incomming msg
 * 						   
 * @return Aggregator_Result: 	AGGREGATOR_SUCCESS - on success
 * 							 	AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR - NULL msg pointer
 * 								AGGREGATOR_UNINITIALIZED_ERROR - NULL Aggregator pointer
 */
Aggregator_Result AggregatorInsertCdr(Aggregator* _pAggregator, void* _cdr);

size_t Agg_Get_Size(Aggregator* _pAggregator);
/** 
 * @brief Get subscriber data/query. data will be written to buffer wich caller
 * must provide at call.   
 * @param[in] 	_pAggregator - previous allocated aggregator pointer
 * 				_subscriberMSISDN - subscriber unique key num
 * 				_pQueryRet - pointer to empty buffer for retval
 * 						   
 * @return Aggregator_Result: 	AGGREGATOR_SUCCESS - on success
 * 							 	AGGREGATOR_SUBSCRIBER_NOT_FOUND_ERROR - invalid MSISDN number 
 * 								AGGREGATOR_UNINITIALIZED_ERROR - NULL Aggregator pointer
 * 
 * @warning: caller responsibility for calling with enough space for retval (x bytes).
 */
Aggregator_Result GetSubscriberQuery(Aggregator* _pAggregator, const char* _subscriberMSISDN, char* _pQueryRet);

Aggregator_Result AggGetSubscriberQuery(Aggregator* _pAggregator, size_t _subscriberImsi, char* _pQueryRet);

/*Aggregator_Result AggGetSubscriberQuery(Aggregator* _pAggregator, size_t _subscriberImsi, void** _pQueryRet);*/
/** 
 * @brief Get operator data/query. data will be written to buffer wich caller
 * must provide at call.   
 * @param[in] 	_pAggregator - previous allocated aggregator pointer
 * 				_operatorIMSI - operator unique key num
 * 				_pQueryRet - pointer to empty buffer for retval
 * 						   
 * @return Aggregator_Result: 	AGGREGATOR_SUCCESS - on success
 * 							 	AGGREGATOR_OPERATOR_NOT_FOUND_ERROR - invalid IMSI number 
 * 								AGGREGATOR_UNINITIALIZED_ERROR - NULL Aggregator pointer
 * 
 * @warning: caller responsibility for calling with enough space for retval (x bytes).
 */

Aggregator_Result GetOperatorQuery(Aggregator* _pAggregator, const char* _operatorIMSI, char* _pQueryRet);
/** 
 * @brief Get operator data report. data will be written to txt file in agiven file path (_operatorsReportFilePath)
 * @param[in] 	_pAggregator - previous allocated aggregator pointer
 * 				_operatorsReportFilePath - full path to destination dir
 * 				
 * 						   
 * @return Aggregator_Result: 	AGGREGATOR_SUCCESS - on success
 * 							 	AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR - invalid path name 
 * 								AGGREGATOR_UNINITIALIZED_ERROR - NULL Aggregator pointer
 * 
 */
Aggregator_Result GetOperatorsReport(Aggregator* _pAggregator, const char* _operatorsReportFilePath);

/** 
 * @brief Get subscriber data report. data will be written to txt file in agiven file path (_subscribersReportFilePath)
 * @param[in] 	_pAggregator - previous allocated aggregator pointer
 * 				_subscribersReportFilePath - full path to destination dir
 * 				
 * 						   
 * @return Aggregator_Result: 	AGGREGATOR_SUCCESS - on success
 * 							 	AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR - invalid path name 
 * 								AGGREGATOR_UNINITIALIZED_ERROR - NULL Aggregator pointer
 * 
 */
Aggregator_Result GetSubscribersReport(Aggregator* _pAggregator, const char* _subscribersReportFilePath);


 
/*UNIT test function*/
void SubscribersDSPrint(Aggregator* _pAggregator);
void OperatorsDSPrint(Aggregator* _pAggregator);




#endif/*__AGGREGATOR_H_*/

