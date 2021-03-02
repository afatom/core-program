#ifndef __PUBLISHER_T_H_
#define __PUBLISHER_T_H_

#include <wtqueue.h>
#include <iostream>
#include <ipublisher.h>
#include <nevent.h>
using namespace std;


class Publisher_t : public IPublisher_t{
	private:
	Publisher_t(const Publisher_t&);
	Publisher_t& operator = (const Publisher_t&);
	WtQueue_t<Event_ShPointer>* m_queue;

	
	
	public:
	Publisher_t();

	Publisher_t(WtQueue_t<Event_ShPointer>* _ptr){m_queue = _ptr;}
	
	~Publisher_t(){}

	virtual void Publish(Event_ShPointer _event);
	
	};



#endif //__PUBLISHER_T_H_
