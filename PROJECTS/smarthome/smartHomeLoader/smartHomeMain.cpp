#include <smartHome.h>
#include <string>


using namespace std;





int main(void)
{
	string sopath = "/home/adhamfaris/work/PROJECTS/smarthome/setup/sharedObjects";
	SmartHome_t* smh = new SmartHome_t(sopath);
	smh->RunSmartHome();
	delete smh;
	return 0;
}
