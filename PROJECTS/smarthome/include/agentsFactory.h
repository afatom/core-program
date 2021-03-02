#ifndef __AGENTS_FACTORY_T_H_
#define __AGENTS_FACTORY_T_H_

#include <iregistrar.h>
#include <ipublisher.h>
#include <agentconfig.h>
#include <txtreader.h>
#include <soloader.h>
#include <vector>
#include <pthread.h>

using std::string;
using std::vector;

class AgentsFactory_t{
	
	private:
	TxtReader_t* m_reader;
	vector<IAgent_t*>* m_vec;
	SoLoader_t* m_soloader; 
	AgentsFactory_t(const AgentsFactory_t&);
	AgentsFactory_t& operator = (const AgentsFactory_t&);
	
	
	public:
	AgentsFactory_t(IRegistrar_t*,IPublisher_t*, const string&); //string as SO Dir path
	~AgentsFactory_t();
	void BuildAgents();
	void ActivateAgents();
};





#endif //__AGENTS_FACTORY_T_H_
