#ifndef __NEVENT_T_H_
#define __NEVENT_T_H_

#include <ctime>
#include <tr1/memory>
#include <string>
#include <iostream>

using std::cout;

class Event_t{
    private:
    time_t m_timestamp;
    std::string m_type;
    std::string m_location;

    public:
    Event_t();
    Event_t(const std::string&, const std::string&);
    ~Event_t(){}
    Event_t(const Event_t& _event);
    Event_t& operator = (const Event_t& _event);
    const std::string& GetType() const{return m_type;}
    const std::string& GetLocation() const{return m_location;}
    const time_t& GetTime() const{return m_timestamp;}
    void SetType(const std::string& _type){m_type = _type;}
    void SetLocation(const std::string& _location){m_location = _location;}

};
std::ostream& operator<< (std::ostream& _os, const Event_t& _event); 

typedef std::tr1::shared_ptr<Event_t> Event_ShPointer; 
#endif //__NEVENT_T_H_


