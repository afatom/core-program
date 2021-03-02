
#include <iostream>
#include <vector>
#include <algorithm>


typedef int (*fn)(int);

int myfunction (int i) {  // function:
  static int count=0;  
  count+= i;
  return count;
}



class Counter{
public:
  Counter() : m_counter(0){}
  void operator() (int i) {m_counter += i;}
  int getcount() const {return m_counter;}  

private:
  int m_counter; 
};


int main()
{
    
    std::vector<int> vec;
    
    vec.push_back(10);
    vec.push_back(10);
    vec.push_back(10);
    
    vec.push_back(20);
    vec.push_back(40);
    vec.push_back(50);

    
    //for_each (vec.begin(), vec.end(), myfunction);
    //std::cout<< myfunction(0);  

    Counter c1 = for_each (vec.begin(), vec.end(), c1);
    std::cout<<c1.getcount()<<std::endl;
    

    return 0;
}
