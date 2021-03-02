#ifndef __TCONTAINER_T_H_
#define __TCONTAINER_T_H_

#include <iostream> //cout
#include <vector>
#include <list>
#include <typeinfo>
#include <algorithm> //stl

using namespace std;


template<typename T, typename container>
class tContainer_t{
	public:
	tContainer_t():container(){}										//done	
	~tContainer_t(){}													//done						
	bool IsEmpty()const;												//done
	unsigned ItemsNum()const;											//done				
	void InsertAtEnd(const T* _item);									//done
	const T* GetFirst()const;
	const T* GetLast()const;
	T* Find(const T& _item)const;
	T* Remove(const T& _item);
	void RemoveAll(); //without delete
	void RemoveAndDelete(const T& _item);
	void RemoveAndDeleteAll();
	T* operator [] (int _index)const; 	
	
	private:
	container m_container;
	//iterator def
	typedef typename container::iterator itr;
	
	tContainer_t(const tContainer_t& _container); 						//copy is forbidden
	tContainer_t& operator = (const tContainer_t& _container); 			//copy is forbidden
	
	class Predicate_t{
		public:
		
		Predicate_t(T& _val):m_val(_val){ }
		bool operator()(T* _currentVal)const{return m_val == *_currentVal;}
		private:
		T m_val;
	}; 
	
	};
#endif //__TCONTAINER_T_H_

template<typename T, typename container>
bool tContainer_t<T,container>::IsEmpty()const
{
	return m_container.empty();
}

template<typename T, typename container>
unsigned tContainer_t<T,container>::ItemsNum()const
{
	return m_container.size();
}

template<typename T, typename container>
void tContainer_t<T,container>::InsertAtEnd(const T* _item)
{
	insert(m_container.end(), _item);
}


template<typename T, typename container>
const T* tContainer_t<T,container>::GetFirst()const
{
	return m_container.front();
}


template<typename T, typename container>
const T* tContainer_t<T,container>::GetLast()const
{
	 return *(m_container.end());
}

template<typename T, typename container>
T* tContainer_t<T,container>::Remove(const T& _item)
{
	itr it = find_if(m_container.begin(),m_container.end(),Predicate_t(_item));
	if(it == m_container.end())
	{
		return NULL; //not exist
	}
	T* temp = *it;
	m_container.erase(it);
	return temp;
}


template<typename T, typename container>
void tContainer_t<T,container>::RemoveAll() //without delete
{
	m_container.clear();
}



template<typename T, typename container>
void tContainer_t<T,container>::RemoveAndDelete(const T& _item)
{
	//use find
	T* temp = Find(_item);
	delete(temp);
}


template<typename T, typename container>	
void tContainer_t<T,container>::RemoveAndDeleteAll()
{
	m_container.erase(m_container.begin(), m_container.end());	
}


template<typename T, typename container>	
T* tContainer_t<T,container>::Find(const T& _item)const
{
	
	itr it = find_if(m_container.begin(),m_container.end(),Predicate_t(_item));
	if(it == m_container.end())
	{
		return NULL; //not exist
	}
	
	return *it;
}
	


template<typename T, typename container>
T* tContainer_t<T,container>::operator [] (int _index)const
{
	/*
	if(_index >= m_container.size())
	{
		//throw Exception<int>(_index, __LINE__,__FILE__,"Operator[]::Index Out Of Bounds");
	}*/
	
	if(typeid(m_container) == typeid(vector<T*>))
	{
		return m_container[_index];
	}
	
	else if(typeid(m_container) == typeid(list<T*>))
	{
			
		itr begin = m_container.begin();
		itr end = m_container.end();
		
		while(begin != end && _index)
		{
			--_index;
			++begin;
		}
		
		if(begin != end && _index == 0)
		{
			return *begin;
		}
	}
	return NULL;
}
