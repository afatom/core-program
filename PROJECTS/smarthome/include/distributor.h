#ifndef __DISTRIBUTOR_T_H_
#define __DISTRIBUTOR_T_H_


#include <wtqueue.h>
#include <tr1/memory>
#include <cstdlib>
#include <nevent.h>
#include <iregistrar.h>
#include <pthread.h>

using namespace std;

class Distributor_t{
	
	private:
	pthread_mutex_t m_mutex;
	Distributor_t& operator = (const Distributor_t&);
	Distributor_t(const Distributor_t&);
	WtQueue_t<Event_ShPointer>* m_queue;
	IRegistrar_t* m_reg;
	
	
	public:
	Distributor_t(WtQueue_t<Event_ShPointer>*, IRegistrar_t*);
	//Distributor_t(std::tr1::shared_ptr< WtQueue_t< std::tr1::shared_ptr<Event_t> >, IRegistrar_t*);
	
	~Distributor_t();
	void Disperse(); //distribute
	
	
	};

#endif //__DISTRIBUTOR_T_H_
