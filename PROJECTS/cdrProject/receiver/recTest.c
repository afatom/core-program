#include "cdr.h"
#include "channel.h"
#include "receiver.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "aggregator.h"
#include <string.h>
#include "mu_test.h"







/*
UNIT(Receiver_Create_And_Destroy_Test)
	Channel* ch; 
	Receiver* rec;
	ch = ChannelCreate("receiver_test_channel", 1024,CHANNEL_CREATE);
	ASSERT_THAT(ch != NULL);
	
	rec = ReceiverCreate("config.txt",2, ch);
	ASSERT_THAT(rec != NULL);
	ReceiverDestroy(&rec);
	ASSERT_THAT(rec == NULL);
END_UNIT*/

UNIT(Receiver_Rx_Test)

	Receiver* rec;

	
	rec = ReceiverCreate("config.txt",1);
	
	ASSERT_THAT(rec != NULL);
	ReceiverStart(rec);
	ReceiverDestroy(&rec);
	ASSERT_THAT(rec == NULL);
END_UNIT

TEST_SUITE(Receiver Test)
TEST(Receiver_Rx_Test)


END_SUITE
