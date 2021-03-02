#ifndef __CAR_T_H_
#define __CAR_T_H_

#include <stddef.h>
#include <string>

using namespace std;


typedef enum GearBox{
	AUTO = 0,
	MANUAL,
	ROBOTIC,
	DSG
	}GearBox;



class Car_t{
	
	public:
	//Car_t();
	Car_t(size_t _engineCapacity);
	Car_t(size_t _engineCapacity, int gearType);
	size_t CarGetID(void)const{return privateCarId;}
	int CarGetGearType(void)const{return carGear;}
	bool operator<(const Car_t& _car)const;
	bool Car_tCmp(const Car_t& _car)const;
	void CarSetName(const char* _name){carName.assign(_name);}
	const char* CarGetName(void){return carName.c_str();}
	Car_t(const Car_t& car); 	//copy CTOR
	//////////////////////////////////////////////
	protected:
	~Car_t(){return;} //nobody can create an car_t obj
	void CarSetGearType(int type);
	/////////////////////////////////////////////
	private:
	Car_t& operator = (const Car_t& _car);
	
	string carName;
	static size_t carID;
	size_t privateCarId;
	size_t engineCapacity;
	int carGear; //0=manual
	
	};



#endif //__CAR_T_H_
