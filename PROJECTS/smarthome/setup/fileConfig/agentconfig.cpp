#include <agentconfig.h>

ostream& operator << (ostream& os, const AgentConfig_t& conf)
{
	os <<"ID: "<< conf.GetId()<<endl;
	os <<"Type: "<< conf.GetType()<<endl;
	os <<"Room: "<< conf.GetRoom()<<endl;
	os <<"floor: "<<conf.GetFloor()<<endl;
	os <<"Log: "<<conf.GetLog()<<endl;
	os <<"config: "<<conf.GetConfig();
	return os;
}


AgentConfig_t::AgentConfig_t()
{
	m_deviceId = " ";
	m_type = " ";
	m_floor = " ";
	m_room = " ";
	m_log = " ";
	m_config = " ";
}

AgentConfig_t::AgentConfig_t(struct AgentInit* _ptr)
{
	m_deviceId = _ptr->m_deviceId;
	m_type = _ptr->m_type;
	m_floor = _ptr->m_floor;
	m_log = _ptr->m_log;
	m_room = _ptr->m_room;
	m_config = _ptr->m_config;
}
	
