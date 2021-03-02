#include <memManager_t.h>



//size_t MemManager_t::m_defaultPageSize = 8; //default page

//default CTOR
//MemManager_t::MemManager_t():m_defaultMemSize(16)
MemManager_t::MemManager_t()
{
	m_actualMemorySize = 0; //how many bytes really written in memory
	m_currentMemoryPosition = 0;
} 


void MemManager_t::SetCurrentMemoryPosition(const size_t _pos)
{
	if(_pos > GetActualMemSize()) 
	{
		throw "Position Out Of Mem Bounds";
	}
	m_currentMemoryPosition = _pos;
}
