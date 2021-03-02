#include <car_t.h>
#include <string>
#include <iostream>
#include <string>


#define DEF_ENG_CAP 1024
#define DEF_CAR_GEAR 0 //manual
size_t Car_t::carID = 0;

using namespace std;

//CTOR from egine capacity
Car_t::Car_t(size_t _engineCapacity)
{
	size_t cap = _engineCapacity;
	if(!_engineCapacity)
	{
		cap = DEF_ENG_CAP;
	}
	 
	privateCarId = carID;
	++carID;
	engineCapacity = cap;
	carGear = DEF_CAR_GEAR;
	return;
}

//CTOR from egine capacity and gearType
Car_t::Car_t(size_t _engineCapacity, int gearType)
{
	size_t cap = _engineCapacity;
	int gear = gearType;
	
	if(!_engineCapacity)
	{
		cap = DEF_ENG_CAP;
	}
	
	if(gearType > 1 || gearType < 0)
	{
		gear = DEF_CAR_GEAR;
	}
	
	privateCarId = carID;
	++carID;
	engineCapacity = cap;
	carGear = gear;
	return;
}


void Car_t::CarSetGearType(int type)
{
	if(type > 1 || type < 0)
	{
		return;
	}
	
	carGear = type;
	return;
}


bool Car_t::operator<(const Car_t& _car)const
{
	return (engineCapacity < _car.engineCapacity) ? (true) : (false);
	
}

bool Car_t::Car_tCmp(const Car_t& _car)const
{
	return (carName.compare (_car.carName)==0) ? (true):(false);
}


Car_t::Car_t(const Car_t& car) 	//copy CTOR
{
	privateCarId = carID;
	++carID;
	carName = car.carName;
	engineCapacity = car.engineCapacity;
	carGear = car.carGear;
}

