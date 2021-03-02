#ifndef __CITY_T_H_
#define __CITY_T_H_

#include <iostream>
#include <vector>
#include <building_t.h>
#include <street_t.h>

using namespace std;

template<class T, class T2, class T3>
class City_t{
	public:
	City_t(){}
	City_t(const T3& _cityIdentity);//
	~City_t(){}//
	
	City_t(const City_t& _city);//
	City_t& operator =(const City_t& _city);
	void SetCityIdentity(T3& _cityID);//
	const T3& GetCityIdentity()const;//
	void AddNewStreet(const T2& _newStreet);//
	const Street_t<T,T2>& GetStreet(size_t _index)const;//
	size_t GetStreetsNum()const;//
	
	protected:
	
	
	private:
	vector< Street_t<T,T2> > container;
	T3 m_cityID;
	};


#endif //__CITY_T_H_

template<class T, class T2, class T3>
City_t<T, T2, T3>::City_t(const T3& _city):m_cityID(_city)
{}

template<class T, class T2, class T3>
City_t<T, T2, T3>::City_t(const City_t& _cityIdentity):container(_cityIdentity.container)
{}

template<class T, class T2, class T3>
City_t<T, T2, T3>& City_t<T, T2, T3>::operator =(const City_t& _city)
{
	this->container = _city.container;
	return *this;
}



template<class T, class T2, class T3>
void City_t<T, T2, T3>::SetCityIdentity(T3& _cityID)
{
	this->m_cityID = _cityID;
}

template<class T, class T2, class T3>
const T3& City_t<T, T2, T3>::GetCityIdentity()const
{
	return m_cityID;
}

template<class T, class T2, class T3>
void City_t<T, T2, T3>::AddNewStreet(const T2& _newStreet)
{
	container.insert(container.end(), _newStreet);
}

template<class T, class T2, class T3>
size_t City_t<T, T2, T3>::GetStreetsNum()const
{
	return container.size();
}

template<class T, class T2, class T3>
const Street_t<T,T2>& City_t<T, T2, T3>::GetStreet(size_t _index)const
{
	return (this->container[(size_t)_index]);
}


template<class T, class T2, class T3>
ostream& operator << (ostream& os, const City_t<T, T2, T3>& _city)
{
	os << "City Identity:"<<_city.GetCityIdentity();
	os<<"*****************************************************"<<endl;
	for (size_t i=0; i < _city.GetStreetsNum(); ++i)
	{
		os <<"Street Identity:"<< _city.GetStreet(i)<<endl;
	}
	
	return os;
}



