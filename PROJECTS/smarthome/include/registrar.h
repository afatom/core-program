#ifndef __REGISTRAR_T_H_
#define __REGISTRAR_T_H_

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
class Registrar_t : public IRegistrar_t{
	
	private:
	pthread_mutex_t m_mutex;
	map<const string, vector<Ilistener_t*> >* m_map;
	Registrar_t(const Registrar_t&);
	Registrar_t& operator = (const Registrar_t&);
	
	public:
	Registrar_t();
	~Registrar_t();
	virtual void Subscribe(Ilistener_t*, const string&);
	virtual void UnSubscribe(Ilistener_t*, const string&);
	virtual vector<Ilistener_t*>& GetSubscribers(const string&);
	virtual size_t GetSubscribersNum() ;
	size_t GetSubscribersOnType(const string&) ;
	};



#endif //__REGISTRAR_T_H_	









