/*
 * op[ ].cpp
 * Copyright 2018 adhamfaris <adhamfaris@localhost.localdomain> 
 */


#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;


class person{
	public:
	person(){age = 0; name = new char[8]; name[0]='\0';}
	~person(){delete[]name;}
	person& operator = (const person& per){age = per.age; delete [] this->name; name = new char[strlen(per.name)]; strcpy(name,per.name); return *this;}
	person(const person& per){age = per.age; name = new char[strlen(per.name)]; strcpy(name,per.name);} 
	person(const char* _name){age = 0; name = new char[strlen(_name)]; strcpy(name,_name);}
	const char* getname()const{return name;}
	int getage()const{return age;}
	private:
	int age;
	char* name; 
	
	};

ostream& operator << (ostream& os, const person& per){
	os<<per.getname()<<endl;
	os<<per.getage();
	return os;
	}


int main(int argc, char **argv)
{
	person p1("zake");
	cout<<p1<<endl;
	return 0;
}

