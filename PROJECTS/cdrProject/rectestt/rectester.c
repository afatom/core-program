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

int main (void)
{
	Channel* _channel = NULL;
	Cdr* pMsg;
	size_t i;
 
	pMsg = CDR_Create_Empty_Cdr();
	
	_channel = ChannelCreate("MS880Q987" ,CHANNEL_BUFFER_SIZE ,CHANNEL_CREATE);
	assert(_channel!=NULL);
	while((ChannelReceive(_channel, pMsg, CdrGetSize()) == CHANNEL_SUCCESS))
	{
		puts("*");
		assert(pMsg!=NULL);
		CdrPrint(pMsg);
	}
	
	
	return 0;
	
}
