#include <TException_t.h>
#include <iostream>
#include <string>


using namespace std;
void foo(void)
{
	int myobj = 1024;
<<<<<<< HEAD
<<<<<<< HEAD
	string msg("Main Exception Msg");
	
	TException_t<int> obj(myobj, __LINE__, __FILE__, msg);
	throw(obj);
=======
	string msg = "Main Exception Msg";
	
	throw(TException_t<int> (myobj, __LINE__, __FILE__,msg));
>>>>>>> 2896f5c0b4056294fd05add5442a4dbe79a314c8
=======

	string msg = "Err msg";
	//string& ref = msg;
	throw(TException_t<int>(myobj, __LINE__, __FILE__,__func__,msg));

>>>>>>> 332bdfa8ba87f9dd98f0424b3c2ac373594371bd
}

int main (int argc, char* argv[])
{
	try {
		foo();
	}
	catch(TException_t<int> obj)
	{
		cout<<"Catch Function Activated.."<<endl;
		cout<<"Thrown Object value: "<<obj.GetObject()<<endl;
		cout<<"At Line Number: "<<obj.GetLineNUmber()<<endl;
		cout<<"At File: "<<obj.GetFileName()<<endl;
		cout<<"Msg: "<<obj.GetExceptionMsg()<<endl;
	}
	
	
	return 0;
}
