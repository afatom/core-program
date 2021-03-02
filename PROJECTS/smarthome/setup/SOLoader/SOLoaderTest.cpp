#include <iostream>
#include <nevent.h>
#include <vector>
#include <cstdio> //mu_test 
#include <pthread.h>
#include <tr1/memory>
#include <registrar.h>
#include <mu_test.h>
#include <cstdio>
#include <soloader.h>
#include <hub.h>
using namespace std;


UNIT(Create_SOLoader_Test)
	Hub_t* phub =  new Hub_t;
    ASSERT_THAT(phub != 0);
    
	Publisher_t* ppub = phub->GetPublisher(); 
    Registrar_t* preg = phub->GetRegistrar();
    ASSERT_THAT(ppub != 0);
    ASSERT_THAT(preg != 0);
    string sodir = "/home/adhamfaris/Documents/6.7smartHome/smarthome/setup/sharedObjects";
    SoLoader_t* psoloader = new SoLoader_t(preg, ppub, sodir);
    delete psoloader;    
	delete phub;
END_UNIT


UNIT(Loading_One_SO_Test)
	Hub_t* phub =  new Hub_t;
    ASSERT_THAT(phub != 0);
    
	Publisher_t* ppub = phub->GetPublisher(); 
    Registrar_t* preg = phub->GetRegistrar();
    ASSERT_THAT(ppub != 0);
    ASSERT_THAT(preg != 0);
    string sodir = "/home/adhamfaris/Documents/6.7smartHome/smarthome/setup/sharedObjects";
    SoLoader_t* psoloader = new SoLoader_t(preg, ppub, sodir);
    
    struct AgentInit X;
    
    X.m_deviceId = "light-1-a-1";
    X.m_type = "LgHue";
    X.m_floor = "1";
    X.m_log = "lights";
    X.m_room = "room_1_a";
    X.m_config = "iot:1003,sat:242, brigh:154, hue:8200";
    
    AgentConfig_t agentConfig(&X);
	IAgent_t* iaptr = psoloader->LoadAgent(agentConfig);
	ASSERT_THAT(iaptr != 0);
    delete psoloader;    
	delete phub;

END_UNIT

UNIT(Loading_Many_SO_Test)
	Hub_t* phub =  new Hub_t;
    ASSERT_THAT(phub != 0);
    
	Publisher_t* ppub = phub->GetPublisher(); 
    Registrar_t* preg = phub->GetRegistrar();
    ASSERT_THAT(ppub != 0);
    ASSERT_THAT(preg != 0);
    string sodir = "/home/adhamfaris/Documents/6.7smartHome/smarthome/setup/sharedObjects";
    SoLoader_t* psoloader = new SoLoader_t(preg, ppub, sodir);
    
    struct AgentInit X;
    
    X.m_deviceId = "light-1-a-1";
    X.m_type = "LgHue";
    X.m_floor = "1";
    X.m_log = "lights";
    X.m_room = "room_1_a";
    X.m_config = "iot:1003,sat:242, brigh:154, hue:8200";
    
    AgentConfig_t agentConfig(&X);
	IAgent_t* iaptr = psoloader->LoadAgent(agentConfig);
	ASSERT_THAT(iaptr != 0);
    
    
    X.m_deviceId = "light-1-a-1";
    X.m_type = "LgContHue";
    X.m_floor = "1";
    X.m_log = "lights";
    X.m_room = "room_1_a";
    X.m_config = "iot:1003,sat:242, brigh:154, hue:8200";
    
	AgentConfig_t agentConfigNew(&X);

	IAgent_t* niaptr = psoloader->LoadAgent(agentConfigNew);
	ASSERT_THAT(niaptr != 0);
    
	

    X.m_deviceId = "light-1-a-1";
    X.m_type = "LgContHue";
    X.m_floor = "1";
    X.m_log = "lights";
    X.m_room = "room_1_a";
    X.m_config = "iot:1003,sat:242, brigh:154, hue:8200";
    
	AgentConfig_t agentConfigNewn(&X);
	IAgent_t* cniaptr = psoloader->LoadAgent(agentConfigNewn);
	ASSERT_THAT(cniaptr != 0);
    
    
    delete psoloader;    
	delete phub;

END_UNIT


TEST_SUITE(Thread Safe STL Queue Unit Test)
	TEST(Create_SOLoader_Test)
	TEST(Loading_One_SO_Test)
	TEST(Loading_Many_SO_Test)
END_SUITE

