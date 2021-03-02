#include <wtqueue.h>
#include <iostream>
#include <nevent.h>
#include <vector>
#include <payload.h>
#include <string>
#include <mu_test.h>
#include <cstdio>
#include <unistd.h>

using namespace std;


UNIT(Push_Few_Test_One_Thread_Pushing)
	WtQueue_t<Event_ShPointer> q;
	ASSERT_THAT(q.size()== 0);
	cout<<"is empty "<<q.empty()<<endl;
	ASSERT_THAT(q.empty() == true);
	
	string type("FIRE");
    string location("Floor 1");
    Payload_t p("0855XX56Vu");
    //Event_t* ptr1 = new Event_t(type, location, p);
	Event_ShPointer ptr1(new Event_t(type, location, p));

	Payload_t p2("085YYRT56Vu");
    string type2("FIRE_SMOKE");
    string location2("Floor 10");
	Event_ShPointer ptr2(new Event_t(type2, location2, p2)); 

    q.push (ptr1);
    q.push (ptr2);
    
    ASSERT_THAT(q.size()== 2);
    ASSERT_THAT(q.empty() == false);
END_UNIT


UNIT(Push_Many_Test_One_Thread_Pushing)
	WtQueue_t<Event_ShPointer> q;
	ASSERT_THAT(q.size()== 0);
	ASSERT_THAT(q.empty() == true);
	
	string type("FIRE");
    string location("Floor 1");
    Payload_t p("0855XX56Vu");
	Event_ShPointer ptr1(new Event_t(type, location, p));
	
	Payload_t p2("085YYRT56Vu");
    string type2("FIRE_SMOKE");
    string location2("Floor 10");
	Event_ShPointer ptr2(new Event_t(type2, location2, p2));

    q.push (ptr1);
    q.push (ptr2);
    
    ASSERT_THAT(q.size()== 2);
    ASSERT_THAT(q.empty() == false);
	
	std::vector<Event_ShPointer> vec;
	for(int i = 0; i < 1024; ++i)
	{
		Event_ShPointer ptrx(new Event_t(type, location2,p2 ));
		vec.push_back(ptrx);
		q.push(vec[i]);
	}
	ASSERT_THAT(q.size()== 1026);
    ASSERT_THAT(q.empty() == false);
	
END_UNIT


UNIT(Push_And_Pop_Many_Test_One_Thread_Pushing)
	WtQueue_t<Event_ShPointer> q;
	ASSERT_THAT(q.size()== 0);
	ASSERT_THAT(q.empty() == true);
	
	string type("FIRE");
    string location("Floor 1");
    Payload_t p("0855XX56Vu");
    Event_ShPointer ptr1(new Event_t(type, location, p));

	Payload_t p2("085YYRT56Vu");
    string type2("FIRE_SMOKE");
    string location2("Floor 10");
	Event_ShPointer ptr2(new Event_t(type2, location2, p2));

    q.push (ptr1);
    q.push (ptr2);
    
    ASSERT_THAT(q.size()== 2);
    ASSERT_THAT(q.empty() == false);
	
	
	std::vector<Event_ShPointer> vec;
	for(int i = 0; i < 1024; ++i)
	{
		Event_ShPointer ptrx(new Event_t(type, location2,p2 ));
		vec.push_back(ptrx);
		q.push(vec[i]);
	}
	ASSERT_THAT(q.size()== 1026);
    ASSERT_THAT(q.empty() == false);
	
	q.Popfront();
	
	ASSERT_THAT(q.size()== 1025);
	
	for(int i = 1024; i > 0; --i)
	{
		ASSERT_THAT(q.size()== i+1);
		q.Popfront();
	}
END_UNIT


void* ThreadPushFunction (void* pp)
{
	WtQueue_t<Event_ShPointer>* q = (WtQueue_t<Event_ShPointer>*)pp;
	//ASSERT_THAT(q->size()== 0);
	//ASSERT_THAT(q->empty() == true);
	
	string type("FIRE");
    string location("Floor 1");
    Payload_t p("0855XX56Vu");
    Event_ShPointer ptr1(new Event_t(type, location, p));

	Payload_t p2("085YYRT56Vu");
    string type2("FIRE_SMOKE");
    string location2("Floor 10");
	Event_ShPointer ptr2(new Event_t(type, location2,p2 ));

    q->push (ptr1);
    q->push (ptr2);
	
	
	std::vector<Event_ShPointer> vec;
	for(int i = 0; i < 1024; ++i)
	{
		Event_ShPointer ptrx(new Event_t(type, location2,p2 ));
		vec.push_back(ptrx);
		//sleep(3);
		//cout<<"In Push Function"<<endl;
		q->push(vec[i]);
	}
}


void* ThreadPopFunction (void* pp)
{
	WtQueue_t<Event_ShPointer>* q = (WtQueue_t<Event_ShPointer>*)pp;
	Event_ShPointer ppt =  q->Popfront();
	
	for(int i = 1023; i > 0; --i)
	{
		q->Popfront();
		//cout<<"Thread: "<< (size_t)pthread_self() <<" In Thread Pop Function"<<endl;
		//cout<<"In Pop Function"<<endl;
		
		//sleep(1);
	}
}


UNIT(Push_And_Pop_Many_Test_MT_Thread_Pushing_Poping)
	
	WtQueue_t<Event_ShPointer>* ptr = new WtQueue_t<Event_ShPointer>;
	pthread_t pusher1;
	pthread_t pusher2;
	pthread_t pusher3;
	pthread_t pusher4;
	
	pthread_t poper1;
	pthread_t poper2;
	pthread_t poper3;
	pthread_t poper4;
	
	
    pthread_create(&pusher1, 0, ThreadPushFunction, ptr);
    pthread_create(&pusher2, 0, ThreadPushFunction, ptr);
    pthread_create(&pusher3, 0, ThreadPushFunction, ptr);
    pthread_create(&pusher4, 0, ThreadPushFunction, ptr);
    
    pthread_create(&poper1, 0, ThreadPopFunction, ptr);
    pthread_create(&poper2, 0, ThreadPopFunction, ptr);
    pthread_create(&poper3, 0, ThreadPopFunction, ptr);
    pthread_create(&poper4, 0, ThreadPopFunction, ptr);
    
    pthread_join(pusher1,0);
    pthread_join(pusher2,0);
    pthread_join(pusher3,0);
    pthread_join(pusher4,0);
    
    
    pthread_join(poper1,0);
    pthread_join(poper2,0);
    pthread_join(poper3,0);
    pthread_join(poper4,0);
    
    delete ptr;
END_UNIT




void* PusherThreadFunc(void* ptr)
{
	WtQueue_t<Event_ShPointer>* queue = (WtQueue_t<Event_ShPointer>*)ptr;
	std::vector<Event_ShPointer> vec;
    string type("FIRE_SMOKE");
    string location("Floor 10");
    Payload_t payload("085YYRT56Vu");
	for(int i = 0; i < 256; ++i)
	{
		Event_ShPointer pevent(new Event_t(type, location,payload));
		vec.push_back(pevent);
		//sleep(3);
		//cout<<"In Push Function"<<endl;
		//q->push(vec[i]);
	}
	
	int i =256;
	while(i--)
	{
		queue->push(vec[i]);
		sleep(2);
	}
	return 0;
}

void* PoperThreadFunc (void* ptr)
{
	WtQueue_t<Event_ShPointer>* queue = (WtQueue_t<Event_ShPointer>*)ptr;
	//Event_ShPointer ppt =  q->Popfront();
	
	for(;;)
	{
		Event_ShPointer pevent = queue->Popfront();
		cout<<"Poper thread received signal"<< *pevent<<endl;
		//cout<<"Thread: "<< (size_t)pthread_self() <<" In Thread Pop Function"<<endl;
		//cout<<"In Pop Function"<<endl;
		//sleep(1);
	}
	return 0;
}





UNIT(MT_Many_Pushers_One_Poper_Test)
	
	WtQueue_t<Event_ShPointer>* ptr = new WtQueue_t<Event_ShPointer>;
	pthread_t pusher1;
	pthread_t poper1;
	
    pthread_create(&pusher1, 0, PusherThreadFunc, ptr);
    pthread_create(&poper1, 0, PoperThreadFunc, ptr);

    
    pthread_join(pusher1,0);

    pthread_join(poper1,0);

    delete ptr;
END_UNIT







TEST_SUITE(Thread Safe STL Queue Unit Test)
	TEST(Push_Few_Test_One_Thread_Pushing)
	TEST(Push_Many_Test_One_Thread_Pushing)
	TEST(Push_And_Pop_Many_Test_One_Thread_Pushing)
	TEST(Push_And_Pop_Many_Test_MT_Thread_Pushing_Poping)
	TEST(MT_Many_Pushers_One_Poper_Test)
END_SUITE

