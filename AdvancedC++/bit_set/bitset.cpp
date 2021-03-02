
#include "bitset.h"
#include <iostream>
 
int main(int argc, char const *argv[])
{
    /* code */
	BitSet<64> X("10001111");
    std::cout<<X<<std::endl;
    return 0;
}
