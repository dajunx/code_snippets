/*
参照 effective c++ item.17
c++函数调用参数 并不总是以特定次序完成函数参数的核算，如27、48行代码的调用顺序
*/

#include "cplusplus_common_def.hpp"
// header file.
//#include <iostream>

class Man {
public:
  Man() { int i = 0;}
};

int right() {
  //throw 0;
  return 5;
}

int left(Man* m) {
  return 4;
}

void fun2(int a, int b) { int c = 0; }

int ParameterFun1() {
  return 1;
}

int ParameterFun2(int a) {
  return 1;
}

int ParameterFun3() {
  return 1;
}

void parent_fun(int a, int b) {
  int i = 0;
}

bool test_cplusplus_fun_para_not_in_order() {
  /**
   * not_in_order
   * parent_fun 函数参数调用顺序 3 -> 1 -> 2
   */
  parent_fun(ParameterFun2(ParameterFun1()), ParameterFun3());

  /**
   * not_in_orde2
   * fun2 函数参数调用顺序 new Main -> right ->left
   */
  fun2(left(new Man()), right());

  return 0;
}