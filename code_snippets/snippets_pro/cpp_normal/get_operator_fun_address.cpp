//��ȡ operator()  ������ַ
#include <iostream>

struct cop{
  bool operator()(const int& a, const int& b) const
  {
    return a < b;
    //return true;
  }
};

int main()
{  
  bool (cop::*ff)(const int& a, const int& b) const;
  ff = &cop::operator();
  cop cop_temp;
  (cop_temp.*ff)(1,2););

  return 0;
}