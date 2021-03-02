#include <agentsBuilder.h>
#include <cstdlib>
#include <dlfcn.h>
#include <pthread.h>
#include <assert.h>
#include <iagent.h>
#include <unistd.h>


AgentsBuilder_t::AgentsBuilder_t(struct AgentBuilderArg* _arg)
{
	m_vec = new vector<IAgent_t*>; 
	m_handles = new vector<void*>;
	m_publisher = _arg->m_pub;
	m_registrar = _arg->m_reg;
	m_reader = _arg->m_reader;
	m_sopath = _arg->m_soPath;
	size_t pos = m_sopath.find_last_of('/');
    string str = m_sopath.substr(0,pos);  
    m_sopath = str;
}



AgentsBuilder_t::~AgentsBuilder_t()
{
	for(size_t i = 0; i < m_vec->size(); ++i)
	{
		delete((*m_vec)[i]); //delete iagents*
		dlclose((*m_handles)[i]);
	}
	delete m_vec;
	delete m_handles;
	m_vec=0;
	m_handles=0;
}


struct Creator{
	string m_sofullpath;
	AgentConfig_t m_conf;
	vector<void*>* m_handlesVec;
	vector<IAgent_t*>* m_agentsVec; 
	IPublisher_t* m_pub; 
	IRegistrar_t* m_reg;
	
	};


struct Runner{
	IAgent_t* m_iaptr;
	void* m_handle;
	};



//extern "C" 
void* threadRunnerFunction(void* ptr)
{
	Runner* rptr = (Runner*)ptr;
	//temp->Run();
	
	//void ActivateSo(IAgent_t* _iagent)
	void (*RunSo)(IAgent_t*);
	
	*(void**)(&RunSo) = dlsym(rptr->m_handle, "RunSo");
	//cout<< " (&RunSo)  " <<(&RunSo)<<endl;
	char* dlerrmsg=0;
	if((dlerrmsg = dlerror()))
	{
		cerr << "Cannot load RunSo Function symbol: " <<dlerrmsg<<endl;
		//throw exception maybe
		cout<< " (&RunSo)  " <<(&RunSo)<<endl;
		return 0;
	}
	cout<<"thread Runner Function working.."<<endl;
	//cout<<Run_Agent<<endl;
	cout<<"Agent* that runs now.."<<rptr->m_iaptr<<endl;
	
	(*RunSo)(rptr->m_iaptr);
	return 0;
}

//extern "C" 
void* threadCreateFunction(void* ptr)
{
	Creator* cptr = (Creator*)ptr;

	void* handle = dlopen((cptr->m_sofullpath).c_str(), RTLD_LAZY);
	if (!handle) 
	{
		cerr << "Cannot load library: " << dlerror() << '\n';
		//throw exception maybe
		return 0;
	}
	
	cptr->m_handlesVec->push_back(handle);
	cout<<"handle :: "<<handle<<endl;
	cout<< cptr->m_handlesVec->size()<<endl;
	
	
	IAgent_t* (*Create)(IPublisher_t*, IRegistrar_t*, AgentConfig_t&);
	
	*(void**)(&Create) = dlsym(handle, "Create");
	
	
	//Create* create_iagent = (Create*)dlsym(handle, "Create");
	
	cout<<"create_iagent"<<(&Create)<<endl;
	
	char* dlerrmsg=0;
	if((dlerrmsg = dlerror()))
	{
		cerr << "Cannot load symbols: " <<dlerrmsg<<endl;
		//throw exception maybe
		return 0;
	}
	
	IAgent_t* iaptr = (*Create)(cptr->m_pub, cptr->m_reg, cptr->m_conf);
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"Created Agent Pointer "<<iaptr<<endl;
	cout<<"--------------------------------------------"<<endl;
	
	return (void*)iaptr;
}




void AgentsBuilder_t::CreateSoAgents()
{
	int i = 2;
	while(i)
	{	
		//cout<<"CreateSoAgents"<<endl;
		
		AgentConfig_t temp = m_reader->ReadSingleConfigSet();
		//cout<<temp<<endl;
		//cout<<"CreateSoAgents82"<<endl;
		if(temp.GetId() == "0") //eof have been reached
		{	
			//cout<<"CreateSoAgents84"<<endl;
			
			cout<<"EOF Reched"<<endl;
			return;
		}
		string sofullpath = this->m_sopath + '/' + temp.GetSoName();
		
		//cout<<"CreateSoAgents"<<endl;
		//cout<<this->m_sopath<<endl;
		
		//call function IAgent_t* agent = LoadDynamicAgent(soname, agentconfig);
		//push back vector
		//******************************************************************************//
		
		struct Creator creatorArgs;
		creatorArgs.m_sofullpath = sofullpath;
		creatorArgs.m_conf = temp;
		creatorArgs.m_handlesVec = this->m_handles;
		creatorArgs.m_pub = this->m_publisher;
		creatorArgs.m_reg = this->m_registrar;
		
		
		pthread_t creatorthread;
		pthread_create(&creatorthread, 0, threadCreateFunction, &creatorArgs);
		IAgent_t* retval;
		assert(pthread_join(creatorthread, (void**)(&retval))==0);
		
		
		cout<<"IAgent* = "<< retval <<endl;
		sleep(3);
		
		
		this->m_vec->push_back(retval);
		
		struct Runner runnerArgs;
		runnerArgs.m_iaptr = retval;
		size_t size = (*m_handles).size(); //error size retval = 0
		
		cout <<"CreateSoAgents -> size"<<size<<endl;
		
		runnerArgs.m_handle = (*m_handles).back(); //last handle
		

		pthread_t runthread;
		pthread_create(&runthread, 0, threadRunnerFunction, &runnerArgs);
		
		//**ADDED
		//assert(pthread_join(runthread, 0)==0);
		//**END
		
		
		cout<<"187 CreateSoAgents"<<endl;
		--i;
	}
}

