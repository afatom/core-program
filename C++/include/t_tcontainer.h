#ifndef __T_CONTAINER_T_H_
#define __T_CONTAINER_T_H_

#include <iostream> //cout
#include <vector>
#include <list>
#include <typeinfo>
#include <algorithm> //stl
#include <iterator>
#include <stdexcept>
#include <algorithm>

using namespace std;

// template <class T, class X>
template<class T, template<class, class> class TContainer>
class tContainer_t {
	private:
	typedef TContainer<T*, allocator<T*> > container;
	container m_container;
	typedef typename container::const_iterator itr;
	typedef typename container::iterator unc_itr;
	
	tContainer_t(const tContainer_t& _container); 						//copy is forbidden
	tContainer_t& operator = (const tContainer_t& _container); 			//copy is forbidden
	class Predicate_t{
		public:
		
		Predicate_t(const T& _val):m_val(_val){ }
		bool operator()(T* _currentVal)const{return m_val == *_currentVal;}

		private:
		T m_val;
	};
	   
	public:
	tContainer_t(){}										//done	
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
	T* operator [] (int _index); 	
		


};

#endif //__T_CONTAINER_T_H_

template<class T, template<class, class> class TContainer>
ostream& operator << (ostream& os, tContainer_t<T,TContainer>& _cont)
{
	int index=0;
	unsigned noe = _cont.ItemsNum();
	if(!noe)
	{
		os <<"Empty container";
	}
	while(noe--)
	{
		os <<*(_cont[index])<<" ";
		++index;
	} 
	return os;
}


template<class T, template<class, class> class TContainer>
bool tContainer_t<T,TContainer>::IsEmpty()const
{
	return m_container.empty();
}

template<class T, template<class, class> class TContainer>
unsigned tContainer_t<T,TContainer>::ItemsNum()const
{
	return (unsigned)m_container.size();
}

template<class T, template<class, class> class TContainer>
void tContainer_t<T,TContainer>::InsertAtEnd(const T* _item)
{
	//m_container.insert(m_container.end(), _item);
	m_container.push_back((T*)_item);
}


template<class T, template<class, class> class TContainer>
const T* tContainer_t<T,TContainer>::GetFirst()const
{
	return m_container.front();
}


template<class T, template<class, class> class TContainer>
const T* tContainer_t<T,TContainer>::GetLast()const
{
	 return m_container.back();
}

template<class T, template<class, class> class TContainer>
T* tContainer_t<T,TContainer>::Remove(const T& _item)
{
	unc_itr it = find_if(m_container.begin(),m_container.end(),Predicate_t(_item));
	if(it == m_container.end())
	{
		return NULL; //not exist
	}
	T* temp = *it;
	m_container.erase(it);
	return temp;
}


template<class T, template<class, class> class TContainer>
void tContainer_t<T,TContainer>::RemoveAll() //without delete
{
	m_container.clear();
}



template<class T, template<class, class> class TContainer>
void tContainer_t<T,TContainer>::RemoveAndDelete(const T& _item)
{
	//use find
	T* temp = Find(_item);
	delete(temp);
}


template<class T, template<class, class> class TContainer>	
void tContainer_t<T,TContainer>::RemoveAndDeleteAll()
{
	m_container.erase(m_container.begin(), m_container.end());	
}


template<class T, template<class, class> class TContainer>	
T* tContainer_t<T,TContainer>::Find(const T& _item)const
{

	itr it = find_if(m_container.begin(),m_container.end(),Predicate_t((T)_item));
	if(it == m_container.end())
	{
		return NULL; //not exist
	}
	
	return *it;
}
	


template<class T, template<class, class> class TContainer>
T* tContainer_t<T,TContainer>::operator [] (int _index)
{
	
	if(_index >= (int)m_container.size())
	{
		//throw Exception<int>(_index, __LINE__,__FILE__,"Operator[]::Index Out Of Bounds");
		return NULL;
	}
	
	if(typeid(m_container) == typeid(vector<T*>))
	{
		return (*(vector<T*>*)&m_container)[_index];
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










