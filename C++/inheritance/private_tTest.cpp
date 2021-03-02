#include "private_t.h"
#include <stddef.h>
#include "car_t.h"
#include "bus_t.h"

int main(void)
{
	Private_t p1;
	cout<<p1;
	Private_t p2(1200, 1);
	cout<<p2;
	Private_t p3(3200);
	cout<<p3;
	
	//inherated functions
	cout<<"car id: "<<p3.CarGetID()<<endl;
	cout<<"car id: "<<p2.CarGetID()<<endl;
	cout<<"car gear "<<p2.CarGetGearType()<<endl;
	cout<<"car name "<<p2.CarGetName()<<endl;
	
	const Car_t& ir = p1;
	
	bool flag = p1.operator < (ir);
	cout<<"flag "<<flag<<endl;
	
	flag = p1.Car_tCmp(ir);
	cout<<"flag "<<flag<<endl;
	
	return 0;
}


