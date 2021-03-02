
#include <mu_test.h>
#include <cstdio> //mu_test 
#include <hub.h>
#include <iostream>
#include <testListiner.h>
#include <pthread.h>
#include <unistd.h>
#include <tr1/memory>
#include <ilistener.h>
#include <iostream>
#include <iregistrar.h>
#include <registrar.h>
#include <string>
#include <testListiner.h>
#include <mu_test.h>
#include <cstdio>



///////harcoded factory includes
#include <lgsensor.h>
#include <lgcontroler.h>
#include <agentconfig.h>
///////////////////////////////

using namespace std;


void* DisperseFunc(void* ptr)
{
	Distributor_t* pd = (Distributor_t*)ptr;
	pd->Disperse();
	return 0;
}



UNIT(Create_Hub_Test)
	Hub_t* phub =  new Hub_t;
    ASSERT_THAT(phub != 0);
	delete phub;
END_UNIT

UNIT(Publish_One_Event_Test)
	Hub_t* phub =  new Hub_t;
    ASSERT_THAT(phub != 0);

    string ttype("FIRE");
    string location("Floor 1");
    Payload_t p("0855XX56Vu");
    Event_ShPointer ptr1(new Event_t(ttype, location, p));
    Publisher_t* ppub = phub->GetPublisher(); 
    ppub->Publish(ptr1);

    Registrar_t* pReg = phub->GetRegistrar();

	Ilistener_t* plistener1 = new Testlistener_t;
	string type1("FIRE");

	pReg->Subscribe(plistener1, type1);

	Distributor_t* pdist = phub->GetDestributor();
	
	pthread_t dist;
	//cout<<"&"<<endl; 
	pthread_create(&dist, 0, DisperseFunc, pdist);
	
	sleep(1);
	
	int i = 3;
	while(i--){
	string type2("FIRE");
    string location2("FLOOR 55");
    Payload_t p2("088900Xu");
    Event_ShPointer ptr2(new Event_t(type2, location2, p2));
    ppub->Publish(ptr2);
	
	sleep(1);
	}
	delete phub;
END_UNIT


UNIT(Publish_Few_Events_Test)
	Hub_t* phub =  new Hub_t;
    ASSERT_THAT(phub != 0);

    string ttype("FIRE");
    string location("Floor 1");
    Payload_t p("0855XX56Vu");
    Event_ShPointer ptr1(new Event_t(ttype, location, p));
	Payload_t p2("085YYRT56Vu");
    string ttype2("SMOKE");
    string location2("Floor 10");
	Event_ShPointer ptr2(new Event_t(ttype2, location2, p2));
	
	Payload_t p3("085DDDFT56Vu");
    string ttype3("HEAT");
    string location3("Floor 15");
	Event_ShPointer ptr3(new Event_t(ttype2, location2, p2));
	
	Payload_t p4("08889EYRT56Vu");
    string ttype4("HVAC");
    string location4("Floor 7");
	Event_ShPointer ptr4(new Event_t(ttype2, location2, p2));
	
	Payload_t p5("085YYRTT6Vu");
    string ttype5("HUMIDITY");
    string location5("Floor 9");
	Event_ShPointer ptr5(new Event_t(ttype2, location2, p2));

    Publisher_t* ppub = phub->GetPublisher(); 
    ppub->Publish(ptr1);
	ppub->Publish(ptr2);
	
	ppub->Publish(ptr3);
	ppub->Publish(ptr4);
	ppub->Publish(ptr5);



    Registrar_t* pReg = phub->GetRegistrar();

	Ilistener_t* plistener1 = new Testlistener_t;
	string type1("FIRE");

	Ilistener_t* plistener2 = new Testlistener_t;
	string type2("SMOKE");
	
	Ilistener_t* plistener3 = new Testlistener_t;
	string type3("HVAC");
	
	Ilistener_t* plistener4 = new Testlistener_t;
	string type4("HUMIDITY");

	pReg->Subscribe(plistener1, type1);
	pReg->Subscribe(plistener2, type2);
	pReg->Subscribe(plistener3, type3);
	pReg->Subscribe(plistener4, type4);
	Distributor_t* pdist = phub->GetDestributor();
	pdist->Disperse();

	delete phub;

END_UNIT







UNIT(Publish_And_Update_Test)

Hub_t* phub =  new Hub_t;
    ASSERT_THAT(phub != 0);

    string ttype("COLD");
    string location("Floor 1");
    Payload_t p("0855XX56Vu");
    Event_ShPointer ptr1(new Event_t(ttype, location, p));
	Payload_t p2("085YYRT56Vu");
    string ttype2("SECURITY");
    string location2("Floor 10");
	Event_ShPointer ptr2(new Event_t(ttype2, location2, p2));
	
	Payload_t p3("085DDDFT56Vu");
    string ttype3("STEAM");
    string location3("Floor 15");
	Event_ShPointer ptr3(new Event_t(ttype2, location2, p2));
	
	Payload_t p4("08889EYRT56Vu");
    string ttype4("LUMINA");
    string location4("Floor 7");
	Event_ShPointer ptr4(new Event_t(ttype2, location2, p2));
	
	Payload_t p5("085YYRTT6Vu");
    string ttype5("POWER");
    string location5("Floor 9");
	Event_ShPointer ptr5(new Event_t(ttype2, location2, p2));

    Publisher_t* ppub = phub->GetPublisher(); 
    ppub->Publish(ptr1);
	ppub->Publish(ptr2);
	
	ppub->Publish(ptr3);
	ppub->Publish(ptr4);
	ppub->Publish(ptr5);



    Registrar_t* pReg = phub->GetRegistrar();

	Ilistener_t* plistener1 = new Testlistener_t;
	string type1("FIRE");

	Ilistener_t* plistener2 = new Testlistener_t;
	string type2("SMOKE");
	
	Ilistener_t* plistener3 = new Testlistener_t;
	string type3("HVAC");
	
	Ilistener_t* plistener4 = new Testlistener_t;
	string type4("HUMIDITY");

	pReg->Subscribe(plistener1, type1);
	pReg->Subscribe(plistener2, type2);
	pReg->Subscribe(plistener3, type3);
	pReg->Subscribe(plistener4, type4);
	Distributor_t* pdist = phub->GetDestributor();

	pthread_t dist;
	//cout<<"&"<<endl; 
	pthread_create(&dist, 0, DisperseFunc, pdist);
	//cout<<"sleeping for 3 sec.."<<endl;
	//sleep(3);

	Payload_t p6("085YYRTT6Vu");
    string ttype6("FIRE");
    string location6("Floor 9");
	Event_ShPointer ptr6(new Event_t(ttype6, location6, p6)); 
    ppub->Publish(ptr6);

    pthread_join(dist,0);

	delete phub;

END_UNIT






void* sensorThread(void* ptr)
{
	Publisher_t* pub = (Publisher_t*)ptr;
	while (true)
	{
		Payload_t p1("085YYRTT6Vu");
		string type1("LgHue");
		string location1("Floor 9");
		Event_ShPointer ptr1(new Event_t(type1, location1, p1));
		pub->Publish(ptr1);
		sleep(1);	
	}
	return 0;
}

void* contThread(void* ptr)
{
	IAgent_t* ctr = (IAgent_t*)ptr;
	ctr->Run();
	return 0;
}


UNIT(Hub_HardCoded_Agents_Factory_Test)
	Hub_t* phub =  new Hub_t;
    Publisher_t* ppub = phub->GetPublisher();
    struct AgentInit lg;
    lg.m_deviceId = "12558XXytLg";
	lg.m_type = "LgHue";
	lg.m_floor = "8";
	lg.m_room = "5";
	lg.m_log = "log";
	lg.m_config = "log/hue1256";
	lg.m_soName = "shmoko";
    AgentConfig_t lgconf(&lg);
	
	
	IAgent_t* sensor = new LgSensor_t(ppub, lgconf);
	
	IRegistrar_t* preg = phub->GetRegistrar();
	
	
	IAgent_t* cont = new LgControl_t(preg, lgconf);
	
	pthread_t dist;
	Distributor_t* pdist = phub->GetDestributor();
	pthread_create(&dist, 0, DisperseFunc, pdist);
	
	pthread_t sens;
	pthread_t contrl;
	
	
	pthread_create(&contrl, 0, contThread, cont);
	pthread_create(&sens, 0, sensorThread, ppub);
	
	//IAgent_t* Create(IPublisher_t* _pub, IRegistrar_t* _reg, AgentConfig_t& _config)
	
	pthread_join(dist,0);
	pthread_join(contrl,0);
	pthread_join(sens,0);
	
END_UNIT



TEST_SUITE(Hub Unit Test)
	TEST(Create_Hub_Test)
	//TEST(Publish_One_Event_Test)
	//TEST(Publish_Few_Events_Test)
	//TEST(Publish_And_Update_Test)
	TEST(Hub_HardCoded_Agents_Factory_Test)
END_SUITE



