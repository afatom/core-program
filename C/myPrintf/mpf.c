#include "mpf.h"
#include <string.h> /*string manpulation functions*/
#include <stdio.h> /*puts func*/
#include <stdarg.h>
#include <stdlib.h>

#define MAX_FORMAT_LENGTH 128
#define MAX_TMP_STR 128

int MyPrintf(const char *_format,...)
{
	size_t length = 0;
	char *str = (char *)malloc(MAX_FORMAT_LENGTH * sizeof(char)); /*this string will store the final answere*/
	if (NULL == str)
	{
		return -1;
	}
	char* tmpStr = (char*)malloc(MAX_TMP_STR * sizeof(char));
	if (NULL == tmpStr)
	{
		free(str);
		return -1;
	}
	char *pos=NULL;
	/*******************************************************************************************/
	/*Copying format str to new str thats for Avoiding Compiler Warning: 
	"initialization discards ‘const’ qualifier from pointer target type [-Wdiscarded-qualifiers]
  	char *uformat=&_format[0];"
	********************************************************************************************/
	//char strt[MAX_FORMAT_LENGTH];
	char *strt = (char *)malloc(MAX_FORMAT_LENGTH * sizeof(char));
	if (NULL == strt)
	{	
		free(tmpStr);
		free(str);
		return -1;
	}
	strcpy(strt,_format);
	char *uformat = &strt[0]; 
	/*check inputs*/
	if (NULL == _format)
	{
		return -1; /*null pointer input*/
	}
	length = strlen(_format);
	if (length == 0)
	{
		return -1;
	}
	if (_format[length - 1] == 't' || _format[length - 1] == '\n')
	{
		length-=1;
	}
	/*Function Code*/
	/********************************************/
	va_list args;
	va_start(args, _format);
	while ((pos = strchr(uformat, '%')) != NULL)
	{
		
		switch(*(pos + 1))
		{
			case 's':
				/*get string*/
				strncat(str, uformat, pos - uformat);
				strcpy(tmpStr ,va_arg(args,char*));
				length += strlen(tmpStr);
				length-=2; /*one for % and one for s*/
				strcat(str,tmpStr);
				uformat = pos + 2;
				break;
			
			case 'd':
				/*get int*/
				strncat(str, uformat, pos - uformat);
				sprintf(tmpStr,"%d",va_arg(args,int));
				length+=strlen(tmpStr);
				length-=2;
				strcat(str,tmpStr);
				uformat = pos + 2;
				break;
			
			case 'f':     
				/*get double*/
				strncat(str, uformat, pos - uformat);
				sprintf(tmpStr, "%f", va_arg(args, double));
				length += strlen(tmpStr);
				length -= 2;
				strcat(str, tmpStr);
				uformat = pos + 2;
				break;

			default:

				strncmp(str, uformat, pos - uformat);
				strcat(str, tmpStr);
				uformat = pos + 1;
				break;
		}
	}
	/*string with no %..*/
	if (pos == NULL && uformat == NULL)
	{
		puts(_format);
		goto END;
	}

	strcat(str,uformat);
	puts(str);
	
	END: va_end(args);
	free(strt);
	free(tmpStr);
	free(str);
	return length;
}

