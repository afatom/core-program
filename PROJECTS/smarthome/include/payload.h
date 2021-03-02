#ifndef __PAYLOAD_T_H_
#define __PAYLOAD_T_H_

#include <string>
#include <iostream>

using namespace std;

class Payload_t{
	private:
	string m_deviceId;
	
	public:
	Payload_t(){m_deviceId = " ";}
	Payload_t(const string& _id){m_deviceId = _id;}
	Payload_t(const char* _id){m_deviceId = _id;}
	
	const string& GetDeviceId() const {return m_deviceId;}
	Payload_t(const Payload_t& _payload){m_deviceId = _payload.GetDeviceId();}
	Payload_t& operator = (const Payload_t& _payload) {this->m_deviceId = _payload.GetDeviceId(); return *this;}
	virtual ~Payload_t(){};

	
	};

/*
ostream& operator << (ostream& _os, const Payload_t& _payload)
{
	_os <<"Device ID: "<< _payload.GetDeviceId();
	return _os;
}*/

#endif //__PAYLOAD_T_H_
