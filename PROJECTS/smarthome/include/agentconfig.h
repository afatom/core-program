#ifndef __AGENT_CONFIG_T_H_
#define __AGENT_CONFIG_T_H_

#include <string>
//#include "iagent.h"

#include <iagent.h>
#include <iostream>

using namespace std;

struct AgentInit{
	string m_deviceId;
	string m_type;
	string m_floor;
	string m_room;
	string m_log;
	string m_config;
	string m_soName;
};


class AgentConfig_t : public IAgent_t{
	
	private:
	string m_deviceId;
	string m_type;
	string m_floor;
	string m_room;
	string m_log;
	string m_config;
	string m_soName;
	
	public:
	AgentConfig_t();
	AgentConfig_t(struct AgentInit*);
	
	//~AgentConfig_t{}
	virtual void SetId(const string& _id) {m_deviceId = _id;}
	virtual void SetType(const string& _type) {m_type = _type;}
	virtual void SetRoom(const string& _room) {m_room = _room;}
	virtual void SetFloor(const string& _floor) {m_floor = _floor;}
	virtual void SetLog(const string& _log) {m_log = _log;}
	virtual void SetConfig(const string& _config) {m_config = _config;}
	void SetSoName(const string& _so) {m_soName = _so;}

	virtual const string& GetId() const {return m_deviceId;}
	virtual const string& GetType() const {return m_type;}
	virtual const string& GetRoom() const {return m_room;}
	virtual const string& GetFloor() const {return m_floor;}
	virtual const string& GetLog() const {return m_log;}
	virtual const string& GetConfig() const {return m_config;}
	virtual void Run(){}
	const string& GetSoName() const {return m_soName;}
	};


ostream& operator << (ostream& os, const AgentConfig_t& conf);
#endif //__AGENT_CONFIG_T_H_
