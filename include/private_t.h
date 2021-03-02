#ifndef __PRIVATE_T_H_
#define __PRIVATE_T_H_

#include "car_t.h"
#include <iostream>
#include <string>

class Private_t:public Car_t{
	
	public:
	Private_t();
	Private_t(size_t _engineCapacity, int gearType);
	Private_t(size_t _engineCapacity);
	~Private_t();
	void IncreaseSpeed(void){m_currentSpeed+=10;}
	void ReduceSpeed(void);
	size_t GetSpeed(void)const{return m_currentSpeed;}
	size_t GetHorsePower(void)const{return m_horsePower;}
	const char* GetModel(void)const{return this->m_model.c_str();}
	void SetModel(const char* _model){this->m_model.assign(_model);}
	Private_t(const Private_t& _private); 	//copy CTOR
	protected:
	
	private:
	size_t m_currentSpeed; //Kph
	size_t m_horsePower;
	string m_model;
	
	Private_t& operator = (const Private_t& _car);
	};
	ostream& operator<<(ostream& os, const Private_t& _car);

#endif //__PRIVATE_T_H_ 
