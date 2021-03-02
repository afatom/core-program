#include "string_t.h"
#include <iostream>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stddef.h>
#include "mu_test.h"
#include <stdlib.h>
using namespace std;

//#define DEBUG






UNIT(CTOR_Test)
	const char* str = "I love C++";
	const char* strr = "My dream is to become an excellent Embeded/RT Engineer! and making Facinating projects and systems!!";
	string_t strt1(str);
	string_t strt2;
	string_t strt3(strr);
	#ifdef DEBUG
	cout<<strt1<<endl;
	cout<<strt3<<endl;
	cout<<strt2<<endl;
	#endif
END_UNIT

UNIT(Get_String_t_Test)
	const char* str = "I love C++";
	const char* strr = "My dream is to become an excellent Embeded/RT Engineer! and making Facinating projects and systems!!";
	const char* get_str = NULL;
	const char* get_strr = NULL;
	
	string_t strt1(str);
	string_t strt2;
	string_t strt3(strr);
	
	get_str = strt1.GetStr();
	get_strr = strt3.GetStr();
	
	ASSERT_THAT(strcmp(get_str,str)==0);
	ASSERT_THAT(strcmp(get_strr,strr)==0);
END_UNIT

UNIT(StringLength_String_t_Test)
	const char* str = "I love C++";
	const char* strr = "My dream is to become an excellent Embeded/RT Engineer! and making Facinating projects and systems!!";
	
	string_t strt1(str);
	string_t strt2;
	string_t strt3(strr);
	
	ASSERT_THAT(strlen(str) == strt1.StrLength());
	ASSERT_THAT(strlen(strr) == strt3.StrLength());

END_UNIT

UNIT(Set_String_t_Test)
	const char* str = "I love C++";
	const char* strr = "My dream is to become an excellent Embeded/RT Engineer! and making Facinating projects and systems!!";
	const char* get_strt2 = NULL;
	const char* get_strt3 = NULL;
	string_t strt1(str);
	string_t strt2;
	string_t strt3(strr);
	
	strt2.SetStr(strr);
	get_strt2 = strt2.GetStr();
	get_strt3 = strt3.GetStr();
	ASSERT_THAT(strcmp(get_strt2,get_strt3)==0);
	
END_UNIT

UNIT(String_t_Compare_Test)	
	string_t strt1("C");
	string_t strt2("C");
	string_t strt3("F");
	string_t strt4("asd");
	string_t strt5("A");
	
	string_t& ir = strt1;
	
	ASSERT_THAT(strt2.String_tCompare(ir) == 0);
	ASSERT_THAT(strt3.String_tCompare(ir) == 2);	
	ASSERT_THAT(strt4.String_tCompare(ir) == 2);
	ASSERT_THAT(strt5.String_tCompare(ir) == 1);
END_UNIT


UNIT(Convert_String_t_To_UpperCase_And_To_LowerCase_Test)	
	string_t strt1("my name is adham and i am 32 years old!");
	void ConvStrToUpperCase();
	void ConvStrToLowerCase();
	#ifdef DEBUG
	strt1.ConvStrToUpperCase();
	cout<<strt1<<endl;
	strt1.ConvStrToLowerCase();
	cout<<strt1<<endl;
	#endif
	ASSERT_THAT(1==1);
END_UNIT


UNIT(String_t_Logical_Operators_Test)	
	string_t strt1("ABC");
	string_t strt2("ABC");
	string_t strt3("bnm");
	string_t strt4("asd");
	string_t strt5("A");
	string_t strt6("age");
	
	string_t& ir2 = strt2;
	string_t& ir1 = strt1;
	string_t& ir3 = strt3;
	string_t& ir5 = strt5;
	string_t& ir6 = strt6;
	
	ASSERT_THAT(strt1.IsEqual(ir2)==true); 		// ==
	ASSERT_THAT(strt1.IsEqual(ir3)==false); 		// ==
	
	ASSERT_THAT(strt1.Isdefferent(ir2)==false);		// !=
	ASSERT_THAT(strt1.Isdefferent(ir3)==true);		// !=
	
	ASSERT_THAT(strt1.IsBigger(ir1)==false);
	ASSERT_THAT(strt1.IsBigger(ir2)==false);
	ASSERT_THAT(strt1.IsBigger(ir5)==true);
	
	ASSERT_THAT(strt5.IsSmaller(ir1)==true);
	ASSERT_THAT(strt1.IsSmaller(ir2)==false);
	ASSERT_THAT(strt1.IsSmaller(ir3)==true);
	
	
	ASSERT_THAT(strt1.IsBiggerOrEqual(ir3)==false);
	ASSERT_THAT(strt3.IsBiggerOrEqual(ir1)==true);
	ASSERT_THAT(strt1.IsSmallerOrEqual(ir3)==true);
	string_t strt10("my age is 32!");
	ASSERT_THAT(strt10.IsContains(ir2)==false);
	ASSERT_THAT(strt10.IsContains(ir6)==true);
	
END_UNIT


UNIT(String_t_Concat_And_Prepend_Test)	
	string_t strt1("Hey ");
	string_t strt2("you!");
	const char* concatString = "Hey you!";
	strt1.StrConcat("you!");
	string_t& stref = strt2;
	
	ASSERT_THAT(strcmp(concatString,strt1.GetStr())==0);
	strt1.StrConcat(stref);
	ASSERT_THAT(strcmp("Hey you!you!",strt1.GetStr())==0);
	
	string_t strt3("my");
	string_t strt4("C++");
	
	strt4.Prepend("my");
	ASSERT_THAT(strcmp("myC++",strt4.GetStr())==0);
	string_t& ref = strt4;
	
	strt3.Prepend(ref);
	ASSERT_THAT(strcmp("myC++my",strt3.GetStr())==0);
	
END_UNIT

UNIT(Get_First_And_Last_Occur_Test)
	string_t strt1("123456789101");
	int first = strt1.GetFirstOccur('1');
	int last = strt1.GetLastOccur('1');
	ASSERT_THAT(first==0);
	ASSERT_THAT(last==11);
END_UNIT

UNIT(String_t_Operators_Test)
	string_t strt2("1234");
	string_t strt1("1");
	string_t& ir = strt2;
	strt1.operator=(ir); //assignment operator
	ASSERT_THAT(strcmp(strt1.GetStr(),"1234")==0);
	strt1.operator+=("1234");  //concat operator
	ASSERT_THAT(strcmp(strt1.GetStr(),"12341234")==0);
	strt1.operator+=(ir);  //concat operator
	ASSERT_THAT(strcmp(strt1.GetStr(),"123412341234")==0);
	string_t newStrt = strt1(0, 4);
	ASSERT_THAT(strcmp(newStrt.GetStr(),"1234")==0);
	
	string_t nstr("Hellow World!");
	
	ASSERT_THAT(nstr[0] =='H');
	ASSERT_THAT(nstr[5] =='w');
	ASSERT_THAT(nstr[100] =='\0');
	ASSERT_THAT(nstr[-90] =='\0');
	
	nstr[6]='.';
	ASSERT_THAT(strcmp(nstr.GetStr(),"Hellow.World!")==0);
	nstr[12]='@';
	ASSERT_THAT(strcmp(nstr.GetStr(),"Hellow.World@")==0);
END_UNIT

UNIT(String_t_CaseSens_Var_Test)
	
	string_t strt1("ADHAM");
	string_t strt2("adham");
	string_t& ir2 = strt2;
	ASSERT_THAT(strt1.GetCaseSensFlag()==true); //true=on
	strt1.SetCaseSens(false); //true=on false=off
	ASSERT_THAT(strt1.GetCaseSensFlag()==false); //true=on
	
	ASSERT_THAT(strt1.String_tCompare(ir2)==0);
END_UNIT

/*Main function Macro*/
TEST_SUITE(String_t_Class_Test)
    TEST(CTOR_Test)
    TEST(Get_String_t_Test)
    TEST(StringLength_String_t_Test)
    TEST(Set_String_t_Test)
    TEST(String_t_Compare_Test)	
	TEST(Convert_String_t_To_UpperCase_And_To_LowerCase_Test)	
	TEST(String_t_Logical_Operators_Test)
	TEST(String_t_Concat_And_Prepend_Test)
    TEST(Get_First_And_Last_Occur_Test)
    TEST(String_t_Operators_Test)
    TEST(String_t_CaseSens_Var_Test)
  
END_SUITE
