#include "channel.h"

#include <string.h> /*strstr*/
#include <stdlib.h>
#include <stdio.h> /*fopen*/
#include <assert.h>
#include <pthread.h>
#include "com.h"
#include <sys/types.h>
#include <unistd.h>



#define CHAN_SIZE 4096

#define FOUND 1

static void NumToString(size_t _num, char* _str)
{
    sprintf(_str, "%lu", _num);
    return;
}

static int GetStrInConfigFile(const char* configFile, const char* str, char* buffer)
{
	/** char str[64] = "initial sub num"; example **/
	FILE *fp;
	char temp[512];
	char* pos;
	char* npos;
	int retval = 0;

	if((fp = fopen(configFile, "r")) == NULL) {
		return(0);
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			
			npos=strchr(temp, '\n'); /** remove /n from the string*/
			*npos = '\0';
		
			pos = temp;
			pos = pos + 1 + strlen(str);
			sscanf(pos,"%s",buffer);
			retval =1;
			break;
		}
	}

	if(fp) 
	{
		fclose(fp);
	}
   	return(retval);
}


int main(int argc, char* argv[])
{
	pid_t pid;
	DataMsg upmsg,dnmsg, upmsg2;
	char pidChannel[24];
	Channel* downChan;
	Channel* upChan;
	char PID[16];
	
	char ctrlchannel[64];
	
	pid = getpid();
	
    sprintf(PID, "%lu", pid);
    printf("pid %lu   %s \n",(size_t)pid,PID);
    
	
	
	upmsg.m_senderPid = getpid();
	upmsg.m_command = DCMD_PING;
	
	
	upmsg2.m_senderPid = getpid();
	upmsg2.m_command = DCMD_SUBQ;
	upmsg2.m_subImsi = 333333333; 
	

	assert((GetStrInConfigFile("../../config/config.txt", "ui-queryManager channel", ctrlchannel))==FOUND); 

	assert((downChan = ChannelCreate(PID , CHAN_SIZE, CHANNEL_CREATE))!=NULL);
	assert((upChan = ChannelCreate(ctrlchannel , CHAN_SIZE, CHANNEL_CREATE))!=NULL);
	
	while(1)
	{
		sleep(1);
		printf("Sending  (sender [%lu]) Ping On Up   Channel\n",(size_t)pid);
		ChannelTransmit(upChan, &upmsg, sizeof(DataMsg));
		sleep(1);
		ChannelReceive(downChan, &dnmsg, sizeof(DataMsg));
		printf("Received (from QM [%lu]) Ping On Down Channel\n",(size_t)dnmsg.m_senderPid);
		sleep(20);
		ChannelTransmit(upChan, &upmsg2, sizeof(DataMsg));
		sleep(1);
		ChannelReceive(downChan, &dnmsg, sizeof(DataMsg));
		printf("IMSI Query:\n%s\n",dnmsg.m_retvalQuery);
		
		
		
	}
	return 0;
}




