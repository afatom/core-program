#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cdr.h"
#include "channel.h"
#include <assert.h>

#define CHANNEL_BUFFER_SIZE 4096

int main(int argc, char* argv[])
{
	size_t _maxLineLength =0;
	Parser* ptr = NULL;
	Channel* _channel = NULL;
	
	_maxLineLength = (size_t)(atoi(argv[2]));
	
	
	_channel = ChannelCreate(argv[3],CHANNEL_BUFFER_SIZE ,CHANNEL_CREATE);
	assert(_channel!=NULL);
	ptr = ParserCreate(argv[1], _maxLineLength, _channel);
	assert(ptr!=NULL);
	
	ParseAndSend(ptr);
	ParserDestroy(&ptr);
	return 0;
}
