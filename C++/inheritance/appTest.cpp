#include <iostream>
#include <car_t.h>
#include <bus_t.h>
#include <private_t.h>


using namespace std;

int main()
{
	int cont = 1;			// trigger to stop loop	
	unsigned int option;
	BusArgs args;
	args.m_engineCapacity = 8192;
	args.m_gearType = 1;
	args.m_seatsNum = 32;
	args.m_lineNumber = 16;

	Bus_t bus1(args);
	
	Private_t private1(1800, 0);
	//const Car_t& ir = bus1;
	
	
	while (cont) {
		cout << "\n Choose option: " << endl;
		cout << "1: Cout bus data " << endl;
		cout << "2: Cout private data " << endl;
		cout << "3: Increase speed to bus " << endl;
		cout << "4: Increase speed to car " << endl;
		cout << "5: Car Reduse speed " << endl;
		cout << "6: Bus Reduse speed " << endl;
		cout << "7: Cars Compare  " << endl;
		

		cin >>  option;
		switch (option) 
		{
			case 1:

					cout<<bus1<<endl;
					cout<<bus1<<endl;
					cout<<bus1<<endl;
					cout<<bus1<<endl;
					cout<<bus1<<endl;
					cout<<bus1<<endl;
					cout<<bus1<<endl;
					
					break;
				
				
			case 2:
			
					cout<<private1<<endl;			
					break;
			
				
			case 3:
				{	
					bus1.IncreaseSpeed();
					break;
				}
				
			case 4:
				{
					private1.IncreaseSpeed();			
					break;
				}
				
			case 5:
				{	
					private1.ReduceSpeed();
					break;
				}
				
			case 6:
				{
					bus1.ReduceSpeed();			
					break;
				}
			case 7:
				{
					//flag = p1.Car_tCmp(ir);	
					break;
				}
				
	
		
			default: cont = 0;	break;
		}
	}

	return 0;
}

