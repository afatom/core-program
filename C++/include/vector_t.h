#ifndef __VECTOR_T_H_
#define __VECTOR_T_H_


#include <algorithm>    // std::copy
#include <container_t.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>

using namespace std;

template<class T>
class Vector_t:public Container_t<T>{
	public:
	Vector_t();
	virtual ~Vector_t();
	Vector_t(const Vector_t& _vec);
	Vector_t& operator=(const Vector_t& _vec);
	virtual int Append(const T* _object, int _index);
	virtual int Prepend(const T* _object, int _index);
	virtual bool IsContains(const T& _object)const;
	virtual T* Find(const T& _object)const;
	virtual int ElementIndex(const T& _value)const;
	
	virtual int PushBack(T* _object);

	virtual T* Remove(const T& _object);
	virtual void RemoveAll();
	virtual void RemoveAndDelete(const T& _object);
	virtual void RemoveAndDeleteAll();
	//virtual bool operator == (const T& _object)const;
	const T& GetItem(int _index)const;
	protected:
	
	
	private:
	T** m_vector;
	int m_size;
	
	
		
	T** ReallocArr(int _newSize)
	{
		T** temp = (T**)realloc(this->m_vector,_newSize);
		if(!temp)
		{
			return NULL;
		}
		
		delete[] this->m_vector;
		return temp;
	}
	
	void CloseGap(int _index, int _noe)
	{
		for(int i = _index; i < _noe-1; ++i)
		{
			m_vector[_index] = m_vector[_index + 1];
		}
	}
	
	
	void Swap(int _index1, int _index2)
	{
		T* temp = m_vector[_index1];
		m_vector[_index1] = m_vector[_index2];
		m_vector[_index2] = temp;
	}
	
	void ShiftRight(int _index, int _noe)
	{
		
		for(int i = _noe-1; i > _index+1; --i)
		{
			Swap(i, i-1);
		}
	}
	
	void ShiftLeft(int _index, int _noe)
	{
		
		for(int i = _noe-1; i >= _index; --i)
		{
			Swap(i, i-1);
		}
	}
	
	
	};
	
	





#endif //__VECTOR_T_H_




#define VEC_INIT_SIZE 512

template<class T>
ostream& operator << (ostream& os, const Vector_t<T>& _vec)
{
	int noe = _vec.GetNumOfElements();
	os<<"Vector Elements:"<<endl;
	if(!noe)
	{
		os << "0"<<endl;
		return os;
	}
	
	for(int i = 0; i < noe; ++i)
	{
		os <<_vec.GetItem(i)<<endl;
	}
	return os;
}


template<class T>
const T& Vector_t<T>::GetItem(int _index)const
{
	int noe = this->GetNumOfElements();
	if(_index <0 || _index >= noe)
	{
		return *m_vector[0]; //what i should return here yossi??
	}
	
	return *m_vector[_index];
}



template<class T>
Vector_t<T>::Vector_t():Container_t<T>()
{
	m_vector = new T*[VEC_INIT_SIZE];
	m_size = VEC_INIT_SIZE;
}

template<class T>
Vector_t<T>::~Vector_t()
{
	this->RemoveAll();
}

template<class T>
int Vector_t<T>::PushBack(T* _object)
{
	int noe = this->GetNumOfElements();
	if(!_object)
	{
		return -1; 
	}
	
	if(m_size == noe)
	{
		//realloc
		this->ReallocArr(this->m_size * 2);
		//update size
		m_size *= 2;
	}
	
	m_vector[noe]=_object;
	this->IncrNumOfOfElements();
	
	return 0;
}

template<class T>
int Vector_t<T>::Append(const T* _object, int _index)
{
	int noe = this->GetNumOfElements();
	if(_index < -1 || _index >= noe)
	{
		return -1;
	}
	
	if(!_object)
	{
		return -1;
	}
	
	if(_index == noe -1) //add and incr noe
	{
		this->PushBack((T*)_object);
	}
	
	//m_vector[_index + 1]=_object;
	PushBack((T*)_object);
	this->ShiftRight(_index, noe);
	return 0;
	
}


template<class T>
int Vector_t<T>::Prepend(const T* _object, int _index)
{
	int noe = this->GetNumOfElements();
	if(_index <=0 || _index >= noe + 2)
	{
		return -1;
	}
	
	if(!_object)
	{
		return -1;
	}
	
	if(_index == noe + 1) //add and incr noe
	{
		this->PushBack((T*)_object);
	}
	
	//m_vector[_index - 1]=_object;
	PushBack((T*)_object);
	this->ShiftLeft(_index, noe);
	return 0;
}

template<class T>
bool Vector_t<T>::IsContains(const T& _object)const
{
	int noe = this->GetNumOfElements();
	for (int i = 0; i < noe ; ++i)
	{
		if(*m_vector[i] == _object)
		{
			return true;
		}
	}
	return false;
	
}


template<class T>
T* Vector_t<T>::Find(const T& _object)const
{
	int noe = this->GetNumOfElements();
	for (int i = 0; i < noe ; ++i)
	{
		if(*m_vector[i] == _object)
		{
			return m_vector[i];
		}
	}
	return NULL;
	
}

template<class T>
int Vector_t<T>::ElementIndex(const T& _value)const
{
	int noe = this->GetNumOfElements();
	for (int i = 0; i < noe ; ++i)
	{
		if(*m_vector[i] == _value)
		{
			return i;
		}
	}
	return -1;
	
}

template<class T>
T* Vector_t<T>::Remove(const T& _object)
{
	int noe = this->GetNumOfElements();
	int j = ElementIndex(_object);
	if(j == -1)
	{
		return NULL;
	}
	
	T* temp = m_vector[j];
	this->CloseGap(j, noe);
	
	this->DecrNumOfOfElements();
	return temp;
}


template<class T>
void Vector_t<T>::RemoveAll()
{
	this->SetNumOfOfElements(0);
}

template<class T>
void Vector_t<T>::RemoveAndDelete(const T& _object)
{
	int noe = this->GetNumOfElements();
	int j = ElementIndex(_object);
	if(j == -1)
	{
		return;
	}
	
	delete (m_vector[j]);
	this->CloseGap(j, noe);	
	this->DecrNumOfOfElements();

}

template<class T>
void Vector_t<T>::RemoveAndDeleteAll()
{
	int noe = this->GetNumOfElements();
	
	for(int i =0; i<noe; ++i)
	{
		delete (m_vector[i]);
	}
	delete [] m_vector;
	this->SetNumOfOfElements(0);
}
/*
template<class T>
bool Vector_t<T>::operator == (const T& _object)const
{
	if(*(this->m_vector[] == _object)
	{
		return true;
	}
	return false;
}
*/
template<class T>
Vector_t<T>& Vector_t<T>::operator=(const Vector_t& _vec)//is it the wright way to emplement = 
{
	if(this != &_vec)
	{
		this->m_size = _vec.m_size;
		int _vecNoe = _vec.GetNumOfElements();
		this->SetNumOfOfElements(0);
		
		for(int i = 0; i < _vecNoe; ++i)
		{
			this->PushBack(_vec.m_vector[i]);
		}
	}
	
	return *this;
}


template<class T>
Vector_t<T>::Vector_t(const Vector_t& _vec) : Container_t<T>(_vec) //copy ctor calls copy ctor of the base allways
{
	this->m_vector = new T* [_vec.GetNumOfElements()]; //bulding new vector with capacity=_vec.items num
	this->m_vector = _vec; //calling operator= 
}
