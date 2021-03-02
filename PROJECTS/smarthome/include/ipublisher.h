#ifndef __IPUBLISHER_T_H_
#define __IPUBLISHER_T_H_

#include <nevent.h>

using namespace std;

//template<typename T>      later :-)
class IPublisher_t{
	
	private:
	IPublisher_t(const IPublisher_t&);
	IPublisher_t& operator = (const IPublisher_t&);
	
	
	public:
	IPublisher_t(){}
	virtual ~IPublisher_t(){}
	virtual void Publish(Event_ShPointer _event)=0;
	};

#endif //__IPUBLISHER_T_H_
