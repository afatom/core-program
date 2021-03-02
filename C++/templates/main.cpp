
#include <iostream>
#include <string>

#include <city_t.h>

//#define STREET
#define CITY_TEST
using namespace std;
int main (void)
{
	#ifdef STREET
	Building_t<string> id7("sapir 7");
	
	Building_t<string> id1("sapir 1");
	Building_t<string> id2("sapir 2");
	Building_t<string> id3("sapir 3");
	Building_t<string> id4("sapir 4");
	Building_t<string> id5("sapir 5");
	Building_t<string> id6("sapir 6");
	
	Street_t<Building_t<string> , string> street1("Habokrem");
	street1.AddBuilding2Street(id1);//
	street1.AddBuilding2Street(id2);//
	street1.AddBuilding2Street(id3);//
	street1.AddBuilding2Street(id4);//
	street1.AddBuilding2Street(id5);//
	street1.AddBuilding2Street(id6);//
	street1.AddBuilding2Street(id7);//

	cout<<street1<<endl;
	string gal("Galele");
	street1.SetStreetID(gal);//
	
	
	Building_t<string> temp("A");
	cout<<street1.getBuilding(0)<<endl;
	
	
	cout<<street1<<endl;
	
	cout<<"Buildings Num "<<street1.GetBuildingsNum()<<endl;

	
	Street_t<string , string> street3("new");

	street3 = street1;
	
	
	Street_t<string , string> xx(street1);//
	cout<<street3<<endl;
	#endif
	
	Street_t<string , string> str("sokolov");
	cout<<str<<endl;
	
	
	#ifdef CITY_TEST
	City_t<string , string ,  string > city("NEW YORK");
	cout<<city<<endl;
	
	#endif
	
	
	
	return 0;
		
}
