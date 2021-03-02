#ifndef __MEMMANAGER_H_
#define __MEMMANAGER_H_

#include <stddef.h>
/**
 * ADT memmory Manger Class.
 * Construction for this class is forbiden
 * actual memory size: how many bytes really written in memory
 * */
class MemManager_t{
	public:
	MemManager_t();
	virtual ~MemManager_t(){return;} 													
	size_t GetCurrentMemoryPosition()const{return m_currentMemoryPosition;}
	size_t GetActualMemSize()const{return m_actualMemorySize;}

	bool IsEmptyMemory()const{return !(bool)m_actualMemorySize;} 						//if actual size==0 retturn true
	
	virtual size_t Read(void* _userBuffer, size_t _numOfBytesToBeRead) = 0; 			//pure virtual- ADT Class//
	virtual size_t Read(void* _userBuffer, size_t _numOfBytesToBeRead,const size_t _pos)= 0;
	virtual size_t Write(const void* _data, size_t _numOfBytesToBeWritten) = 0;
	virtual size_t Write(const void* _data, size_t _numOfBytesToBeWritten,const size_t _pos) = 0;
	
	
	protected:
	
	void SetActualMemSize(size_t _newActualSize){m_actualMemorySize = _newActualSize;}
	void SetCurrentMemoryPosition(const size_t _pos);
	/*
	{
		if(_pos > GetActualMemSize()) 
		{
			throw "Positin Out Of Mem Bounds";
		}
		m_currentMemoryPosition = _pos;
	}*/
	
	private:
	size_t m_actualMemorySize; 
	size_t m_currentMemoryPosition; 
	MemManager_t(MemManager_t& _memManger); //copy CTOR // non copy class
	MemManager_t& operator = (const MemManager_t& _memManager); //asignement operator
};



#endif //__MEMMANAGER_H_
