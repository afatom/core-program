#ifndef __BUS_T_H_
#define __BUS_T_H_

#include "car_t.h"
#include <iostream>

typedef struct BusArgs {
	size_t m_engineCapacity;
	int m_gearType;
	size_t m_seatsNum;
	size_t m_lineNumber;
	}BusArgs;

class Bus_t:public Car_t{
	
	public:
	Bus_t();
	Bus_t(size_t _engineCapacity, int _gearType);
	Bus_t(size_t _engineCapacity);
	Bus_t(BusArgs _busArgs);
	
	//Bus_t(size_t _engineCapacity, int _gearType, const size_t _seatsNum, const size_t _lineNumber);
		
	~Bus_t();
	Bus_t(const Bus_t& _bus); 	//copy CTOR
	void IncreaseSpeed(void){m_currentSpeed+=10;}
	void ReduceSpeed(void);
	size_t GetSpeed(void)const{return m_currentSpeed;}
	const size_t GetSeatsNum(void)const{return m_seatsNum;}
	const size_t GetLineNum(void)const{return m_lineNum;}
	protected:
	
	private:
	size_t m_seatsNum; //
	size_t m_lineNum;
	size_t m_currentSpeed;
	Bus_t& operator = (const Bus_t& _car);
	};
	
	ostream& operator<<(ostream& os, const Bus_t& _bus);
	

#endif //__BUS_T_H_ 
