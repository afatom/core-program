
#include <iostream>
#include <string>
//#include <limits.h>
#include <assert.h>
#include <virtIO_t.h>
#include <asciiIO_t.h>
#include <binIO_t.h>
#include <stdio.h>
#include <iomanip>      // std::setw


#define TYPE int
#define LINE_MAX 1024
using namespace std;

int test(VirtIO_t& _virtIO)
{
	int cont = 1;			// trigger to stop loop	
	unsigned int option;

    string status[] = {"FILE_OK",
		"OPEN_FILE_ERROR",
		"BAD_ACCESS",
		"WR_ERR",
		"READ_ERR"};
        
	while (cont)
	{
		try
		{
			cout << "Choose option:" << endl;
			cout << "	1:  Open New File" << endl;
			cout << "	2:  Close File" << endl;
			cout << "	3:  Get File Path" << endl;
			cout << "	4:  Get File current Access Mode" << endl;
			cout << "	5:  Get File Length" << endl;
			cout << "	6:  Get File Error Status" << endl;
			cout << "	7:  Get File Cursor Position" << endl;
			cout << "	8:  Set File Cursor Position" << endl;
			cout << "	9:  ascii Write" << endl;
			cout << "	10: ascii Read " << endl;

			cout << "	11: Binary Write " << endl;
			cout << "	12: Binary Read " << endl;

			cout << "	Any other number - exit " << endl;
			
			
			cin >> option;
			system("clear");
			system("Test IO");
			switch(option)
			{
				case 1:
				{
					string path;
					string mode;

					cout << "Plz enter filePath: ";
					cin >> path;
					cout << endl;

					cout << "Plz enter open mode: ";
					cin >> mode;
					cout << endl;

					_virtIO.FileOpen(path, mode);
					break;
				}
				case 2:
				{
					_virtIO.FileClose();

					break;
				}
				case 3:
				{
					cout << _virtIO.GetFilePath() << endl;

					break;
				}
				case 4:
				{
					cout << _virtIO.GetFileAccess() << endl;

					break;
				}
				case 5:
				{
					cout << _virtIO.GetFileLength() << endl;

					break;
				}
				case 6:
				{
					cout << status[_virtIO.GetFileStatus()] << endl;

					break;
				}
				case 7:
				{
					cout << _virtIO.GetPos() << endl;

					break;
				}
				case 8:
				{
					long newPosition;

					cout<<"Enter new cursor position: ";
					cin >> newPosition;
					//cout<<"Set SeekRelative flag (REL_BEG = 0  REL_CUR = 1  REL_END = 2)";
					int flag=0;
					cin>>flag;
					//SeekRelative seek_flag = (SeekRelative)flag;
					//enum SeekRelative sf = 0;
					_virtIO.SeekPos(newPosition, SEEK_SET);
					break;
				}
				case 9:
				{
					TYPE value;
					
					cout << "Plz enter your value: " << endl;
					cin >> value;

					_virtIO << value;

					break;
				}
				case 10:
				{
					TYPE value;
					_virtIO >> value;
					cout << value << endl;
					
					break;
				}
				case 11:
				{
		
				    char txt[1024];
					cout<<"Enter your text here(White space)"<<endl;
					cin >> setw(1024) >> txt;
					
					//cout << strlen(value) << endl;
					*((BinIO_t*)&_virtIO)<<txt,sizeof(txt);
					break;
				}
				case 12:
				{
					_virtIO.FileClose();
					
					string mode = "rb";
					_virtIO.FileOpen(_virtIO.GetFilePath(),mode);
					_virtIO.Home();
				    char buf[1024];
				    //char rtxt[1024];
					//*((BinIO_t*)&_virtIO) >> buf, (int)(_virtIO.GetFileLength());
					*((BinIO_t*)&_virtIO)>>buf,sizeof(buf);
					//string str(buf);
					cout << buf << endl;
					
				    break;
				}

				default: cont = 0;	
					 break;
			}
		}

		catch(TException_t<long> obj)
		{
			cout<<"Catch Function Activated.."	<<endl;
			cout<<"Thrown Object value: "<<obj.GetObject()<<endl;
			cout<<"At Line Number: "<<obj.GetLineNUmber()<<endl;
			cout<<"At File: "<<obj.GetFileName()<<endl;
			cout<<"At Function: "<<obj.GetFunc()<<endl;
			
			cout<<"Msg: "<<obj.GetExceptionMsg()<<endl;
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{


	int cont = 1;			// trigger to stop loop	
	unsigned int option;
    string path(" ");
	string mode(" ");
	
	while (cont)
	{
		cout << "Choose option:" << endl;
		cout << "	1: Open ASCII File" << endl;
		cout << "	2: Open Binary File" << endl;

		cout << "	Any other number - exit " << endl;

		cin >> option;
		system("clear");
		system("Test I/O");
		switch(option)
		{
			case 1:
			{
				cout << "Plz enter filePath: ";
				cin >> path;
				cout << endl;

				AsciiIO_t * aIO = new AsciiIO_t(path, "a+");

				test(*aIO);

				break;
			}

			case 2:
			{
				cout << "Plz enter filePath: ";
				cin >> path;
				cout << endl;

				BinIO_t * bIO = new BinIO_t(path, "wb");

				test(*bIO);
				break;
			}

			default: cont = 0;	
					 break;
		}
		
	}

	return 0;
}

