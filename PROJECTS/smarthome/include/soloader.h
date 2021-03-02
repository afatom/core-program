#ifndef __SO_LOADER_T_H_
#define __SO_LOADER_T_H_

#include <agentconfig.h>
#include <string>
#include <iagent.h>
#include <map>
#include <tr1/memory>
#include <iregistrar.h>
#include <ipublisher.h>


using std::string;
using std::vector;

class SoLoader_t{
	private:
	IPublisher_t* m_pub; 
	IRegistrar_t* m_reg;
	string m_sopath;
	std::tr1::shared_ptr<map<const string,void*> > m_soHandles;		
	
	IAgent_t* OpenedSoLoading(const AgentConfig_t&, void*);
	IAgent_t* ClosedSoLoading(const AgentConfig_t&);
	
	SoLoader_t(const SoLoader_t&); 
	SoLoader_t& operator = (const SoLoader_t&);
	
	
	public:
	SoLoader_t(IRegistrar_t*,IPublisher_t*,const string&);
	~SoLoader_t();
	IAgent_t* LoadAgent(const AgentConfig_t&);
};

typedef std::tr1::shared_ptr<map<const string,void*> > Handles_ShPtr;
#endif //__SO_LOADER_T_H_
