// i++ 与++i 操作符重载
/*
Time operator++();//重载++i;
Time operator++(int);//重载i++；
C++约定，后置自增/自减运算符增加一个int型参数。
*/

#include "cplusplus_common_def.hpp"

class test_operator_plusplus {
public:
  test_operator_plusplus() : x(0) {}
  test_operator_plusplus &operator++() {
    ++x;
    return *this;
  }

  test_operator_plusplus &operator++(int) {
    test_operator_plusplus t1(*this);
    ++this->x;
    return *this;
  }
  int x;
};

bool test_i_plusplus_i() {
  test_operator_plusplus t1;
  t1++;
  ++t1;

  return true;
}