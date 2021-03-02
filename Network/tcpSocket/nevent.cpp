#include <nevent.h>
#include <iostream>

using std::cout;
using std::endl;

std::ostream& operator<< (std::ostream& _os, const Event_t& _event) 
{
    struct tm * timeinfo;
    timeinfo = localtime(&(_event.GetTime()));
    _os << "Time: "<<asctime(timeinfo);
    _os << "Type: "<<_event.GetType()<<endl;
    _os << "Location: "<<_event.GetLocation()<<endl;
    return _os;
}


Event_t::Event_t() : m_timestamp(time(0)), m_type(" "), m_location(" "){}


Event_t::Event_t(const std::string& _type, const std::string& _location) 
: m_timestamp(time(0))
, m_type(_type)
, m_location(_location){}


Event_t::Event_t(const Event_t& _event)
{
    m_type = _event.m_type;
    m_location = _event.m_location;
    m_timestamp = _event.m_timestamp;
}


Event_t& Event_t::operator = (const Event_t& _event)
{
    if(this == &_event)
        return *this;

    m_type = _event.m_type;
    m_location = _event.m_location;
    m_timestamp = _event.m_timestamp;
    return *this;
}
