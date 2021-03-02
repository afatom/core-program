#ifndef __CONTAINER_T_H_
#define __CONTAINER_T_H_
#include <stddef.h>



using namespace std;

/*
class int{
	
			
	enum Container_Stat{
	
	CONTAINER_SUCCESS =0,
	CONTAINER_NULL_PARAMATER_ERROR,
	CONTAINER_ELEMENT_NOT_EXIST_ERROR,
	CONTAINER_INDEX_OUT_OF_BOUNDS_ERROR
	
	};

	
	};
	*/




template<class T>
class Container_t{
	public:
	
	Container_t(){ m_numOfElements = 0;}
	virtual ~Container_t(){};
	Container_t(const Container_t& _container){this->m_numOfElements = _container.m_numOfElements;} //copy ctor
	virtual Container_t& operator=(const Container_t& _container)
	{
		this->m_numOfElements = _container.m_numOfElements;
		return *this;
	}; 
	virtual int Append(const T* _object, int _index)=0;
	virtual int Prepend(const T* _object, int _index)=0;
	virtual bool IsContains(const T& _object)const=0;
	virtual T* Find(const T& _object)const=0;
	virtual int ElementIndex(const T& _value)const=0;
	virtual int PushBack(T* _object)=0;
	bool IsEmpty()const{return (m_numOfElements==0)?(true):(false);}
	virtual T* Remove(const T& _object)=0;
	virtual void RemoveAll()=0;
	virtual void RemoveAndDelete(const T& _object)=0;
	virtual void RemoveAndDeleteAll()=0;
	//virtual bool operator == (const T& _object)const=0;
	int Count()const{return m_numOfElements;}
	
	int GetNumOfElements()const{return this->m_numOfElements;}
	
	protected:
	//virtual const T& GetItem(int _index)const=0;
	void IncrNumOfOfElements(){++this->m_numOfElements;}
	void SetNumOfOfElements(int num){m_numOfElements = num;}
	void DecrNumOfOfElements()
	{
		if(m_numOfElements == 0)
		{
			return;
		}
		--this->m_numOfElements;
	}
	
	
	private:
	int m_numOfElements;
	
	};




#endif //__CONTAINER_T_H_
