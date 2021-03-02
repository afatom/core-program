#ifndef __ILISTENER_T_H_
#define __ILISTENER_T_H_
#include <tr1/memory>
#include <nevent.h>
using namespace std;

//template <typename Event>
class Ilistener_t{
	private:
	Ilistener_t(const Ilistener_t&);
	Ilistener_t& operator = (const Ilistener_t&);
	
	public:
	Ilistener_t(){}
	virtual ~Ilistener_t(){}
	//virtual void Update(const Event_t&)=0;
	virtual void Update(std::tr1::shared_ptr<Event_t>)=0;
	
	};

typedef std::tr1::shared_ptr<Ilistener_t> Ilistener_ShPointer; 
#endif //__ILISTENER_T_H_
