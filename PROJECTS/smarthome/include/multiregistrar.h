#ifndef __MULTI_REGISTRAR_T_H_
#define __MULTI_REGISTRAR_T_H_

#include <iterator>
#include <vector>
#include <map>
#include <ilistener.h>
#include <iostream>
#include <cstdlib>
#include <iregistrar.h>
#include <pthread.h>
using namespace std;




//template<typename T> //T=Key
//typedef map <string, map <string, map <string, vector <int*> > > > my_multimap;
typedef map<const string, map <const string, map <const string, vector <Ilistener_t*> > > > IlistenersContainer;

class MRegistrar_t : public MIRegistrar_t{
	
	private:
	pthread_mutex_t m_mutex;
	IlistenersContainer*  m_container;
	MRegistrar_t(const MRegistrar_t&);
	MRegistrar_t& operator = (const MRegistrar_t&);
	void SubscribeOnAllRooms(const string& _eventType, const string& _floor, Ilistener_t* _pListiner);
	void SubscribeOnAllFloors(const string& _eventType ,Ilistener_t* _pListiner);
	
	
	public:
	MRegistrar_t();
	~MRegistrar_t();
	virtual void Subscribe(Ilistener_t*, SubscribingSet&);
	//virtual void UnSubscribe(Ilistener_t*, SubscribingSet&);
	virtual map<Ilistener_t*,int>* GetSubscribers(SubscribingSet&); 
	//virtual size_t GetSubscribersNum() ;
	//size_t GetSubscribersOnTypeNum(const string&) ;
	};



#endif //__MULTI_REGISTRAR_T_H_	









