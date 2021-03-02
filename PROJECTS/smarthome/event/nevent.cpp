#include <nevent.h>
#include <iostream>

using std::cout;


ostream& operator<< (ostream& _os, const Event_t& _event) 
{
    struct tm * timeinfo;
    timeinfo = localtime(&(_event.GetTime()));
    _os << "Time: "<<asctime(timeinfo);
    _os << "Type: "<<_event.GetType()<<endl;
    _os << "Location: "<<_event.GetLocation()<<endl;
    _os <<"Device ID: "<< (_event.GetPayLoadData()).GetDeviceId();
    return _os;
}


Event_t::Event_t(){
	m_payload = " ";
    m_type = " ";
    m_location = " ";
    m_timestamp = time(0);
}


Event_t::Event_t(const string& _type, const string& _location, const Payload_t& _payload)
{
    m_type = _type;
    m_location = _location;
    m_timestamp = time(0);
    m_payload = _payload;
}


Event_t::Event_t(const Event_t& _event)
{
    m_type = _event.m_type;
    m_location = _event.m_location;
    m_timestamp = _event.m_timestamp;
    m_payload = _event.m_payload;
}


Event_t& Event_t::operator = (const Event_t& _event)
{
    if(this == &_event)
        return *this;

    m_type = _event.m_type;
    m_location = _event.m_location;
    m_timestamp = _event.m_timestamp;
    m_payload = _event.m_payload;
    return *this;
}
