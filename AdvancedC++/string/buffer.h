
#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <cstddef>
#include <algorithm>

namespace advcpp {

namespace detail {

template<typename T>
class Buffer{

public:
	inline explicit Buffer(size_t size = defaultCapacity);
	inline Buffer(const Buffer& other);
    inline ~Buffer();
	
	inline Buffer& operator=(Buffer const& other);
    inline const Buffer& operator[](size_t) const;
    inline Buffer& operator[](size_t);
    inline void swap(Buffer& other);
	inline const T* begin() const; //for const objects ex:    foo(const buffer& buf)
	inline const T* end() const; //for non const objects ex:  foo(buffer& buf)
	inline T* begin();
	inline T* end();
    inline const T* getBuffer() const;
    inline size_t capacity() const;
    inline void grow(double times = 1.5); // new capacity = times * current capacity //

private:
	size_t m_capacity;
	T* m_buffer;
    static const size_t defaultCapacity = 16;
}; // class Buffer



template<typename T>
Buffer<T>::Buffer(size_t size)	
: m_capacity(size)
, m_buffer(new T[m_capacity]){;}

template<typename T>
Buffer<T>::~Buffer()
{
    delete[] m_buffer;
}

template<typename T>
Buffer<T>::Buffer(const Buffer& other)
: m_capacity(other.m_capacity)
, m_buffer(new T[m_capacity])
{
    std::copy(other.begin(), other.end(), begin()); //this expression is not exception safe because copy/= operator of class T can throw exception. try catch and release new or use shared pointer with deleter with []		
}
	
template<typename T>
Buffer<T>& Buffer<T>::operator=(Buffer const& other)
{
    Buffer t(other);
    swap(t);		
    return *this;
}
	
template<typename T>
void Buffer<T>::swap(Buffer& other)
{
    using std::swap;
    swap(m_buffer, other.m_buffer);
    swap(m_capacity, other.m_capacity);
}
	
template<typename T>	
const T* Buffer<T>::begin() const{return m_buffer;}

template<typename T>
const T* Buffer<T>::end() const {return m_buffer + m_capacity;}

template<typename T>
T* Buffer<T>::begin() {return m_buffer;}

template<typename T>
T* Buffer<T>::end(){ return m_buffer + m_capacity;}
		
template<typename T>
const T* Buffer<T>::getBuffer() const {return m_buffer;}

template<typename T>    
size_t Buffer<T>::capacity() const {return m_capacity;}

template<typename T>
void Buffer<T>::grow(double times)
{
    if(times < 1)
        return;

    m_capacity *= times;
    T* newBuffer = new T[m_capacity];
    T* temp = m_buffer;
    std::copy(this->begin(), this->end(), newBuffer);
    m_buffer = newBuffer;
    delete[]temp;	
}

}} // namespace advcpp::detail

#endif /* __BUFFER_H__ */





