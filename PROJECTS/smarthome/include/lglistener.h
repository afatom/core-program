
#ifndef __LGLISTINER_T_H_
#define __LGLISTINER_T_H_

#include <nevent.h>
#include <iostream>

using namespace std;


class LgListener_t : public Ilistener_t{
	
	private:
	
	
	public:
	LgListener_t(){}
	~LgListener_t(){}
	virtual void Update(const Event_t& _event){cout<<"LgListener_t Received new event:"<<endl<< _event<<endl;}
	
	};

#endif //__TESTLISTINER_T_H_



