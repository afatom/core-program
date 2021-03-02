#include <mstring.h>

using namespace std;

int main(void)
{
    String_t y("adham");
    y.ToUpper();
    const char* ptr = y.C_Str();
    cout<<ptr<<endl;
    

    y.ToLower();
    ptr = y.C_Str();
    cout<<ptr<<endl;
    
    y.Reverse();
    ptr = y.C_Str();
    cout<<ptr<<endl;
    
    y.Concat(y);
    ptr = y.C_Str();
    cout<<ptr<<endl;

    String_t d("adham");
    d += '_';
    ptr = d.C_Str();
    cout<<ptr<<endl;

    
    return 0;
}