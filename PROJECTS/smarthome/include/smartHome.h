#ifndef __SMART_HOME_T_H_
#define __SMART_HOME_T_H_


#include <agentsFactory.h>
#include <hub.h>
#include <setup.h>

//using namespace std;

class SmartHome_t{
	private:
	Hub_t* m_hub;
	Setup_t* m_setup;
	void LoadSmartHomeResources() {this->m_setup->CreateAgents();}
	
	
	public:
	SmartHome_t(const string& _soFullPath);
	~SmartHome_t();
	void RunSmartHome();
	//void ShutDownSmartHome(){}
};

#endif //__SMART_HOME_T_H_
