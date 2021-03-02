#ifndef __IREGISTRAR_T_H_
#define __IREGISTRAR_T_H_

#include <ilistener.h>

#include <vector>
using namespace std;

//template<typename T> //T=Key
class IRegistrar_t{
	
	private:
	IRegistrar_t(const IRegistrar_t&);
	IRegistrar_t& operator = (const IRegistrar_t&);
	
	public:
	IRegistrar_t(){}
	virtual ~IRegistrar_t(){}
	virtual void Subscribe(Ilistener_t*, const string&)=0;
	virtual void UnSubscribe(Ilistener_t*, const string&)=0;
	virtual vector<Ilistener_t*>& GetSubscribers(const string&)  =0;
	virtual size_t GetSubscribersNum()  = 0;
	
	};



#endif //__IREGISTRAR_T_H_
