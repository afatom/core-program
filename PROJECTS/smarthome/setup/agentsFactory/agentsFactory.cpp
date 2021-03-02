#include <agentsFactory.h>
#include <pthread.h>
#include <control.h>
#include <assert.h>
#include <cstdlib>

AgentsFactory_t::AgentsFactory_t(IRegistrar_t* _reg, IPublisher_t* _pub, const string& _soDirPath) //string as SO Dir path
{
	string config = _soDirPath + '/' + "config.txt";
	m_reader = new TxtReader_t(config.c_str());
	m_vec = new vector<IAgent_t*>;
	m_soloader = new SoLoader_t(_reg, _pub, _soDirPath); 
}	
	
AgentsFactory_t::~AgentsFactory_t()
{
	delete m_reader;
	delete m_vec;
	delete m_soloader; 
}


void AgentsFactory_t::BuildAgents()
{
	for(;;)
	//for(int i=0;i<1;++i)
	{
		AgentConfig_t config = m_reader->ReadSingleConfigSet();

		if(config.GetId() == "0") //eof have been reached
		{	
			return;
		}
		
		IAgent_t* pAgent = m_soloader->LoadAgent(config);
		assert(pAgent != 0);
		this->m_vec->push_back(pAgent);
	}
}


void* ActivatorThread(void* ptr)
{
	IAgent_t* pagent = (IAgent_t*)ptr;
	pagent->Run();
	return 0;
}

void AgentsFactory_t::ActivateAgents()
{
	size_t size = m_vec->size();
	for(size_t j = 0; j < size; ++j)
	{
		pthread_t activatorthread;
		pthread_create(&activatorthread, 0, ActivatorThread, (*m_vec)[j]);
	}
}

