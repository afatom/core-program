#include <nevent.h>
#include <iostream>
#include <mu_test.h>
#include <cstdio>
using namespace std;


UNIT(Create_Event_Test)
	Event_t msg;
    msg.SetType("fire");
    msg.SetLocation("floor 1");
	ASSERT_THAT(msg.GetType() == "fire");
	ASSERT_THAT(msg.GetLocation() == "floor 1");
	Payload_t Pa("SDFFF85946ZS#");
	msg.SetPayLoadData(Pa);
	//cout<<msg<<endl;
END_UNIT

TEST_SUITE(Thread Safe STL Queue Unit Test)
	TEST(Create_Event_Test)
END_SUITE