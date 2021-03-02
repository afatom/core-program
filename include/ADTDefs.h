#ifndef __ADTDEFS_H_
#define __ADTDEFS_H_

/** 
 *  @file ADTDefs.h
 *  @brief This file includes all ADT possible Errors and returns.
 *	@all functions and data types retvals will be one of those errors/status
 *	@bellow.
 *  @author adhamfares Email: faresadham@gmail.com
 * 
 *  @bug No known bugs! 
 */
 
typedef enum ADTStatus
{
	SUCCESS = 0x0,
	UNINITIALIZED_ERROR,
	ALLOCATION_ERROR,
	NULL_ELEMENT_ERROR,
	UNDERFLOW_ERROR,
	OVERFLOW_ERROR,
	ENVALID_FUNCTION_PARAMETER,
	INDEX_OUT_OF_BOUNDS_ERROR,
	KEY_NULL_ERROR, 			/**< Key was null 				*/
	KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 		*/
	KEY_NOT_FOUND_ERROR,
	EMPTY_BUFFER_ERROR 
}ADTStatus;

	
	
#endif /*__ADTDEFS_H_*/
