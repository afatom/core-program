#include <pthread.h>
#include <dlfcn.h>
#include <exception>      // std::exception
#include <assert.h>
#include <soloader.h>
#include <iagent.h>

//_soDirPath ex: /home/docs/proj/shared/soobjs

/**********************************************************************/
SoLoader_t::SoLoader_t(IRegistrar_t* _reg, IPublisher_t* _pub, const string& _soDirPath)
{
	m_pub = _pub; 
	m_reg = _reg;
	m_sopath = _soDirPath;
	m_soHandles = Handles_ShPtr(new map<const string,void*>);	//can throw bad alloc
}

/**********************************************************************/

IAgent_t* SoLoader_t::OpenedSoLoading(const AgentConfig_t& _config, void* _handle)
{
	IAgent_t* (*Create)(IPublisher_t*, IRegistrar_t*, const AgentConfig_t&);
	*(void**)(&Create) = dlsym(_handle, "Create");
	char* dlerrmsg=0;
	if((dlerrmsg = dlerror()))
	{
		cerr << "Cannot load symbols: " <<dlerrmsg<<endl;
		//throw exception maybe
		return 0;
	}
	
	IAgent_t* iaptr = (*Create)(m_pub, m_reg, _config);
	assert(iaptr != 0);
	
	return iaptr;		
}

/**********************************************************************/

IAgent_t* SoLoader_t::ClosedSoLoading(const AgentConfig_t& _config)
{
	string currentSo = m_sopath + '/' + _config.GetType() + ".so";
	void* handle = dlopen(currentSo.c_str(), RTLD_LAZY);
	if (!handle) 
	{
		cerr << "Cannot load library: " << dlerror() << '\n';
		//throw exception maybe
		return 0;
	}
	
	(*m_soHandles).insert(std::pair<const string,void*>(_config.GetType() ,handle) );
	return OpenedSoLoading(_config, handle);
}

/**********************************************************************/


IAgent_t* SoLoader_t::LoadAgent(const AgentConfig_t& _config)
{
	std::map<const string,void*>::iterator it;
	it = m_soHandles->find(_config.GetType());
	
	if (it != m_soHandles->end()) //founded .so string. already opened so
	{
		return OpenedSoLoading(_config, it->second);
	}
	
	return ClosedSoLoading(_config); 
}

/**********************************************************************/
SoLoader_t::~SoLoader_t()
{
	std::map<const string,void*>::iterator itb = (*m_soHandles).begin();
	std::map<const string,void*>::iterator ite = (*m_soHandles).end();
	while(itb != ite)
	{
		dlclose(itb->second);
		++itb;
	}
	
}
/**********************************************************************/
