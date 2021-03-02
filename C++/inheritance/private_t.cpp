#include <car_t.h>
#include <stddef.h>
#include <private_t.h>
#include <iostream>

void Private_t::ReduceSpeed(void)
{

	if(!m_currentSpeed)
	{
		return;
	}
	m_currentSpeed-=10;
	return;
}


Private_t::Private_t(size_t _engineCapacity, int gearType):Car_t(_engineCapacity, gearType)
{
	m_currentSpeed = 0;
	m_horsePower = 102;
	this->SetModel("sosita");
	CarSetName("Private");
}


Private_t::Private_t(size_t _engineCapacity):Car_t(_engineCapacity, 0)
{
	m_currentSpeed = 0;
	m_horsePower = 102;
	this->SetModel("sosita");
	CarSetName("Private");
}


Private_t::Private_t():Car_t(1024, 0)
{
	m_currentSpeed = 0;
	m_horsePower = 102;
	this->SetModel("sosita");
	CarSetName("Private");
}


Private_t::~Private_t()
{
	return;
}

Private_t::Private_t(const Private_t& _private):Car_t(_private) 	//copy CTOR
{
	m_currentSpeed = _private.m_currentSpeed;
	m_horsePower = _private.m_currentSpeed;
	m_model = _private.m_model;
	CarSetName("Private");
}


ostream& operator<<(ostream& os, const Private_t& _car)
{
	os<<"Car Current Speed: "<<_car.GetSpeed()<<endl;
	os<<"Car Horse Power: "<<_car.GetHorsePower()<<endl;
	os<<"Car Model: "<<_car.GetModel()<<endl;
	
	return os;
}
