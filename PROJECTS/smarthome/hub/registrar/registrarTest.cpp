#include <ilistener.h>
#include <iostream>
#include <iregistrar.h>
#include <registrar.h>
#include <string>
#include <testListiner.h>
#include <mu_test.h>
#include <cstdio>
using namespace std;

UNIT(Registrar_Create_And_Subscribe_Few_Test)
	Registrar_t* X = new Registrar_t;
	
	Ilistener_t* plistener1 = new Testlistener_t;
	string type("FIRE");
	
	Ilistener_t* plistener2 = new Testlistener_t;
	string type2("SMOKE");
	
	X->Subscribe(plistener1, type);
	X->Subscribe(plistener2, type2);
	//cout<<X.GetSubscribersNum()<<endl;
	X->UnSubscribe(plistener1,type);
	//cout<<X.GetSubscribersNum()<<endl;
	//delete plistener1;
	delete plistener2;
	delete X;
END_UNIT


UNIT(Registrar_Create_And_Subscribe_UnSubscribe_Many_Test)
	Registrar_t* ptr = new Registrar_t;
	
	Testlistener_t** plisteners = new Testlistener_t*[1024];
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
		ptr->Subscribe(plisteners[i],str[i]);
		
	//cout<<ptr->GetSubscribersOnType("SMOKE")<<endl;	
	
	for(int i=0; i<1024; ++i){
		ptr->UnSubscribe(plisteners[i],str[i]);
		//cout<<ptr->GetSubscribersOnType("SMOKE")<<endl;
		}
		
	delete ptr;
	delete [] plisteners;
	delete [] str;
END_UNIT


UNIT(Registrar_UnSubscribe_Test)
	Registrar_t* ptr = new Registrar_t;

	
	Testlistener_t** plisteners = new Testlistener_t*[1024];
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
		ptr->Subscribe((plisteners)[i],str[i]);

	for(int i=0; i<1024; ++i)
		ptr->UnSubscribe((plisteners)[i],str[i]);
	
	delete ptr;
	delete []plisteners;
	delete [] str;
END_UNIT


UNIT(Registrar_Get_Subscribes_Test)
	Registrar_t* ptr = new Registrar_t;

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
		ptr->Subscribe(plisteners[i],str[i]);
	}
		
	//ASSERT_THAT(ptr->GetSubscribersNum() == 6);
	string type = "SMOKE";
	
	ASSERT_THAT(ptr->GetSubscribersOnType(type) == 256);
	vector<Ilistener_t*> mptr = ptr->GetSubscribers(type); 
	ASSERT_THAT(mptr.size() == 256);
	
	Payload_t x("1258SDD7Eptr");
	
	std::tr1::shared_ptr<Event_t> _pevent(new Event_t("FIRE","FLOOR25",x));
	for(size_t i=0;i<256;++i)
	{
		//mptr[i]->Update(_pevent);
		ASSERT_THAT(mptr[i]!=0);
		//cout<<mptr[i]<<endl;
	}
	
	
	
	
	delete ptr;
	//delete plisteners;
	delete [] str;
END_UNIT


TEST_SUITE(Registrar Unit Test)
	TEST(Registrar_Create_And_Subscribe_Few_Test)
	TEST(Registrar_Create_And_Subscribe_UnSubscribe_Many_Test)
	TEST(Registrar_UnSubscribe_Test)
	TEST(Registrar_Get_Subscribes_Test)
END_SUITE
