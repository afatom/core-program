
#include <iostream>

using namespace std;

class base{
    public:
    virtual bool foo()const{cout<<"base"<<endl; return true;}
};

class derived:public base{
    public:
    virtual bool foo(){
        cout<<"Deribed foo"<<endl; return true;
    }
};



void func(const base& b){
    if(b.foo()==true){cout<<"*"<<endl;}
}




int main()
{
    derived d;
    derived &ir=d;
    
    base b; 
    func(d);
    return 0;
}
