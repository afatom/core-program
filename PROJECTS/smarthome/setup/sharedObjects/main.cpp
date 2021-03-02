#include <iagent.h>
#include <nevent.h>
#include <payload.h>
#include <iostream>
#include <dlfcn.h>
#include <publisher.h>
#include <registrar.h>
#include <wtqueue.h>
#include <iostream>
#include <ipublisher.h>
#include <nevent.h>
#include <pthread.h>
#include <agentconfig.h>
#include <hub.h>

using namespace std;

typedef IAgent_t* Create(IPublisher_t* _pub, IRegistrar_t* _reg, AgentConfig_t& _config);
typedef void Destroy(IAgent_t* _agent);
int main()
{
	
	//void* lgSenPtr = dlopen("./LgHuelight-1-a-1.so", RTLD_LAZY);
	//void* lgConPtr = dlopen("./LgHuelight-1-a-2.so", RTLD_LAZY);

	char lgsenpath[] =  "/home/adhamfaris/work/PROJECTS/smarthome/setup/soLoader/so_agents/LgHuelight-1-a-1.so";
	char lgconpath[] =  "/home/adhamfaris/work/PROJECTS/smarthome/setup/soLoader/so_agents/LgHuelight-1-a-2.so";

	void* lgSenPtr = dlopen(lgsenpath, RTLD_LAZY);
	void* lgConPtr = dlopen(lgconpath, RTLD_LAZY);


	if (!lgSenPtr || !lgConPtr) {
	cerr << "Cannot load library: " << dlerror() << '\n';
	return 1;
	} 

	
	Create* create_iagent = (Create*)dlsym(lgSenPtr, "Create");
	char* dlerrmsg=0;
	if((dlerrmsg = dlerror()))
	{
		cerr << "Cannot load symbols: " <<dlerrmsg<<endl;
		return 1;
	}
	Create* create_con_iagent = (Create*)dlsym(lgConPtr, "Create");
	if((dlerrmsg = dlerror()))
	{
		cerr << "Cannot load symbols: " <<dlerrmsg<<endl;
		return 1;
	}
	Destroy* dest_iagent = (Destroy*)dlsym(lgSenPtr, "Destroy");
	if((dlerrmsg = dlerror()))
	{
		cerr << "Cannot load symbols: " <<dlerrmsg<<endl;
		return 1;
	}
	Destroy* dest_iconagent = (Destroy*)dlsym(lgConPtr, "Destroy");
	if((dlerrmsg = dlerror()))
	{
		cerr << "Cannot load symbols: " <<dlerrmsg<<endl;
		return 1;
	}


/*
	if (!create_iagent || !create_con_iagent || !dest_iagent || !dest_iconagent) 
	{
		cerr << "Cannot load symbols: " << dlerror() << '\n';
		return 1;
	}*/

	Hub_t* hub = new Hub_t;

	Publisher_t* pub = hub->GetPublisher();
	Registrar_t* reg = hub->GetRegistrar();

	AgentConfig_t conf;

	string m_deviceId = "LgSens1xTr-Oppqw";
	string m_type = "Light";
	string m_floor = "1";
	string m_room = "1-a";
	string m_log = "Light";
	string m_config = "configure";
	string m_soName = "lg...so";
	
	//~AgentConfig_t{}
	conf.SetId(m_deviceId);
	conf.SetType(m_type);
	conf.SetFloor(m_floor);
	conf.SetRoom(m_room);
	conf.SetLog(m_log);
	conf.SetConfig(m_config);
	conf.SetSoName(m_soName);


	IAgent_t* iaptr = create_iagent(pub, reg, conf);
	m_deviceId = "LgSens1xTr-OpqrrXXXop";
	conf.SetId(m_deviceId);
	IAgent_t* icptr = create_con_iagent(pub, reg, conf);
		

	cout<<iaptr->GetId()<<endl;
	cout<<iaptr->GetType()<<endl;
	cout<<iaptr->GetRoom()<<endl;
	cout<<iaptr->GetFloor()<<endl;
	cout<<iaptr->GetLog()<<endl;
	cout<<iaptr->GetConfig()<<endl;

	cout<<icptr->GetId()<<endl;
	cout<<icptr->GetType()<<endl;
	cout<<icptr->GetRoom()<<endl;
	cout<<icptr->GetFloor()<<endl;
	cout<<icptr->GetLog()<<endl;
	cout<<icptr->GetConfig()<<endl;

	// use the class
	//destroy_cperson(pperson);
	// unload the triangle library
	dest_iagent(iaptr);
	//iaptr->Run();
	//Event_t _event;
	//icptr->Update()
	dest_iconagent(icptr);

	
	dlclose(lgSenPtr);
	dlclose(lgConPtr);

return 0;
}

