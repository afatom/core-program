
#include <iostream>

using namespace std;



void printbin(unsigned int* bin)
{
    int bits = (int)sizeof(unsigned int)*8;
    unsigned int mask = 1;
    unsigned int temp=*bin;
    mask <<= bits-1;
    while(bits){

        (mask & temp) ? (cout<<"1 "):(cout<<"0 ");
        temp<<=1;
        --bits;
    }
}

int main()
{
   // cout<<"Hello World";
    
    unsigned int res= 0;
    const char* str="00000111";
    //11010001
    unsigned int mask = 1;
    unsigned char v=128;
    res |= v;


    int i=7;
    while(i>=0){
        res |= mask & (str[i] - '0');
        //res |= mask & v;
        mask <<= 1;
        mask |=1;
        --i;
    }
    
    cout<<res<<endl;
    printbin(&res);
    
    return 0;
}
