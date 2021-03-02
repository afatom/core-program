#ifndef __SHARED_POINTER_H__
#define __SHARED_POINTER_H__ 

#include <stddef.h>
#include <algorithm>
#include <iostream> //test only

#define TEST_MODE


class Counter
{
public:
	Counter() {m_counter =0;}
	//~Counter();

	Counter& operator++() {++m_counter; return *this;}
	Counter& operator--() {--m_counter; return *this;}
	size_t GetCount() const {return m_counter;}
	bool operator==(const size_t& rhs) const {return (m_counter == rhs);} 

private:
	size_t m_counter;
};



template<typename Type>
class ShPointer{
public:
	explicit ShPointer(Type* rptr = 0);
	~ShPointer();
	ShPointer(const ShPointer&);

	ShPointer& operator=(const ShPointer&);
	Type& operator*();
	Type* operator->();
	const Type* GetAddress() const;


private:
	Type* m_address;
	Counter* m_counter;
};




template<typename Type>
inline ShPointer<Type>::ShPointer(Type* rptr)
: m_address(rptr)
, m_counter(new Counter)
{
	++(*m_counter);
	#ifdef TEST_MODE
	std::cout<<"CTOR Body . RefCount= "<< m_counter->GetCount()<<std::endl;
	#endif
}


template<typename Type>
inline ShPointer<Type>::~ShPointer()
{
	#ifdef TEST_MODE
	std::cout<<"Dtor Entry"<<std::endl;
	std::cout<<"RefCount= "<<m_counter->GetCount()<<std::endl;
	#endif
	
	if(--(*m_counter) == 0){
		#ifdef TEST_MODE
		std::cout<<"Dtor Activated"<<std::endl;
		std::cout<<"RefCount= "<< m_counter->GetCount() <<std::endl;
		#endif
		delete m_counter;
		delete m_address;

		
	}
}



template<typename Type>
inline Type& ShPointer<Type>::operator*()
{
	return *m_address;
}



template<typename Type>
const Type* ShPointer<Type>::GetAddress() const
{
	return m_address;
}



template<typename Type>
Type* ShPointer<Type>::operator->()
{
	return m_address;
}


template<typename Type>
ShPointer<Type>& ShPointer<Type>::operator=(const ShPointer& other)
{
	//if(*this == other) {return other;} safe for smartones and painly for idiots
	ShPointer temp(other);
	std::swap(temp, *this);
	return *this;
}


template<typename Type>
ShPointer<Type>::ShPointer(const ShPointer& other)
: m_address(other.m_address)
, m_counter(other.m_counter)
{
	#ifdef TEST_MODE
	std::cout<<"Copy CTOR Entry"<<std::endl;
	#endif
	++m_counter;
}

#endif //__SHARED_POINTER_H__