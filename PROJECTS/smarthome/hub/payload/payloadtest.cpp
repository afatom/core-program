#include <string>
#include <iostream>
#include <lg_payload.h>
#include <nevent.h>

using namespace std;



int main ()
{
	string _id("03815554266987");
	string _ver("03.85XX");
	
	Lg_Payload_t device(_id, _ver);
	cout<<device<<endl;
	
	
	string type("FIRE");
	string location("FLOOR 1");
	
	
	Event_t t(type, location, device);
	cout<<t<<endl;
	
	return 0;
}
