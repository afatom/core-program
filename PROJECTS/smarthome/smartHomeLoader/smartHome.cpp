#include <smartHome.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
SmartHome_t::SmartHome_t(const string& _soFullPath)
{
	m_hub = new Hub_t;
	m_setup = new Setup_t(m_hub->GetPublisher(), m_hub->GetRegistrar(),_soFullPath);
}

SmartHome_t::~SmartHome_t()
{
	delete m_hub;
	m_hub=0;
	delete m_setup;
	m_setup=0;
	
}


void* threadfunc1(void* ptr)
{
	Setup_t* set = static_cast<Setup_t*>(ptr);
	set->ActivateAgents();
	return 0;
}


void* threadfunc2(void* ptr)
{
	Hub_t* hub = (Hub_t*)ptr;
	hub->Activate();
	return 0;
}





void SmartHome_t::RunSmartHome()
{
	this->LoadSmartHomeResources();
	pthread_t set;
	pthread_t act;
	
	pthread_create(&set, 0, threadfunc1, m_setup);
	pthread_create(&act, 0, threadfunc2, m_hub);
	assert(pthread_join(set, 0)==0);
	assert(pthread_join(act, 0)==0);
	
}
