#ifndef __NEVENT_T_H_
#define __NEVENT_T_H_

#include <ctime>
#include <tr1/memory>
#include <string>
#include <iostream>
#include <payload.h>

using std::cout;

class Event_t{
    private:
    time_t m_timestamp;
    string m_type;
    string m_location;
    Payload_t m_payload;

    public:
    Event_t();
    Event_t(const string&, const string&, const Payload_t&);
    ~Event_t(){}
    Event_t(const Event_t& _event);
    Event_t& operator = (const Event_t& _event);
    const string& GetType() const{return m_type;}
    const string& GetLocation() const{return m_location;}
    const Payload_t& GetPayLoadData() const{return m_payload;}
    const time_t& GetTime() const{return m_timestamp;}
    void SetType(const string& _type){m_type = _type;}
    void SetLocation(const string& _location){m_location = _location;}
    void SetPayLoadData(const Payload_t& _payload){m_payload = _payload;}

};
ostream& operator<< (ostream& _os, const Event_t& _event); 

typedef std::tr1::shared_ptr<Event_t> Event_ShPointer; 
#endif //__NEVENT_T_H_


