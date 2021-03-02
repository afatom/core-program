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


char sstr[1024] = "Ping Rxajksdfhklajhsdlfhalksdfmabmsur29083475890723945 2374159003475lasldfhlk ajksldhlfjkhalksdhfkjahslkdhflkahsdlkjfh akjshdklfhlakjhsdklhfklahskldfhklajshdflkhasdiufyqweuiyr8698623894568 asdfgajksdgfkjagsdkfjg asdfa53456423565465245634578927 7982734895789237495 24134564556243456456 23459720347572893475970 12345hklaehfmdm,m,xbncasdklfh lkajh&*^*(%^(%%$^%&$^$^ ahdkahdkahui qwer54we4r556we4r564w6e4r654we56r43564564563445663425231sd23f1gsdf1g sdfhfgakjgsjdhgfjkas ashdgfkgasdgfjk gasdf";




/******************************************************/
UNIT(Channel_Create_And_Destroy_Test)

	Channel* ch = NULL;
   	ch = ChannelCreate("MSGQQ",1024,CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	ChannelDestroy(&ch);
	ASSERT_THAT(ch == NULL);
END_UNIT
/******************************************************/

UNIT(Channel_Tx_Rx_Test)
	Channel* ch = NULL;
	char str[8] = "Ping Rx";
   	char rxstr[24];
   	
   	ch = ChannelCreate("MSGQQ", 1024, CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	ASSERT_THAT (ChannelTransmit(ch, (void*)str, 8) == CHANNEL_SUCCESS);
   	
   	
	ASSERT_THAT (ChannelReceive(ch, (void*)rxstr, 24) == CHANNEL_SUCCESS);
	ASSERT_THAT((strcmp(str,rxstr))==0);
	ChannelDestroy(&ch);
   	ASSERT_THAT(ch == NULL);
END_UNIT

UNIT(Channel_BroadCast_Test)
	Channel* ch = NULL;
	
   	char rxstr[1024];
   	
   	ch = ChannelCreate("MSGQQ", 1024, CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	ASSERT_THAT (ChannelTransmit(ch, (void*)sstr, 1024) == CHANNEL_SUCCESS);
   	
   	
	ASSERT_THAT (ChannelReceive(ch, (void*)rxstr, 1024) == CHANNEL_SUCCESS);
	ASSERT_THAT((strcmp(sstr,rxstr))==0);
	ChannelDestroy(&ch);
   	ASSERT_THAT(ch == NULL);
END_UNIT

UNIT(Channel_BroadCast__PING_Test)
	Channel* ch = NULL;
	char pstr[8];
   	char rxstr[8];
   	
   	ch = ChannelCreate("MSGQQ", 1024, CHANNEL_CREATE);
   	ASSERT_THAT(ch != NULL);
   	ASSERT_THAT (ChannelTransmit(ch, (void*)pstr, 8) == CHANNEL_SUCCESS);
   	
   	
	ASSERT_THAT (ChannelReceive(ch, (void*)rxstr, 8) == CHANNEL_SUCCESS);
	ASSERT_THAT((strcmp(pstr,rxstr))==0);
	ChannelDestroy(&ch);
   	ASSERT_THAT(ch == NULL);
END_UNIT
/******************************************************/
/*Main function */
TEST_SUITE(IPC Channel Module Test)
	TEST(Channel_Create_And_Destroy_Test)
	TEST(Channel_Tx_Rx_Test)
	TEST(Channel_BroadCast_Test)
	TEST(Channel_BroadCast__PING_Test)   
END_SUITE
/******************************************************/

