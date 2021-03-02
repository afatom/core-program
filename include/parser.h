#ifndef __PARSER_H_
#define __PARSER_H_

#include "channel.h"
/** 
 *  @file parser.h
 *  @brief Creating and Implementing Parser module.  
 *	
 *  @details  Parser is amodule wich can handle array of pointers to files and 
 *  can handle several parsers at time.  
 *	user/caller can controll amount of open txt files by files num. 
 *  @author 
 * 
 *  @bug No known bugs! 
 */


typedef enum Parser_Status {
	PARSER_SUCCESS =0,
	PARSER_SEND_OPERATION_FAILED,
	PARSER_ERROR_WHILE_OPENING_CDR_FILE,
	PARSER_ALLOCATION_ERROR

}Parser_Status;



typedef struct Parser Parser;

#include <stddef.h>

/** 
 * @brief Create and implement parser module.   
 * @param[in]	_files[] - array of files names (files names should include 
 * relative paths to parser.c).
 * @param[in]  _filesNum - array size - number of files to be open
 * @param[in]  _maxLineLength - max chars to be read in single line.						   
 * @return     parser pointer      
 */
Parser* ParserCreate(char* _relativeFilePath, size_t _maxLineLength, Channel* _channel);
/** 
 * @brief Destroy previous created parser pointer and set its value to NULL   
 * @param[in]	_pParser - address of parser pointer 						   
 * @return    void    
 */
void ParserDestroy(Parser** _pParser);


/** 
 * @brief parse line in loop operation, till end of file. 
 * and set parseed data as string to buffer allocated in parser module.
 * @param[in]	_parser - parser pointer 
 * @param[in]	_fileIndex - file index (in the above array) 						   
 * @return    pointer to parssed data string/buffer     
 */
Parser_Status ParseAndSend(Parser* _parser);



void StopParsing(Parser* _parser);


#endif /*__PARSER_H_*/
