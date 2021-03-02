#ifndef _MPF_H_
#define _MPF_H_


/*******************************************************************************
*[Description]:Prints to stdout argument list sending by user. allowable args
*%d-int, %s-string,%f-double %%- %printing.  
*[Input]:formated allowabel args 
*[return]: On success, the total number of characters written is returned.
*[Errors]:-1 invalid input.
*******************************************************************************/
int MyPrintf(const char *_format,...);


#endif /*_MPF_H_*/
