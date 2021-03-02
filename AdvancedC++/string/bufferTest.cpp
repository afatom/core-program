#include "mu_test.h"
#include <cstdio>
#include "buffer.h"
#include <iostream>
 
using namespace std;


UNIT(Create_Buffer_Test)
	using namespace advcpp::detail;
	Buffer<char>* buf1 = new Buffer<char>(16);
	Buffer<char>* buf2 = new Buffer<char>;
	
	ASSERT_THAT(buf1 != 0);
	ASSERT_THAT(buf2 != 0);

	delete buf1;
	delete buf2;
END_UNIT


UNIT(Buffer_Capacity_Test)
	using namespace advcpp::detail;
	Buffer<char>* buf1 = new Buffer<char>(64);
	Buffer<char>* buf2 = new Buffer<char>;
	
	ASSERT_THAT(buf1 != 0);
	ASSERT_THAT(buf1->capacity() == 64);

	ASSERT_THAT(buf2 != 0);
	ASSERT_THAT(buf2->capacity() == 16);

	delete buf1;
	delete buf2;
END_UNIT

UNIT(Buffer_Copy_Ctor_Test)
	using namespace advcpp::detail;
	Buffer<char> buf1 = Buffer<char>(64);
	Buffer<char> buf2 = Buffer<char>();
	
	Buffer<char> buf3 = Buffer<char>(buf1);
	ASSERT_THAT(buf1.capacity() == 64);
	ASSERT_THAT(buf3.capacity() == 64);
	ASSERT_THAT(buf2.capacity() == 16);

END_UNIT


TEST_SUITE(Generic Buffer Unit Test)
	TEST(Create_Buffer_Test)
	TEST(Buffer_Capacity_Test)
	TEST(Buffer_Copy_Ctor_Test)
END_SUITE