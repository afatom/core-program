#include <publisher.h>
#include <distributor.h>
#include <iostream>
#include <registrar.h>
#include <string>
#include <vector>
#include <testListiner.h>
#include <publisher.h>
#include <mu_test.h>
using namespace std;

UNIT(MVP_Test_1)
	//WtQueue_t<const Event_t*>* pqueue = new WtQueue_t<const Event_t*>;
	WtQueue_t<Event_ShPointer>* pqueue = new WtQueue_t<Event_ShPointer>;
	Publisher_t* ppub = new Publisher_t(pqueue);
	
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
	
	
	
	ppub->Publish(ptr1);
	ppub->Publish(ptr2);
	
	ppub->Publish(ptr3);
	ppub->Publish(ptr4);
	ppub->Publish(ptr5);
		
	
	
	Registrar_t* pReg = new Registrar_t;
	
	vector<Testlistener_t*> plisteners;
	for(size_t j=0;j<1024;++j)
	{
		plisteners.push_back(new Testlistener_t);
	}
	
	ASSERT_THAT(plisteners.size() == 1024);

		string* str = new string[1024];
	
	for(int i=0; i<256; ++i)
		str[i] = "SMOKE";
	
	for(int i=256; i<512; ++i)
		str[i] = "FIRE";
	
	for(int i=512; i<700; ++i)
		str[i] = "HVAC";
	
	for(int i=700; i<800; ++i)
		str[i] = "HDLC";
	
	for(int i=800; i<900; ++i)
		str[i] = "HXLCC";

	for(int i=900; i<1024; ++i)
		str[i] = "HUMIDITY";
		
	for(int i=0; i<1024; ++i)
	{
		pReg->Subscribe(plisteners[i],str[i]);
	}
	
	Distributor_t* pdist = new Distributor_t(pqueue, pReg);
	
	pdist->Disperse();

END_UNIT


TEST_SUITE(MVP Unit Test)
	TEST(MVP_Test_1)
END_SUITE



