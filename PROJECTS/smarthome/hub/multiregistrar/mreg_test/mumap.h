#ifndef _MUMAP_H_
#define _MUMAP_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef map <string, map <string, map <string, vector <int*> > > > my_multimap;

class X{
	private:
	my_multimap* mymap;
	
	
	public:
	X(){mymap = new my_multimap;}
	~X(){delete mymap;}
	
};





#endif //_MUMAP_H_
