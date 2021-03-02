#ifndef __MEMPAGE_T_H_
#define __MEMPAGE_T_H_

#include <stddef.h>
#include <memManager_t.h>
class MemPage_t : public MemManager_t{
	public:
	virtual ~MemPage_t();
	MemPage_t();
	MemPage_t(size_t _pageSize);
	
	virtual size_t Read(void* _userBuffer, size_t _numOfBytesToBeRead);
	virtual size_t Read(void* _userBuffer, size_t _numOfBytesToBeRead,const size_t _pos);
	
	virtual size_t Write(const void* _data, size_t _numOfBytesToBeWritten);
	virtual size_t Write(const void* _data, size_t _numOfBytesToBeWritten,const size_t _pos);
	
	bool IsPageFull()const{return isFullBuffer;}
	size_t GetPageCapacity(){return m_bufferSize;}
	
	size_t GetDefaultPageSize()const{return m_defaultPageSize;}
	size_t GetPageSize()const{return m_pageSize;}
	size_t GetPageBufferFreeBytesNum()const{return m_bufferFreeBytesNum;}
	static void SetDefaultPageSize(const size_t _newSize); //from now on change new born Mem size


	protected:
	
	
	private:
	static size_t m_defaultPageSize; //in Bytes
	const size_t m_pageSize; //current page capacity = tottal page bytes number
	char* m_buffer;
	size_t m_bufferSize;
	size_t m_bufferFreeBytesNum; //free bytes in cuurent page
	bool isFullBuffer;
	
	MemPage_t(MemPage_t& _page); //copy CTOR // page copy is forbidden
	MemPage_t& operator = (const MemPage_t& _page); //asignement operator
	char* CreateFrom(size_t _size){
		char* tmp = new char[_size];
		m_bufferSize = _size;
		isFullBuffer = false;
		m_bufferFreeBytesNum = _size;
		return tmp;
		}
	};
	
	//ostream& operator<<(ostream& os, const MemPage_t& _page);



#endif //__MEMPAGE_T_H_//
