// boost function  省略参数的使用方法
#include "boost_common.h"

void fun2(int a) { int i = 0; }

void fun1(boost::function<void()> p_fun) {
  if (p_fun) {
    p_fun();
  }
}

bool test_function_bypass_parameter_usage() {
  boost::function<void()> fun_ = boost::bind(&fun2, 5);
  boost::function<void()> nullfun;
  fun1(nullfun);
  fun1(fun_);

  return true;
}