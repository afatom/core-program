#include <car_t.h>
#include <string>
#include <iostream>
#include <bus_t.h>


#define DEF_LINE 11
#define DEF_SEAT 32



Bus_t::Bus_t(size_t _engineCapacity, int _gearType):Car_t(_engineCapacity, _gearType)
{
	m_seatsNum = DEF_SEAT; 
	m_lineNum = DEF_LINE;
	m_currentSpeed = 0;
	CarSetName("Bus");
}
Bus_t::Bus_t(size_t _engineCapacity):Car_t(_engineCapacity)
{
	m_seatsNum = DEF_SEAT; 
	m_lineNum = DEF_LINE;
	m_currentSpeed = 0;
	CarSetName("Bus");
}
/*
Bus_t::Bus_t(size_t _engineCapacity, int _gearType, const size_t _seatsNum, const size_t _lineNumber):Car_t(_engineCapacity, _gearType)
{
	m_seatsNum = _seatsNum; 
	m_lineNum = _lineNumber;
	CarSetName("Bus");
}*/

Bus_t::Bus_t(BusArgs _busArgs):Car_t(_busArgs.m_engineCapacity, _busArgs.m_gearType)
{
	m_seatsNum = _busArgs.m_seatsNum; 
	m_lineNum = _busArgs.m_lineNumber;
	m_currentSpeed = 0;
	CarSetName("Bus");
}



Bus_t::Bus_t():Car_t(6800, 0)
{
	m_seatsNum = DEF_SEAT; 
	m_lineNum = DEF_LINE;
	m_currentSpeed = 0;
	CarSetName("Bus");
	
}


Bus_t::Bus_t(const Bus_t& _bus):Car_t(_bus) 	//copy CTOR
{
	this->m_seatsNum = _bus.m_seatsNum; 
	this->m_lineNum = _bus.m_lineNum; 
	this->m_currentSpeed = _bus.m_currentSpeed;
	CarSetName("Bus");
}


void Bus_t::ReduceSpeed(void)
{

	if(!m_currentSpeed)
	{
		return;
	}
	m_currentSpeed-=10;
	return;
}

Bus_t::~Bus_t()
{
	return;
}


ostream& operator<<(ostream& os, const Bus_t& _bus)
{
	os<<"Bus LineNum: "<<_bus.GetLineNum()<<endl;
	os<<"Bus SeatsNum: "<<_bus.GetSeatsNum()<<endl;
	os<<"Bus GetSpeed: "<<_bus.GetSpeed()<<endl;

	return os;
}




