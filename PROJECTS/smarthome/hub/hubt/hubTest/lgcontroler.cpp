#include <lgcontroler.h>
#include <tr1/memory>

void LgControl_t::SetId(const string& _id) {m_id = _id;}
void LgControl_t::SetType(const string& _type) {m_type = _type;}
void LgControl_t::SetRoom(const string& _room) {m_room = _room;}
void LgControl_t::SetFloor(const string& _floor) {m_floor = _floor;}
void LgControl_t::SetLog(const string& _log) {m_log = _log;}
void LgControl_t::SetConfig(const string& _conf) {m_config = _conf;}

const string& LgControl_t::GetId() const {return m_id;}
const string& LgControl_t::GetType() const {return m_type;}
const string& LgControl_t::GetRoom() const {return m_room;}
const string& LgControl_t::GetFloor() const {return m_floor;}
const string& LgControl_t::GetLog() const {return m_log;}
const string& LgControl_t::GetConfig() const {return m_config;}

LgControl_t::LgControl_t(IRegistrar_t* _reg, AgentConfig_t& _lgControlConfig)
{
	m_id = _lgControlConfig.GetId();
	m_type = _lgControlConfig.GetType();
	m_room = _lgControlConfig.GetRoom();
	m_floor = _lgControlConfig.GetFloor();
	m_log = _lgControlConfig.GetLog();
	m_config = _lgControlConfig.GetConfig();
	m_registrar = _reg;
}



/*
void LgControl_t::Update(const Event_t& _event)
{
	cout<<"LgController Received Event Bellow"<<endl;
	cout<<_event<<endl;
}*/


void LgControl_t::Update(std::tr1::shared_ptr<Event_t> _pevent)
{
	cout<<"___________________LgController Received Event Bellow__________________________________*#"<<endl;
	cout<<*_pevent<<endl;
}


void LgControl_t::Run()
{
	//Ilistener_ShPointer this_ShPointer(this); //bad error
	cout << "LgControl_t::Run _____________________________________________line 49 lg con"<<endl;
	m_registrar->Subscribe(this, m_type);
	cout<<"Cont Type::" <<m_type<<endl;
	cout << "LgControl_t::Subscribed successfully _________________________"<<endl;
	
}
