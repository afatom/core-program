#ifndef __HUB_T_H_
#define __HUB_T_H_

#include <tr1/memory>
#include <distributor.h>
#include <registrar.h>
#include <publisher.h>
#include <wtqueue.h>
#include <nevent.h>



class Hub_t
{
	private:
	Hub_t(const Hub_t&);
	Hub_t& operator = (const Hub_t&);	
	WtQueue_t<Event_ShPointer>* m_queue;
	Registrar_t* m_pPregistrar;
	Publisher_t* m_pPublisher;
	Distributor_t* m_pDistributer;
	
	
	public:
	Hub_t();
	//Hub_t(): m_queue(new WtQueue_t<Event_ShPointer>), m_pPublisher(new Publisher_t), m_pDistributer(new Distributor_t), m_pPregistrar(new Registrar_t){}
	~Hub_t();
	Publisher_t* GetPublisher() const {return m_pPublisher;}
	Registrar_t* GetRegistrar() const{return m_pPregistrar;}
	void Activate();
	
	//TEST Only
	Distributor_t* GetDestributor() const {return m_pDistributer;}
};

#endif //__HUB_T_H_
