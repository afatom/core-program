#include "car_t.h"
#include <string>
#include <iostream>
#include "bus_t.h"



int main (void)
{
	BusArgs args;
	args.m_engineCapacity = 8192;
	args.m_gearType = 1;
	args.m_seatsNum = 32;
	args.m_lineNumber = 16;
	
	Bus_t bus1(args);
	
	cout<<bus1;
	
	Bus_t bus2;
	cout<<bus2;
	
	Bus_t bus3(4096, 1);
	Bus_t bus4(4096);
	
	cout<<bus3; 
	cout<<bus4;
	
	cout<<"bus3 speed "<<bus3.GetSpeed()<<endl;
	cout<<"bus4 speed "<<bus4.GetSpeed()<<endl;
	
	cout<<"Bus3 seats num "<<bus3.GetSeatsNum()<<endl;
	cout<<"Bus1 seats num "<<bus1.GetSeatsNum()<<endl;
	
	bus1.ReduceSpeed();
	cout<<bus1;
	bus1.IncreaseSpeed();
	cout<<bus1<<endl;
	bus1.IncreaseSpeed();
	cout<<bus1<<endl;
	
	Bus_t& ir = bus1; 
	Bus_t bus9(ir); 	//copy CTOR
	
	cout<<"bus9:"<<bus9<<endl;
	return 0;
}
