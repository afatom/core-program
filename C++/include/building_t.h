#ifndef __BUILDING_T_H_
#define __BUILDING_T_H_

#include <iostream>

using namespace std;

template<class T>
class Building_t{
	public:
	Building_t(){}
	~Building_t(){}
	Building_t(T _buildingIdentity);
	Building_t& operator=(const Building_t& _buildingIdentity); //assignment operator
	void SetBuildingID(T& _buildingIdentity);
	const T& GetBuildingID()const;
	Building_t(const Building_t& _building);
	
	private:
	T m_buildingID;
	
	}; 
template<class T>
ostream& operator << (ostream& os, const Building_t<T>& _buildingIdentity)
{
	os <<"Building ID "<<_buildingIdentity.GetBuildingID()<<endl;
	return os;
}




template<class T>
void Building_t<T>::SetBuildingID(T& _buildingIdentity)
{
	this->m_buildingId = _buildingIdentity.m_buildingID;
}

template<class T>
const T& Building_t<T>::GetBuildingID()const
{
	return this->m_buildingID;
}

template<class T>
Building_t<T>::Building_t(T _buildingIdentity)
{
	this->m_buildingID = _buildingIdentity;
}

template<class T>

Building_t<T>& Building_t<T>::operator=(const Building_t& _buildingIdentity) //assignment operator
{
	this->m_buildingID = _buildingIdentity.m_buildingID;
	return *this; 
}

template<class T>
Building_t<T>::Building_t(const Building_t& _building)
{
	this->m_buildingID = _building.m_buildingID;
}









#endif //__BUILDING_T_H_
