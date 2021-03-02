#include <pthread.h>
#include <distributor.h>



Distributor_t::Distributor_t(WtQueue_t<Event_ShPointer>* _pWtqueue, IRegistrar_t* _pReg) : m_queue(_pWtqueue), m_reg(_pReg)
{
	if(pthread_mutex_init(&m_mutex, NULL) != 0)
    {
        //throw exception;
    }
}

Distributor_t::~Distributor_t()
{
	pthread_mutex_destroy(&m_mutex);
}


typedef struct threadArgs{
	WtQueue_t<Event_ShPointer>* pQueue;
	IRegistrar_t* pReg;
	}threadArgs;

//extern "C" 
void* ThreadFunction(void* args)
{
	WtQueue_t<Event_ShPointer>* queue = ((threadArgs*)args)->pQueue;
	IRegistrar_t* reg = ((threadArgs*)args)->pReg;
	
	while(true)
	{
		Event_ShPointer epop = queue->Popfront();
		const string type = epop->GetType();

		vector<Ilistener_t*> vec = reg->GetSubscribers(type);
		
		size_t size = vec.size();
		size_t i =0;
		while(i != size)
		{
			vec[i]->Update(epop); //change from *epop to epop	
			++i;
		}
		
	}
	return 0;
}

void Distributor_t::Disperse()
{
 
	pthread_t poper1;
	pthread_t poper2;
	//pthread_t poper3;
	//pthread_t poper4;
	threadArgs ptr;
	ptr.pQueue = m_queue;
	ptr.pReg = m_reg;
	
	
	pthread_create(&poper1, 0, ThreadFunction, &ptr);
	pthread_create(&poper2, 0, ThreadFunction, &ptr);
	//pthread_create(&poper3, 0, ThreadFunction, &ptr);
	//pthread_create(&poper4, 0, ThreadFunction, &ptr);
	pthread_join(poper1, 0);
	pthread_join(poper2, 0);
	//pthread_join(poper3, 0);
	//pthread_join(poper4, 0);
    
}
