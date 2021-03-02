#ifndef __MULTI_IREGISTRAR_T_H_
#define __MULTI_IREGISTRAR_T_H_

#include <ilistener.h>
#include <string>
#include <map>
#include <vector>
using namespace std;

//template<typename T> //T=Key



typedef struct SubscribingSet{
	string m_eventType;
	string m_floor;
	string m_room;
	}SubscribingSet;


class MIRegistrar_t{
	
	private:
	MIRegistrar_t(const MIRegistrar_t&);
	MIRegistrar_t& operator = (const MIRegistrar_t&);
	
	public:
	MIRegistrar_t(){}
	virtual ~MIRegistrar_t(){}
	virtual void Subscribe(Ilistener_t*, SubscribingSet&) = 0;
	//virtual void UnSubscribe(Ilistener_t*, SubscribingSet&) = 0;
	virtual map<Ilistener_t*,int>* GetSubscribers(SubscribingSet&)=0; 
	//virtual size_t GetSubscribersNum() = 0;
	
	};



#endif //__MULTI_IREGISTRAR_T_H_
