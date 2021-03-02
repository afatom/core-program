
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "channel.h"
#include <pthread.h>
#include "com.h"
#include <unistd.h>
#include <stdio.h>

#define CHAN_BUFF_SIZE 4096

int main (int argc, char* argv[])
{
	Channel* up=NULL;
	Channel* down=NULL;
	CCMD inCommand;
	ControlMsg inMsg;
	ControlMsg UpMsg;
	
	
	UpMsg.m_command = CCMD_PING;
	
	assert((up = ChannelCreate("CTRL_CHAN1_UP", CHAN_BUFF_SIZE, CHANNEL_CREATE))!=NULL);
	if(up == NULL)
	{
		return 1;
	}
	
	assert((down = ChannelCreate("CTRL_CHAN1_DN", CHAN_BUFF_SIZE, CHANNEL_CREATE))!=NULL);
	if(down == NULL)
	{
		ChannelDestroy(&(up));
		return 1;
	}
	
	while(1)
	{
		ChannelReceive(down, &inMsg, sizeof(ControlMsg));
		if(inMsg.m_command == CCMD_PING)
		{
			puts("CCMD_PING   Received :From: ReaderManager");
		}
		
		ChannelTransmit(up, &UpMsg, sizeof(ControlMsg));
		sleep(1);
	}
	
	
	
	return 0;
}
