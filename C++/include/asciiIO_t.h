#ifndef __ASCII_T_H_
#define __ASCII_T_H_






using namespace std;

class AsciiIO_t:public VirtIO_t{
	
	public:
	AsciiIO_t(){};
	virtual ~AsciiIO_t(){}
	
	AsciiIO_t(const string& _fileName, const string& _mode):VirtIO_t(_fileName,_mode){;}
	AsciiIO_t& operator << (int _val){return Write<int>(_val, "%d");}
	AsciiIO_t& operator << (char _val){return Write<char>(_val, "%c");}
	AsciiIO_t& operator << (short _val){return Write<short>(_val, "%d");}
	AsciiIO_t& operator << (long _val){return Write<long>(_val, "%ld");}
	AsciiIO_t& operator << (float _val){return Write<float>(_val, "%f");}
	AsciiIO_t& operator << (double _val){return Write<double>(_val, "%f");}
	AsciiIO_t& operator << (unsigned int  _val){return Write<unsigned int>(_val, "%u");}
	AsciiIO_t& operator << (unsigned char  _val){return Write<unsigned char>(_val, "%u");}
	AsciiIO_t& operator << (unsigned short  _val){return Write<unsigned short>(_val, "%u");}
	AsciiIO_t& operator << (unsigned long _val){return Write<unsigned long>(_val, "%lu");}

	/**********************************************************************/
	AsciiIO_t& operator >> (int &_val){return Read<int>(_val, "%d");}
	AsciiIO_t& operator >> (char &_val){return Read<char>(_val, "%c");}
	AsciiIO_t& operator >> (short &_val){return Read<short>(_val, "%hd");}
	AsciiIO_t& operator >> (long &_val){return Read<long>(_val, "%ld");}
	AsciiIO_t& operator >> (float &_val){return Read<float>(_val, "%f");}
	AsciiIO_t& operator >> (double &_val){return Read<double>(_val, "%lf");}
	AsciiIO_t& operator >> (unsigned int &_val){return Read<unsigned int>(_val, "%u");}
	AsciiIO_t& operator >> (unsigned char &_val){return Read<unsigned char>(_val, "%cu");}
	AsciiIO_t& operator >> (unsigned short &_val){return Read<unsigned short>(_val, "%hu");}
	AsciiIO_t& operator >> (unsigned long &_val){return Read<unsigned long>(_val, "%lu");}
	
	
	private:
	AsciiIO_t(const AsciiIO_t&);
	AsciiIO_t& operator = (const AsciiIO_t&);
	
	template<typename T>
	AsciiIO_t& Write(const T& _type, const char* _format);
	
	template<typename T>
	AsciiIO_t& Read(T& _type, const char* _format);
	
	
	};
#endif //__ASCII_T_H_


template<typename T>
AsciiIO_t& AsciiIO_t::Write(const T& _type, const char* _format)
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
		fprintf(this->m_pFile, _format, _type);
		
	}
	return *this;
}



template<typename T>
AsciiIO_t& AsciiIO_t::Read(T& _type, const char* _format)
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
		fscanf(this->m_pFile, _format, &_type);
		
	}
	return *this;
}







