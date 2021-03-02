#include <mu_test.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ireader.h>
#include <agentconfig.h>
#include <txtreader.h>


using namespace std;


UNIT(Agent_Config_File_Processing_Test)
	TxtReader_t X("agentsconfig.txt");
	AgentConfig_t temp = X.ReadSingleConfigSet();
	//cout<<temp<<endl;
	//temp = X.ReadSingleConfigSet();
	//cout<<temp<<endl;
	ASSERT_THAT(temp.GetId() == "light-1-a-1");
	//ASSERT_THAT(temp.GetType() == "PhilipsHue");
	ASSERT_THAT(temp.GetRoom() == "room_1_a");
	ASSERT_THAT(temp.GetFloor() == "1"); 
	ASSERT_THAT(temp.GetLog() == "lights"); 
	ASSERT_THAT(temp.GetConfig() == "iot:1003,sat:242, brigh:154, hue:8200");
END_UNIT




UNIT(Agent_Config_File_Many_Sets_Processing_Test)
	TxtReader_t X("agentsconfig.txt");
	AgentConfig_t temp = X.ReadSingleConfigSet();
	//cout<<temp<<endl;
	//temp = X.ReadSingleConfigSet();
	//cout<<temp<<endl;
	ASSERT_THAT(temp.GetId() == "light-1-a-1");
	//ASSERT_THAT(temp.GetType() == "PhilipsHue");
	ASSERT_THAT(temp.GetRoom() == "room_1_a");
	ASSERT_THAT(temp.GetFloor() == "1"); 
	ASSERT_THAT(temp.GetLog() == "lights"); 
	ASSERT_THAT(temp.GetConfig() == "iot:1003,sat:242, brigh:154, hue:8200");
	
	temp = X.ReadSingleConfigSet();
	ASSERT_THAT(temp.GetId() == "light-1-a-2");
	//ASSERT_THAT(temp.GetType() == "PhilipsHue");
	ASSERT_THAT(temp.GetRoom() == "room_1_a");
	ASSERT_THAT(temp.GetFloor() == "1"); 
	ASSERT_THAT(temp.GetLog() == "lights"); 
	ASSERT_THAT(temp.GetConfig() == "iot:1008,sat:242, brigh:154, hue:8200");
END_UNIT




UNIT(Agent_Config_File_EOF_Test)
	TxtReader_t X("agentsconfig.txt");
	AgentConfig_t temp = X.ReadSingleConfigSet();
	//cout<<temp<<endl;
	//temp = X.ReadSingleConfigSet();
	//cout<<temp<<endl;
	ASSERT_THAT(temp.GetId() == "light-1-a-1");
	//ASSERT_THAT(temp.GetType() == "PhilipsHue");
	ASSERT_THAT(temp.GetRoom() == "room_1_a");
	ASSERT_THAT(temp.GetFloor() == "1"); 
	ASSERT_THAT(temp.GetLog() == "lights"); 
	ASSERT_THAT(temp.GetConfig() == "iot:1003,sat:242, brigh:154, hue:8200");
	
	temp = X.ReadSingleConfigSet();
	ASSERT_THAT(temp.GetId() == "light-1-a-2");
	//ASSERT_THAT(temp.GetType() == "PhilipsHue");
	ASSERT_THAT(temp.GetRoom() == "room_1_a");
	ASSERT_THAT(temp.GetFloor() == "1"); 
	ASSERT_THAT(temp.GetLog() == "lights"); 
	ASSERT_THAT(temp.GetConfig() == "iot:1008,sat:242, brigh:154, hue:8200");

	AgentConfig_t temp2 = X.ReadSingleConfigSet();
	AgentConfig_t temp3 = X.ReadSingleConfigSet();
	AgentConfig_t temp4 = X.ReadSingleConfigSet();
	//cout<<temp4<<endl;
	ASSERT_THAT(temp4.GetId() == "0");
END_UNIT



TEST_SUITE(Txt Reader Unit Test)
	TEST(Agent_Config_File_Processing_Test)
	TEST(Agent_Config_File_Many_Sets_Processing_Test)
	TEST(Agent_Config_File_EOF_Test)
END_SUITE
