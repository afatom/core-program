#ifndef __VIRTIO_T_H_
#define __VIRTIO_T_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <TException_t.h>
#include <string.h>

using namespace std;

class VirtIO_t{
	public:
	/******************************************************************/
	VirtIO_t();
	virtual ~VirtIO_t();
	VirtIO_t(const string& _fileName, const string& _mode);
	/*
	enum SeekRelative{
		REL_BEG = SEEK_SET, //the offset is relative to the start of the file
		REL_CUR = SEEK_CUR, //the current position indicator
		REL_END = SEEK_END // end-of-file
	};*/
	
	long GetFileLength()const //in bytes
	{
		//svae current pos
		fseek(m_pFile, 0, SEEK_END);
		length = ftell(m_pFile);
		fseek again to init pos
		return length
	} 
	const string& GetFileAccess()const{return m_access;} //mode r r+
	const string& GetFilePath()const{return m_path;} //mode r r+
	const FILE* GetFilePtr()const{return m_pFile;}
	
	typedef enum FileStatus_t{
		FILE_OK =0,
		OPEN_FILE_ERROR,
		BAD_ACCESS,
		WR_ERR,
		READ_ERR
	}FileStatus_t;
	
	FileStatus_t GetFileStatus()const{return m_stat;}

	FileStatus_t FileOpen(const string& _fpath, const string& _access);
	FileStatus_t FileOpen();
	
	int FileClose()
	{
		return fclose(m_pFile);
	}
	
	long GetPos()const
	{
		return ftell(m_pFile);
	}
	
	
	//maybe this function needs to return file status
	int SeekPos(long _offset,int _seekRelative)
	{
		if(!fseek(m_pFile,_offset,_seekRelative))
		{
			throw(TException_t<int>(0, __LINE__, __FILE__,__func__,"SEEK_ERROR"));
		}
		return 0; //success
	}
	
	void Home()
	{
		rewind(m_pFile);
	}
	
	virtual VirtIO_t& operator << (int _val)=0;
	virtual VirtIO_t& operator << (char _val)=0;
	virtual VirtIO_t& operator << (short _val)=0;
	virtual VirtIO_t& operator << (long _val)=0;
	virtual VirtIO_t& operator << (float _val)=0;
	virtual VirtIO_t& operator << (double _val)=0;
	virtual VirtIO_t& operator << (unsigned int _val)=0;
	virtual VirtIO_t& operator << (unsigned char _val)=0;
	virtual VirtIO_t& operator << (unsigned short _val)=0;
	virtual VirtIO_t& operator << (unsigned long _val)=0;
	virtual VirtIO_t& operator >> (int& _val)=0;
	virtual VirtIO_t& operator >> (char& _val)=0;
	virtual VirtIO_t& operator >> (short& _val)=0;
	virtual VirtIO_t& operator >> (long& _val)=0;
	virtual VirtIO_t& operator >> (float& _val)=0;
	virtual VirtIO_t& operator >> (double& _val)=0;
	virtual VirtIO_t& operator >> (unsigned int& _val)=0;
	virtual VirtIO_t& operator >> (unsigned char& _val)=0;
	virtual VirtIO_t& operator >> (unsigned short& _val)=0;
	virtual VirtIO_t& operator >> (unsigned long& _val)=0;
	
	
	
	//Open - if user call dflt ctor
	//Close
	protected:
	string m_access; //file mode
	string m_path;
	FILE* m_pFile;
	FileStatus_t m_stat;

	VirtIO_t(const VirtIO_t& _io); //non copy
	VirtIO_t& operator = (const VirtIO_t& _io); //non copy

	private:
	/******************************************************************/

	
	
	//int addressMode[2]; //address and 0 = read  1  =Wr  ex:  |0x788FFABBFF|0| for binary uses only//for class binIO
	/******************************************************************/  
	};

#endif //__VIRTIO_T_H_



VirtIO_t::~VirtIO_t()
{
	if(m_stat == FILE_OK)
	{
		fclose(m_pFile);
	}
}


/**********************************************************************/  	
VirtIO_t::VirtIO_t()//:m_access("0"),m_path("0")
{
	m_access = " ";
	m_path = " ";
	m_pFile = 0; //null init. good init
	m_stat = OPEN_FILE_ERROR;

}

/**********************************************************************/  	
VirtIO_t::VirtIO_t(const string& _fileName, const string& _mode)//:m_access(_mode),m_path(_fileName) //error: only constructors take member initializers
{
	m_access = _mode;
	m_path = _fileName;
	m_pFile = fopen(_fileName.c_str(),_mode.c_str());
	if(!m_pFile)
	{
		m_stat = OPEN_FILE_ERROR;
	}
	else
	{
		m_stat = FILE_OK;
	}
}
/**********************************************************************/  	
VirtIO_t::FileStatus_t VirtIO_t::FileOpen(const string& _fpath, const string& _access)
{
	m_access = _access;
	m_path = _fpath;
	m_pFile = fopen(_fpath.c_str(),_access.c_str());
	if(!m_pFile)
	{
		throw(TException_t<int>(0, __LINE__, __FILE__,__func__,"File Path/File Access Rejected"));
		
	}
	m_stat = FILE_OK;
	return m_stat;
}

/**********************************************************************/  	
VirtIO_t::FileStatus_t VirtIO_t::FileOpen()
{
	m_pFile = fopen(m_path.c_str(), m_access.c_str());
	if(!m_pFile)
	{
		//exception
		throw(TException_t<int>(0, __LINE__, __FILE__,__func__,"File Path/File Access Rejected"));
	}
	m_stat = FILE_OK;
	return m_stat;
}
/**********************************************************************/  	



