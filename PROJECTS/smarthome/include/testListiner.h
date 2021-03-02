
#ifndef __TESTLISTINER_T_H_
#define __TESTLISTINER_T_H_

#include <nevent.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <ilistener.h>
using namespace std;

class Testlistener_t : public Ilistener_t{	
	private:
	
	public:
	Testlistener_t(){}
	~Testlistener_t(){}
	//virtual void Update(const Event_t&);
	virtual void Update(std::tr1::shared_ptr<Event_t> _pevent){cout<< *_pevent <<endl;}
	};
	
#endif //__TESTLISTINER_T_H_



