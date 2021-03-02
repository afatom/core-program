#ifndef __AGENTS_BUILDER_T_H_
#define __AGENTS_BUILDER_T_H_

#include <vector>
#include <iagent.h>
#include <txtreader.h>
#include <string>

using namespace std;


struct AgentBuilderArg{
	IPublisher_t* m_pub;
	IRegistrar_t* m_reg;
	TxtReader_t* m_reader;
	char* m_soPath;
	};



class AgentsBuilder_t{
	private:
	vector<IAgent_t*>* m_vec;
	vector<void*>* m_handles;
	IPublisher_t* m_publisher;
	IRegistrar_t* m_registrar;
	TxtReader_t* m_reader;
	string m_sopath;
	//IAgent_t* LoadSoAgent(const string& _sofullpath, AgentConfig_t& _conf);
	
	
	
	public:
	AgentsBuilder_t(struct AgentBuilderArg*);
	~AgentsBuilder_t();
	void CreateSoAgents();
};

//typedef IAgent_t* Create(IPublisher_t* _pub, IRegistrar_t* _reg, AgentConfig_t& _config);
//typedef void ActivateSo(IAgent_t* _iagent);

#endif //__AGENTS_BUILDER_T_H_
