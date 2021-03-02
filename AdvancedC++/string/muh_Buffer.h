#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "stddef.h"


namespace advcpp {

namespace detail {

template<typename T>
class Buffer{
public:
	Buffer(size_t c = DEFAULT_CAPACITY)
	: n_capacity(c)
	, m_data(new T[m_capacity]
	{
	}
	
	
	~Buffer()
	{
		delete[] m_data;
	}
	
	Buffer(const Buffer& lhs)	
	: n_capacity(lhs.m_capacity)
	, m_data(new T[m_capacity]
	{
		std::copy(lhs.begin(), lhs.end(), begin());		
	}
	
	Buffer& operator=(Buffer const& lhs)
	{
		Buffer t(lhs);
		swap(t);
		
		return *this;
	}
	
	
	void swap(Buffer& other)
	{
		using std::swap;
		
		swap(m_data, other.m_data);
		swap(m_capacity, other.m_capacity);
	}
	
	
	const T* begin() const
	{
		return m_data;
	}
	
	const T* end() const
	{
		return m_data + m_capacity;
	}

	T* begin()
	{
		return m_data;
	}
	
	T* end()
	{
		return m_data + m_capacity;
	}
		
	
    Buffer& operator=(const Buffer&);
    
    
    void swap(Buffer&);

    const char* getBuffer() const;
    
    size_t capacity() const;

private:
	static const size_t DEFAULT_CAPACITY = 16;
	size_t m_capacity;
	T* m_data;
}; // class Buffer

}} // namespace advcpp::detail






















#endif /* __BUFFER_H__ */
