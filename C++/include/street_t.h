#ifndef __STREET_T_H_
#define __STREET_T_H_

#include <iostream>
#include <vector>
#include <building_t.h>

using namespace std;

template<class T, class T2>
class Street_t{
	
	public:
	Street_t();//
	Street_t(const T2& _streetID);//

	
	~Street_t(){}//
	Street_t(const Street_t& _street);//
	Street_t& operator =(const Street_t& _street);
	void SetStreetID(T2& _streetID);//
	const T2& GetStreeID()const;//
	void AddBuilding2Street(const T& _newBuilding);//
	const Building_t<T>& getBuilding(int _index)const;//
	size_t GetBuildingsNum()const;//
	
	protected:
	
	
	private:
	vector< Building_t<T> > container;
	T2 m_streetID;	
	};
//setStreetID and getStreetID¸ AddBuilding2Street, getBuilding


#endif //__STREET_T_H_



template<class T, class T2>
Street_t<T, T2>::Street_t(const T2& _streetID):m_streetID(_streetID)
{ }

/*
template<class T, class T2>
Street_t<T, T2>::Street_t(T& _building)
{
	container.insert(container.end(), _building);
}

*/

template<class T, class T2>
void Street_t< T, T2>::SetStreetID(T2& _streetID)
{
	this->m_streetID = _streetID;
}

template<class T, class T2>
const T2& Street_t<T,  T2>::GetStreeID()const
{
	return this->m_streetID;
}


template<class T, class T2>
void Street_t<T, T2>::AddBuilding2Street(const T& _newBuilding)
{
	container.insert(container.end(), _newBuilding);
		
}

template<class T, class T2>
size_t Street_t< T, T2>::GetBuildingsNum()const
{
	return container.size();
}


template<class T, class T2>
ostream& operator << (ostream& os, const Street_t<T, T2>& _street)
{
	os << "Street ID "<<_street.GetStreeID()<<endl;
	
	for (size_t i=0; i < _street.GetBuildingsNum(); ++i)
	{
		os <<"Building At "<< i <<" "<< _street.getBuilding((int)i)<<endl;
	}
	
	return os;
}


template<class T, class T2>
Street_t< T,  T2>::Street_t(const Street_t& _street):container(_street.container)
{
	//	container(_street.container);
}



template<class T, class T2>
Street_t< T,  T2>& Street_t< T, T2>::operator =(const Street_t& _street)
{
	this->container = _street.container;
	return *this;
}


template<class T, class T2>
const Building_t<T>& Street_t< T, T2>::getBuilding(int _index)const
{
	return (this->container[(size_t)_index]);
}

