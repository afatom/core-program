#include <lgsensor.h>
#include <unistd.h>
#include <nevent.h>
#include <payload.h>
#include <tr1/memory>

LgSensor_t::LgSensor_t(IPublisher_t* _pub, AgentConfig_t& _lgSensorConfig)
{
	m_id = _lgSensorConfig.GetId();
	m_type = _lgSensorConfig.GetType();
	m_room = _lgSensorConfig.GetRoom();
	m_floor = _lgSensorConfig.GetFloor();
	m_log = _lgSensorConfig.GetLog();
	m_config = _lgSensorConfig.GetConfig();
	m_publisher = _pub;
}

void LgSensor_t::SetId(const string& _id) {m_id = _id;}
void LgSensor_t::SetType(const string& _type) {m_type = _type;}
void LgSensor_t::SetRoom(const string& _room) {m_room = _room;}
void LgSensor_t::SetFloor(const string& _floor) {m_floor = _floor;}
void LgSensor_t::SetLog(const string& _log) {m_log = _log;}
void LgSensor_t::SetConfig(const string& _conf) {m_config = _conf;}

const string& LgSensor_t::GetId() const {return m_id;}
const string& LgSensor_t::GetType() const {return m_type;}
const string& LgSensor_t::GetRoom() const {return m_room;}
const string& LgSensor_t::GetFloor() const {return m_floor;}
const string& LgSensor_t::GetLog() const {return m_log;}
const string& LgSensor_t::GetConfig() const {return m_config;}


/*
struct args{
	IPublisher_t* pub;
	string type;
	string id;
	string room;
	string floor;
};



extern "C" void* threadfunc (void* ptr)
{
	struct args* argptr = (struct args*)ptr;
	//IPublisher_t* pub = (IPublisher_t*)ptr;
	while(1)
	{
		//create event and publish it
		Event_ShPointer pEvent(new Event_t);
		pEvent->SetType(argptr->type);
		string location = "floor: ";
		location =location + argptr->floor + "room: " + argptr->room;  
		pEvent->SetLocation(location);
		Payload_t pload(argptr->id);
		argptr->pub->Publish(pEvent);
		sleep(2);
	}
	return 0;
} 

*/





void LgSensor_t::Run()
{
	//thread creation for sending lg_sensing events
	//m_sender
	/*
	struct args threadargs;
	threadargs.pub = m_publisher;
	threadargs.type = m_type;
	threadargs.id = m_id;
	threadargs.room = m_room;
	threadargs.floor = m_floor;

	pthread_t m_sender;
	pthread_create(&m_sender,0, threadfunc, &threadargs);
	pthread_join(m_sender, 0);*/
	while(true)
	{
		//create event and publish it
		Event_ShPointer pEvent(new Event_t);
		pEvent->SetType(m_type);
		string location = "floor: ";
		location =location + m_floor + "room: " + m_room;  
		pEvent->SetLocation(location);
		Payload_t pload(m_id);
		
		
		m_publisher->Publish(pEvent);
		
		
		sleep(4);
		
		cout<<"Lg Sensor is Publishing"<<endl;

	}
}
