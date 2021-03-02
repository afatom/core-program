#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cdr.h"
#include "channel.h"
#include <assert.h>
	
#define TRUE 1
#define DEBUG

struct Parser{
	char*  m_relativeFilePath; 
	size_t m_maxLineLength;
	Channel* m_channel;
	};

	
/*******************************************************************************/
Parser* ParserCreate(char* _relativeFilePath, size_t _maxLineLength, Channel* _channel)
{
	Parser* par = NULL;
	
	if(!_maxLineLength)
	{
		return NULL;
	}
	
	par = (Parser*)malloc(sizeof(Parser));
	if(!par)
	{
		return NULL;
	}
	 
	par->m_relativeFilePath = _relativeFilePath;
	par->m_maxLineLength = _maxLineLength;
	par->m_channel = _channel;
	return par;
}
/*******************************************************************************/
void ParserDestroy(Parser** _pParser)
{
	if( NULL == _pParser || NULL == *_pParser )
	{
		return;
	}
	
	free(*_pParser);
	*_pParser = NULL;
	return;
}

/*******************************************************************************/
/**int glob = 100;*/
Parser_Status ParseAndSend(Parser* _parser)
{
	FILE* fp;
	char* bufbegin;
	char *pos;
	char* _buffer;
	Cdr* mcdr;

	_buffer = (char*)malloc(_parser->m_maxLineLength);
	if(!_buffer)
	{
		return PARSER_ALLOCATION_ERROR;
	}
	
	fp = fopen(_parser->m_relativeFilePath,"r");
	if(!fp)
	{
		#ifdef DEBUG
		puts("Error fopen");
		#endif
		
		return PARSER_ERROR_WHILE_OPENING_CDR_FILE;
	}

	while (TRUE)
	{
		bufbegin = fgets(_buffer,(int)_parser->m_maxLineLength,fp);
		if (feof(fp))
		{
			break;
		}
		
		pos=strchr(_buffer, '\n'); /** remove /n from the string*/
		*pos = '\0';
		mcdr = CDR_Create(_buffer);
		
		
		assert(ChannelTransmit(_parser->m_channel, 
		mcdr, CdrGetSize()) == CHANNEL_SUCCESS);
		/**--glob;*/
		
		puts("This Is Send Msg");
		
		CdrPrint(mcdr);sleep(1);
		/**
		if (glob == 0)
		{
		glob=100;	
		sleep(5);
		}**/
		CDR_Destroy(&mcdr);
		
	}
	free(_buffer);
	fclose(fp);
	return PARSER_SUCCESS;
}
/*******************************************************************************/
