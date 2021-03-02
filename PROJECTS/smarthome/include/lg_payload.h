#ifndef __LG_PAYLOAD_T_H_
#define __LG_PAYLOAD_T_H_

#include <payload.h>
#include <string>
#include <iostream>

using namespace std;

class Lg_Payload_t : public Payload_t{
	
	private:
	string m_ver;
	
	public:
	Lg_Payload_t(const string& _id, const string& _ver) : Payload_t(_id){ m_ver = _ver;}
	~Lg_Payload_t(){}
	const string& GetDeviceVer() const {return m_ver;}
	};


ostream& operator << (ostream& _os, const Lg_Payload_t& _payload)
{
	_os <<"Device ID: "<< _payload.GetDeviceId()<<endl;
	_os <<"Device Ver: "<< _payload.GetDeviceVer();
	return _os;
}


#endif //__LG_PAYLOAD_T_H_
