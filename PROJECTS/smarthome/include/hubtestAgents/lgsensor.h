#ifndef __LG_SENSOR_T_H_
#define __LG_SENSOR_T_H_

#include "iagent.h"
#include <pthread.h>
#include <agentconfig.h>
class LgSensor_t : public IAgent_t{

private:
	string m_id;
	string m_type;
	string m_room;
	string m_floor;
	string m_log;
	string m_config;
	IPublisher_t* m_publisher;
	
public:
	LgSensor_t(IPublisher_t*, AgentConfig_t&);
	~LgSensor_t(){}
	virtual void SetId(const string&);
	virtual void SetType(const string&);
	virtual void SetRoom(const string&);
	virtual void SetFloor(const string&);
	virtual void SetLog(const string&);
	virtual void SetConfig(const string&);

	virtual const string& GetId() const;
	virtual const string& GetType() const;
	virtual const string& GetRoom() const;
	virtual const string& GetFloor() const;
	virtual const string& GetLog() const;
	virtual const string& GetConfig() const;
	virtual void Run();

};

// the class factories

/*
extern "C" IAgent_t* Create(IPublisher_t* _pub, IRegistrar_t* _reg, AgentConfig_t& _config)
{
	return new LgSensor_t(_pub, _config);
}

extern "C" void Destroy(IAgent_t* _agent)
{
	delete _agent;
}

extern "C" void RunSo(IAgent_t* _iagent)
{
	cout<<"LG sensor: ____At My Run Function____: "<<endl;
	_iagent->Run();
	
}
*/
#endif //__LG_SENSOR_T_H_
