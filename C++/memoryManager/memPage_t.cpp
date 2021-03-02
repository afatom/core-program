#include <memManager_t.h>
#include <memPage_t.h>
#include <iostream>
#include <string.h>
#include <assert.h>

size_t MemPage_t::m_defaultPageSize = 8;

void MemPage_t::SetDefaultPageSize(const size_t _newSize)
{
	m_defaultPageSize = _newSize; 
}


MemPage_t::~MemPage_t()
{
	delete[] m_buffer;
	m_buffer = NULL;
}

MemPage_t::MemPage_t():m_pageSize(m_defaultPageSize)
{
	m_buffer = CreateFrom(m_defaultPageSize);
}

MemPage_t::MemPage_t(size_t _pageSize):m_pageSize(_pageSize)
{
	size_t allocSize = 0, defSize = 0; 
	allocSize = defSize = m_defaultPageSize;
	
	if(_pageSize > defSize)
	{
		allocSize = _pageSize;
	}
	m_buffer = CreateFrom(allocSize);
}

size_t MemPage_t::Read(void* _userBuffer, size_t _numOfBytesToBeRead)
{
	size_t retval = 0;
	size_t curpos = GetCurrentMemoryPosition();
	if(!_userBuffer || !_numOfBytesToBeRead)
	{
		return 0;
	}
	
	if(curpos + _numOfBytesToBeRead < m_bufferSize)
	{
		assert(memcpy(_userBuffer, m_buffer + curpos, _numOfBytesToBeRead) != NULL); //read from current position
		SetCurrentMemoryPosition(_numOfBytesToBeRead);//increase curssor
		retval = _numOfBytesToBeRead; 
	
	}
	else if(curpos == m_bufferSize)
	{
		retval = 0;
	}
	else
	{
		assert(memcpy(_userBuffer, m_buffer + curpos, m_bufferSize - curpos) != NULL); //read from current position
		SetCurrentMemoryPosition(m_bufferSize);  //increase curssor
		retval = m_bufferSize - curpos;
	}
	
	return retval;
}


size_t MemPage_t::Read(void* _userBuffer, size_t _numOfBytesToBeRead,const size_t _pos)
{
	size_t retval = 0;
	size_t writerPos = GetActualMemSize();
	
	if(!_userBuffer || !_numOfBytesToBeRead || _pos > writerPos)
	{
		return 0;
	}
	
	SetCurrentMemoryPosition(_pos);
	
	retval = Read(_userBuffer, _numOfBytesToBeRead);
	return retval;
}


size_t MemPage_t::Write(const void* _data, size_t _numOfBytesToBeWritten)
{
	size_t writerPos = GetActualMemSize();
	size_t retval = 0;
	
	if(!_data || !_numOfBytesToBeWritten )
	{
		return 0;
	}
	
	if(m_bufferSize - writerPos >= _numOfBytesToBeWritten)
	{	
		assert(memcpy( m_buffer + writerPos, _data , _numOfBytesToBeWritten) != NULL); //read from current position
		SetActualMemSize(_numOfBytesToBeWritten);
		m_bufferFreeBytesNum -= _numOfBytesToBeWritten;
		retval = _numOfBytesToBeWritten;
	}
	
	else
	{	
		assert(memcpy( m_buffer+ writerPos, _data , m_bufferSize - writerPos) != NULL); //read from current position
		SetActualMemSize(m_bufferSize);
		m_bufferFreeBytesNum -= (m_bufferSize - writerPos);
		retval = m_bufferSize - writerPos;
	}
	return retval;
}

size_t MemPage_t::Write(const void* _data, size_t _numOfBytesToBeWritten,const size_t _pos)
{
	size_t writerPos = GetActualMemSize();
	size_t retval = 0;
	
	if(!_data || !_numOfBytesToBeWritten || _pos > writerPos)
	{
		return 0;
	}
	
	SetActualMemSize(_pos);
	retval = Write(_data, _numOfBytesToBeWritten);
	return retval;
}
/*	
ostream& MemPage_t::operator<<(ostream& os, const MemPage_t& _page)
{
	size_t i = 0;
	while (m_bufferSize)
	os<<"Page Buffer: "<<*(int*)m_buffer
	return os;
}
*/

//Addition------------------------
//ADD align to 2 exp x function
//ADD Cout operator
//add operators..like is defrent or...
