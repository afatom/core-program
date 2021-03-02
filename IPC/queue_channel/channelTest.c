#include "channel.h"
#include <time.h> /*srand*/
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <assert.h>
#include "mu_test.h"    
#include <stdio.h>  
#include <string.h>
#include <unistd.h>


char sstr[64] = "Ping channel is funny";
char rxsstr[64]="...";

char msg[8]="Ping";
char rxstr[8]="....";

UNIT(Channel_Create_And_Destroy_Test)

	Channel* ch = NULL;
   	ch = ChannelCreate("MSGQQ",sizeof(msg),1024,CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	ChannelDestroy(&ch);
	ASSERT_THAT(ch == NULL);
END_UNIT


UNIT(Channel_Tx_Rx_Test)
	Channel* ch = NULL;
	
  
   	
   	ch = ChannelCreate("MSGQQ",sizeof(msg),1024,CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	ASSERT_THAT (ChannelTransmit(ch, (void*)msg, sizeof(msg)) == CHANNEL_SUCCESS);
   	
   	
	ASSERT_THAT (ChannelReceive(ch, (void*)rxstr, sizeof(msg)) == CHANNEL_SUCCESS);
	printf("%s %s\n",rxstr,msg);
	ASSERT_THAT((strcmp(msg,rxstr))==0);
	ChannelDestroy(&ch);
   	ASSERT_THAT(ch == NULL);
END_UNIT

UNIT(Channel_BroadCast_Test)
	Channel* ch = NULL;
	

   	
   	ch = ChannelCreate("MSGQQ",sizeof(sstr),1024,CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	ASSERT_THAT (ChannelTransmit(ch, (void*)sstr, 1024) == CHANNEL_SUCCESS);
   	
   	
	ASSERT_THAT (ChannelReceive(ch, (void*)rxsstr, 1024) == CHANNEL_SUCCESS);
	ASSERT_THAT((strcmp(sstr,rxsstr))==0);
	ChannelDestroy(&ch);
   	ASSERT_THAT(ch == NULL);
END_UNIT

UNIT(Channel_BroadCast__PING_Test)
	Channel* ch = NULL;
	char pstr[8];
   	char rxstr[8];
   	
   	ch = ChannelCreate("MSGQQ", sizeof(pstr),1024, CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	ASSERT_THAT (ChannelTransmit(ch, (void*)pstr, 8) == CHANNEL_SUCCESS);
   	
   	
	ASSERT_THAT (ChannelReceive(ch, (void*)rxstr, 8) == CHANNEL_SUCCESS);
	ASSERT_THAT((strcmp(pstr,rxstr))==0);
	ChannelDestroy(&ch);
   	ASSERT_THAT(ch == NULL);
END_UNIT

UNIT(Channel_Cyclic_BroadCast_Test)
	Channel* ch = NULL;
	

   	
   	ch = ChannelCreate("MSGQQ",sizeof(sstr),1024,CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	
   	while (1)
   	{
	   	ASSERT_THAT (ChannelTransmit(ch, (void*)sstr, 1024) == CHANNEL_SUCCESS);
		printf("Tx:: %s\n",sstr);
		sleep(1);
		ASSERT_THAT (ChannelReceive(ch, (void*)rxsstr, 1024) == CHANNEL_SUCCESS);
		printf("Rx:: %s\n",rxsstr);
		ASSERT_THAT((strcmp(sstr,rxsstr))==0);
			
   	}
	
	
	ChannelDestroy(&ch);
   	ASSERT_THAT(ch == NULL);
END_UNIT

TEST_SUITE(IPC Channel Module Test)
	TEST(Channel_Create_And_Destroy_Test)
	TEST(Channel_Tx_Rx_Test)
	TEST(Channel_BroadCast_Test)
	TEST(Channel_BroadCast__PING_Test)  
	TEST(Channel_Cyclic_BroadCast_Test) 
END_SUITE

