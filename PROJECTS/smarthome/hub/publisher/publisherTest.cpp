#include <publisher.h>
#include <iostream>
#include <nevent.h>
#include <wtqueue.h>
#include <pthread.h>
#include <cstdlib>
#include <nevent.h>
#include <distributor.h>
#include <iostream>
#include <registrar.h>
#include <mu_test.h>
#include <stdio.h>

using namespace std;


UNIT(Publisher_t_Create_Test)
	WtQueue_t<Event_ShPointer>* q = new WtQueue_t<Event_ShPointer>;
	ASSERT_THAT(q->size()== 0);
	//cout<<"is empty "<<q.empty()<<endl;
	ASSERT_THAT(q->empty() == true);
	
	string type("FIRE");
    string location("Floor 1");
    Payload_t p("0855XX56Vu");
    //Event_t* ptr1 = new Event_t(type, location, p);
	Event_ShPointer ptr1(new Event_t(type, location, p));

	Payload_t p2("085YYRT56Vu");
    string type2("FIRE_SMOKE");
    string location2("Floor 10");
	Event_ShPointer ptr2(new Event_t(type2, location2, p2)); 

    q->push (ptr1);
    q->push (ptr2);
    //ASSERT_THAT(dis > 0);
    ASSERT_THAT(q->size()== 2);
    ASSERT_THAT(q->empty() == false);
    
    Publisher_t* pub = new Publisher_t(q);
    pub->Publish(ptr2);
	pub->Publish(ptr1);
        
	ASSERT_THAT(q->size()== 4);
    
END_UNIT


TEST_SUITE(Publisher Test)
	TEST(Publisher_t_Create_Test)
END_SUITE
