#ifndef __LG_CONTROL_T_H_
#define __LG_CONTROL_T_H_
#include <tr1/memory>

#include <pthread.h>
#include <ilistener.h>
#include <iagent.h>
#include <agentconfig.h>
class LgControl_t : public IAgent_t, public Ilistener_t{

private:
	string m_id;
	string m_type;
	string m_room;
	string m_floor;
	string m_log;
	string m_config;
	IRegistrar_t* m_registrar;
	
public:
	LgControl_t(IRegistrar_t*, AgentConfig_t&);
	~LgControl_t(){}
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
	//virtual void Update(const Event_t&);
	virtual void Update(std::tr1::shared_ptr<Event_t>);
	virtual void Run();
};

// the class factories
/*
extern "C" IAgent_t* Create(IPublisher_t* _pub, IRegistrar_t* _reg, AgentConfig_t& _config)
{
	cout<<"Lg Controll Create  "<<endl;
	return new LgControl_t(_reg, _config);
}

extern "C" void Destroy(IAgent_t* _agent)
{
	delete _agent;
}

extern "C" void RunSo(IAgent_t* _iagent)
{
	cout<<"Agent controll Run function"<<endl;
	_iagent->Run();
	cout<<"Agent controll Run function****** return** catastrophy"<<endl;
}
*/
#endif //__LG_CONTROL_T_H_
