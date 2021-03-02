#ifndef __MEMPOOL_T_H_
#define __MEMPOOL_T_H_

#include <iostream>
#include <vector>
#include <memPage_t.h>
using namespace std;

class MemPool_t : public MemManager_t{
	public:
	MemPool_t();
	
	virtual ~MemPool_t();
	size_t GetTottalWrittenBytes()const{return m_tottalWrittenBytes;}
	
	static void SetDefPagesSize(const size_t _new);
	virtual size_t Read(void* _userBuffer, size_t _numOfBytesToBeRead);
	virtual size_t Read(void* _userBuffer, size_t _numOfBytesToBeRead,const size_t _pos);
	
	virtual size_t Write(const void* _data, size_t _numOfBytesToBeWritten);
	virtual size_t Write(const void* _data, size_t _numOfBytesToBeWritten,const size_t _pos);
	
	
	protected:
	
	private:
	vector<MemPage_t*> pool;
	size_t m_tottalWrittenBytes;
	size_t m_currentPage;
	size_t m_currentPosition; //in bytes
	
	
	
	MemPool_t(MemPool_t& _pool); 
	MemPool_t& operator = (const MemPool_t& _pool);
	size_t FindPageAndOffsetInFoundedPage(size_t _userPosition, size_t* _foundedPageOffset);
	bool CheckParams(const void* _data, size_t _userBytesNum, size_t _pos);
	
	};
	




#endif //__MEMPOOL_T_H_//
