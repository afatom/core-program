#include <assert.h>
#include <stddef.h>
#include <memManager_t.h>
#include <memPool_t.h>
#include <memPage_t.h>
#include <iostream>
#include <vector>

using namespace std;

//#define TEST

MemPool_t::MemPool_t() //compiler constructs manger alone. no need to call memManager CTOR 
{
	MemPage_t* pg = new MemPage_t;
	pool.insert(pool.end(), pg);
	m_tottalWrittenBytes = 0;
	m_currentPage =0;
	m_currentPosition =0;
}

void MemPool_t::SetDefPagesSize(const size_t _new)
{
	MemPage_t::SetDefaultPageSize(_new);
}

MemPool_t::~MemPool_t()
{
	size_t vecSize = pool.size();
	assert(vecSize != 0);
	for(size_t i =0; i< vecSize; ++i)
	{
		delete(pool[i]); //delete pages
	}
	//vector DTOR - compiler do the work alone 
}

/*
size_t MemPool_t::Read(void* _userBuffer, size_t _numOfBytesToBeRead)
{
	if(!_numOfBytesToBeRead || !_userBuffer)
	{
		return 0;
	}
	
	size_t numOfPages = pool.size(), i=0, curPageBufferSize = 0, retval = 0;
	char* ptr = (char*)_userBuffer;
	while(_numOfBytesToBeRead && i < numOfPages)
	{
		curPageBufferSize = pool[i]->GetPageSize() - pool[i]->GetPageBufferFreeBytesNum();
		//curPageBufferSize = pool[i]->GetPageCapacity();
		//curPageBufferSize = pool.at(i)->GetPageCapacity();
		
		if(curPageBufferSize >= _numOfBytesToBeRead)
		{
			retval = pool[i]->MemPage_t::Read(ptr, _numOfBytesToBeRead);
			//retval = pool.at(i)->MemPage_t::Read(ptr, _numOfBytesToBeRead);
			
			break;
		}
		//retval = pool[i]->MemPage_t::Read(ptr, _numOfBytesToBeRead);
		retval = pool[i]->MemPage_t::Read(ptr, curPageBufferSize);
		
		_numOfBytesToBeRead -= retval;
		ptr += retval;
		++i;
	}
	return retval;
}*/





/*
size_t MemPool_t::Read(void* _userBuffer, size_t _numOfBytesToBeRead)
{
	char* ptr = (char*)_userBuffer;
	size_t numOfReadedBytesTillNow = 0, j =0, retval =0, currentBytes =0;
	
	if(!_userBuffer || !_numOfBytesToBeRead)
	{
		return 0;
	}
	
	while(numOfReadedBytesTillNow < _numOfBytesToBeRead  &&  j < pool.size())
	{
		_numOfBytesToBeRead -= numOfReadedBytesTillNow;
		
		currentBytes = pool[j]->MemPage_t::GetPageSize() - pool[j]->MemPage_t::GetPageBufferFreeBytesNum();
		
		if(_numOfBytesToBeRead <= currentBytes)
		{
			retval = pool[j]->MemPage_t::Read(ptr, _numOfBytesToBeRead);
			numOfReadedBytesTillNow += retval;
			break;
		}
		
		retval = pool[j]->MemPage_t::Read(ptr, currentBytes); 
		assert(retval == currentBytes);
		ptr = ptr + currentBytes;
		numOfReadedBytesTillNow += currentBytes;
		++j;
	}
	return numOfReadedBytesTillNow;
}
*/



/*
size_t MemPool_t::Read(void* _userBuffer, size_t _numOfBytesToBeRead)
{
	char* ptr = (char*)_userBuffer;
	size_t numOfReadedBytesTillNow = 0, j =0, retval =0, currentBytes =0;
	
	if(!_userBuffer || !_numOfBytesToBeRead)
	{
		return 0;
	}
	
	while(numOfReadedBytesTillNow < _numOfBytesToBeRead  &&  j < pool.size())
	{
		_numOfBytesToBeRead -= numOfReadedBytesTillNow;
		
		currentBytes = pool[j]->MemPage_t::GetPageSize() - pool[j]->MemPage_t::GetPageBufferFreeBytesNum();
		
		if(_numOfBytesToBeRead <= currentBytes)
		{
			retval = pool[j]->MemPage_t::Read(ptr, _numOfBytesToBeRead);
			numOfReadedBytesTillNow += retval;
			break;
		}
		
		retval = pool[j]->MemPage_t::Read(ptr, currentBytes); 
		assert(retval == currentBytes);
		ptr = ptr + currentBytes;
		numOfReadedBytesTillNow += currentBytes;
		++j;
	}
	return numOfReadedBytesTillNow;
}

*/



size_t MemPool_t::Read(void* _userBuffer, size_t _numOfBytesToBeRead)
{
	char* ptr = (char*)_userBuffer;
	size_t numOfReadedBytesTillNow = 0, j =m_currentPage, retval =0, currentBytes =0, count =0;
	size_t def = 0;
	if(!_userBuffer || !_numOfBytesToBeRead)
	{
		return 0;
	}
	
	if(_numOfBytesToBeRead >= m_tottalWrittenBytes)
	{
		for(j = m_currentPage; j < pool.size(); ++j)
		{
			currentBytes = pool[j]->MemPage_t::GetPageSize() - pool[j]->MemPage_t::GetPageBufferFreeBytesNum();
			retval = pool[j]->MemPage_t::Read(ptr, currentBytes);
			numOfReadedBytesTillNow += retval;
			ptr = ptr + currentBytes;
		}
		m_currentPosition = m_tottalWrittenBytes;
		m_currentPage = j;
		return numOfReadedBytesTillNow;
	}
	
	while(count < _numOfBytesToBeRead)
	{
		def = _numOfBytesToBeRead - count;
		currentBytes = pool[j]->MemPage_t::GetPageSize() - pool[j]->MemPage_t::GetPageBufferFreeBytesNum();
		if(currentBytes <= def)
		{
			retval = pool[j]->MemPage_t::Read(ptr, currentBytes);
			count += currentBytes;
			numOfReadedBytesTillNow += retval;
			ptr = ptr + currentBytes;
		}
		else
		{
			retval = pool[j]->MemPage_t::Read(ptr, def);
			count += def;
			numOfReadedBytesTillNow += retval;
			ptr = ptr + def;
		}
		++j;
	}
	m_currentPosition = numOfReadedBytesTillNow;
	m_currentPage = j;
	return numOfReadedBytesTillNow;
}


/*
size_t MemPool_t::FindPageToStartFrom(size_t _userPosition, size_t* _countedBytes)
{
	size_t counter =0, j =0, total=0;
	while(_userPosition > 0)
	{
		counter = pool[j]->MemPage_t::GetPageSize();
		_userPosition -= counter;
		total += counter;
		++j;
	}
	*_countedBytes = total;
	return j;
}
*/

size_t MemPool_t::FindPageAndOffsetInFoundedPage(size_t _userPosition, size_t* _foundedPageOffset)
{
	size_t j =0;
	int userpos = (int)_userPosition;
	while(userpos > 0)
	{
		userpos -= (int)(pool[j]->MemPage_t::GetPageSize());
		++j;
	}
	
	*_foundedPageOffset = (size_t)((int)(pool[j]->MemPage_t::GetPageSize()) - userpos);
	return j;
}










/*
size_t MemPool_t::Write(const void* _data, size_t _numOfBytesToBeWritten)
{
	char* ptr = (char*)_data;
	size_t i =0, freeBytesInThisPage = 0, retval =0;
	
	if(!_numOfBytesToBeWritten || !_data)
	{
		return 0;
	}
	
	//GetPageBufferFreeBytesNum();
	while(1)
	{
		freeBytesInThisPage = pool[i]->MemPage_t::GetPageBufferFreeBytesNum();
		if(_numOfBytesToBeWritten <= freeBytesInThisPage)
		{
			retval = pool[i]->MemPage_t::Write(_data, _numOfBytesToBeWritten);
			m_tottalWrittenBytes += retval;
			
			#ifdef TEST
			cout<<"m_tottalWrittenBytes "<<m_tottalWrittenBytes<<endl;
			#endif
			break;
		}
		
		//write bytes - what ever you can - tell page end
		//pool[i]->MemPage_t::Write(_data, _numOfBytesToBeWritten);
		pool[i]->MemPage_t::Write(_data, freeBytesInThisPage);
		
		_numOfBytesToBeWritten -= freeBytesInThisPage;
		ptr += freeBytesInThisPage;
		m_tottalWrittenBytes += freeBytesInThisPage;
		
		//insert new page
		MemPage_t* newPage = new MemPage_t;
		pool.insert(pool.end(), newPage);
		#ifdef TEST
		cout<<"m_tottalWrittenBytes "<<m_tottalWrittenBytes<<endl;
		#endif
		++i;
	}

	return retval;
}


*/

bool MemPool_t::CheckParams(const void* _data, size_t _userBytesNum, size_t _pos)
{
	if(!_data || !_userBytesNum || _pos > GetActualMemSize())
	{
		return false;
	}
	
	return true;
}



size_t MemPool_t::Write(const void* _data, size_t _numOfBytesToBeWritten,const size_t _pos)
{
	size_t _foundedPageOffset = 0, foundedPage =0, retval = 0;
	if(!CheckParams(_data,_numOfBytesToBeWritten,_pos))
	{
		return 0; //bad params
	}
	
	foundedPage = FindPageAndOffsetInFoundedPage(_pos, &_foundedPageOffset);
	
	//set offset in the founded page for writing
	retval =  pool[foundedPage]->MemPage_t::Write(_data, _numOfBytesToBeWritten, _foundedPageOffset);
	if(retval == _numOfBytesToBeWritten)
	{
		if(_pos + _numOfBytesToBeWritten > GetActualMemSize())
		{
			SetActualMemSize(_pos + _numOfBytesToBeWritten);
		}
		//SetCurrentMemoryPosition(_pos);
		//test only
		try
		{
			SetCurrentMemoryPosition(10800);
		}
		catch(const char* _setmsg)
		{
			cout<<"Exception arrival"<<endl;
			cout<<_setmsg<<endl;
		}
			
			
			return retval;
		}
	//////////////////////////////
	_data = (char*)_data + retval;
	_numOfBytesToBeWritten -= retval;
	retval = 0;
	
	while(retval != _numOfBytesToBeWritten)
	{
		//create new page and keep inserting
		MemPage_t* newPage = new MemPage_t;
		pool.insert(pool.end(), newPage);
		
		
		retval +=  pool[foundedPage]->MemPage_t::Write(_data, _numOfBytesToBeWritten, 0);
		_data = (char*)_data + retval;
		_numOfBytesToBeWritten -= retval;
		retval = 0;
	}
	
	if(_pos + _numOfBytesToBeWritten > GetActualMemSize())
	{
		SetActualMemSize(_pos + _numOfBytesToBeWritten);
	}
	//SetCurrentMemoryPosition(_pos);
	//for ex only 
	try
	{
		SetCurrentMemoryPosition(2048);
	}
	catch(const char* _setmsg)
	{
		cout<<"Exception arrival"<<endl;
		cout<<_setmsg<<endl;
	}
	return _numOfBytesToBeWritten;
}



size_t MemPool_t::Write(const void* _data, size_t _numOfBytesToBeWritten)
{
	return Write(_data, _numOfBytesToBeWritten, GetCurrentMemoryPosition());
}


size_t MemPool_t::Read(void* _userBuffer, size_t _numOfBytesToBeRead,const size_t _pos)
{
	size_t _foundedPageOffset = 0, foundedPage =0, retval = 0;
	
	if(!CheckParams(_userBuffer, _numOfBytesToBeRead, _pos))
	{
		return 0; //bad params
	}
	
	foundedPage = FindPageAndOffsetInFoundedPage(_pos, &_foundedPageOffset);
	//set offset in the founded page for Reading
	retval =  pool[foundedPage]->MemPage_t::Read(_userBuffer, _numOfBytesToBeRead, _foundedPageOffset);
	
		return retval; //for now//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}
















