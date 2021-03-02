#ifndef __SETUP_T_H_
#define __SETUP_T_H_

#include <iregistrar.h>
#include <ipublisher.h>
#include <agentsFactory.h>

using namespace std;

class Setup_t{
	private:
	AgentsFactory_t* m_factory;
	static bool isPause;
	
	public:
	Setup_t(IPublisher_t* _ipub, IRegistrar_t* _ireg, const string& _soPath) {m_factory = new AgentsFactory_t(_ireg, _ipub, _soPath);} 
	//string as an abstract path to so dir
	~Setup_t() {delete m_factory;}
	void CreateAgents() {m_factory->BuildAgents();}
	void ActivateAgents() {m_factory->ActivateAgents();}
	static void Pause();
	static void Resume();	
};

#endif //SETUP
