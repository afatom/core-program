#include "string_t.h"
#include <iostream>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stddef.h>
#include "mu_test.h"

using namespace std;



int main()
{
	const char* ptr;
	string_t str3;
	string_t str1("ALEX");
	string_t str2("Adham");
	int cmp;
	string_t& ir = str2;
	
	string_t str4(str1);
	
	//Print and strlen test
	size_t  len1 = str1.StrLength();
	str1.Print();
	str2.Print();
	printf("%lu\n",len1);
	
	//get test
	ptr = str1.GetStr();
	printf("%s\n",ptr);
	
	//DCTOR
	str3.Print();

	//Set Test
	str3.SetStr("Hadeel is my love");
	str3.Print();
	
	//compare
	cmp  = str1.String_tCompare(ir);
	cout<<"cmp = "<<cmp<<endl;
	
	//tolower case
	cout<<"Before Lower case"<<endl;
	str1.Print();
	str1.ConvStrToLowerCase();
	str1.Print();
	
	
	//toupper case
	cout<<"Before upper case"<<endl;
	str1.Print();
	str1.ConvStrToUpperCase();
	str1.Print();
	
	//precat from char*
	cout<<"Before Prepend case"<<endl;
	str1.Print();
	str1.Prepend("01472589633698521478522qweerrttyyuuuiiioooppp{{{{}}}}}");
	str1.Print();

	//precat from string_t
	cout<<"Before Prepend case"<<endl;
	str2.Print();
	str2.Prepend(str3);
	cout<<"after Prepend case"<<endl;
	str2.Print();

	
	str2 += (str2.GetStr());
	str2.Print();
	
	//create new obj
	string_t str5;
	str5.SetStr("Rambo");
	str5.Print();
	str5 += ("is silvister stalone");  //concat operator
	str5.Print();
	
	
	
	string_t str6;
	str6.SetStr("Alesher");
	
	string_t str7;
	str7.SetStr("alsha3er");
	
	str6 += str7;
	str6.Print();
	
	
	
	str7.SetStr("foofoo");
	str6.SetStr("foofoo");
	
	
	
	bool iseq = str7.IsEqual(str6);
	cout<<"isEqual = "<<iseq<<endl;
	
	cout<<str7;
	cout<<"Scan string to str7"<<endl;
	cin>>str7;
	cout<<str7;
	
	/*
	char x;
	x = str7[0];
	cout<<"X val:"<<x<<endl;
	*/
	string_t str8;
	str8.SetStr("lotanza");
	int last =0;
	
	last = str8.GetLastOccur('a');
	cout<<"Index of F:"<<last<<endl;
	
	
	//substring test
	string_t str9="123456789";
	cout<<str9;
	string_t str10 = str9(3,3);
	cout<<str10;
	
	
	
	
	return 0;
}
