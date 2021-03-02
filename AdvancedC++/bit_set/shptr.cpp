
#include "shptr.h"
#include "mu_test.h"
#include <stdio.h> //mutest

UNIT(Create_SHPointer_Test)
	ShPointer<int> smart_ptr(new int);
END_UNIT


UNIT(Ref_SHPointer_Test)
	ShPointer<int> smart_ptr1(new int);
	ShPointer<int> smart_ptr2(smart_ptr1);
	*smart_ptr1 = 10;
	std::cout<< *smart_ptr1<<" "<<std::endl;
	*smart_ptr2 = 20;
	std::cout<< *smart_ptr2<<" "<<std::endl;
END_UNIT

TEST_SUITE(SHPointer Unit Test)
	TEST(Create_SHPointer_Test)
	TEST(Ref_SHPointer_Test)
END_SUITE