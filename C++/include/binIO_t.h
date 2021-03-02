#ifndef __BINIO_T_H_
#define __BINIO_T_H_





using namespace std;

class BinIO_t:public VirtIO_t{
	
	public:
	BinIO_t(){m_rwFlag = '\0'; m_rwAdress=NULL;}
	virtual ~BinIO_t(){fclose(m_pFile);}
	BinIO_t(const string& _fileName, const string& _mode);
	
	BinIO_t& operator >> (void* Buf);
	BinIO_t& operator << (const void* Buf);
	void  operator,(int len);        // for read / write blocks
	
	
	
	virtual BinIO_t& operator << (int _val){return Write<int>(_val);}
	virtual BinIO_t& operator << (char _val){return Write<char>(_val);}
	virtual BinIO_t& operator << (short _val){return Write<short>(_val);}
	virtual BinIO_t& operator << (long _val){return Write<long>(_val);}
	virtual BinIO_t& operator << (float _val){return Write<float>(_val);}
	virtual BinIO_t& operator << (double _val){return Write<double>(_val);}
	virtual BinIO_t& operator << (unsigned int _val){return Write<unsigned int>(_val);}
	virtual BinIO_t& operator << (unsigned char _val){return Write<unsigned char>(_val);}
	virtual BinIO_t& operator << (unsigned short _val){return Write<unsigned short>(_val);}
	virtual BinIO_t& operator << (unsigned long _val){return Write<unsigned long>(_val);}
	virtual BinIO_t& operator >> (int& _val){return Read<int>(_val);}
	virtual BinIO_t& operator >> (char& _val){return Read<char>(_val);}
	virtual BinIO_t& operator >> (short& _val){return Read<short>(_val);}
	virtual BinIO_t& operator >> (long& _val){return Read<long>(_val);}
	virtual BinIO_t& operator >> (float& _val){return Read<float>(_val);}
	virtual BinIO_t& operator >> (double& _val){return Read<double>(_val);}
	virtual BinIO_t& operator >> (unsigned int& _val){return Read<unsigned int>(_val);}
	virtual BinIO_t& operator >> (unsigned char& _val){return Read<unsigned char>(_val);}
	virtual BinIO_t& operator >> (unsigned short& _val){return Read<unsigned short>(_val);}
	virtual BinIO_t& operator >> (unsigned long& _val){return Read<unsigned long>(_val);}
	
	
	
	private:
	BinIO_t(const BinIO_t&);
	BinIO_t& operator = (const BinIO_t&);
	void* m_rwAdress;
	char m_rwFlag;
	
	template<typename T>
	BinIO_t& Write(const T& _type);
	
	template<typename T>
	BinIO_t& Read(T& _type);	
	
	};



#endif //__BINIO_T_H_

BinIO_t::BinIO_t(const string& _fileName, const string& _mode):VirtIO_t(_fileName,_mode){}

/**********************************************************************************/
template<typename T>
BinIO_t& BinIO_t::Write(const T& _type)
{
	if(this->GetFileStatus() != FILE_OK)
	{
		throw(TException_t<long>(0, __LINE__, __FILE__,__func__,"OPEN_FILE_ERROR"));
	}
	
	//string errno_msg(strerror(retval));
	if(ferror((FILE*)GetFilePtr()))
	{
		throw(TException_t<long>(0, __LINE__, __FILE__,__func__, "WR_ERR"));
	}
	
	else
	{
		fwrite(&_type , sizeof(T), 1, this->m_pFile);
		
	}
	return *this;
}

/**********************************************************************************/

template<typename T>
BinIO_t& BinIO_t::Read(T& _type)
{
	if(this->GetFileStatus() != FILE_OK)
	{
		throw(TException_t<long>(0, __LINE__, __FILE__,__func__,"OPEN_FILE_ERROR"));
	}
	
	if(ferror((FILE*)GetFilePtr()))
	{
		//string errno_msg(strerror(retval));
		throw(TException_t<long>(0, __LINE__, __FILE__,__func__, "READ_ERR"));
	}
	else
	{
		fread(&_type , sizeof(T), 1, this->m_pFile);
		
	}
	return *this;
}
/**********************************************************************************/



BinIO_t& BinIO_t::operator >> (void* Buf)
{
	//check NULL buf in case <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||||||
	m_rwAdress = Buf;
	m_rwFlag = 'R';
}
BinIO_t& BinIO_t::operator << (const void* Buf)
{
	//check NULL buf in case <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||||||
	m_rwAdress = (void*)Buf;
	m_rwFlag = 'W';
}
void BinIO_t::operator,(int len)
{
	if(m_rwFlag == 'R')
	{
		//call read
		if(this->GetFileStatus() != FILE_OK)
		{
			throw(TException_t<long>(0, __LINE__, __FILE__,__func__,"OPEN_FILE_ERROR"));
		}
		
		if(ferror((FILE*)GetFilePtr()))
		{
			//string errno_msg(strerror(retval));
			throw(TException_t<long>(0, __LINE__, __FILE__,__func__, "READ_ERR"));
		}
		else
		{
			fread(m_rwAdress , size_t(len), 1, this->m_pFile);
			//check fwrite retval and update file status respictevly
			
		}
		return;
			
	}
	else if('W')
	{
		if(this->GetFileStatus() != FILE_OK)
		{
			throw(TException_t<long>(0, __LINE__, __FILE__,__func__,"OPEN_FILE_ERROR"));
		}
		
		//string errno_msg(strerror(retval));
		if(ferror((FILE*)GetFilePtr()))
		{
			throw(TException_t<long>(0, __LINE__, __FILE__,__func__, "WR_ERR"));
		}
		
		else
		{
			fwrite(m_rwAdress ,  size_t(len), 1, this->m_pFile);
			//check fwrite retval and update file status respictevly
			
		}
		return;
	}
	else
	{
		//throw exception
		throw(TException_t<long>(0, __LINE__, __FILE__,__func__, "INVALID_RW_BINARY_FLAG"));
	}
}












