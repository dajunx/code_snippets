//boost function  ʡ�Բ�����ʹ�÷���

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/cstdint.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

void fun2(int a)
{
  int i = 0;
}

void fun1(boost::function<void()> p_fun)
{
  if (p_fun) {
    p_fun();
  }
}

int main()
{
  boost::function<void()> fun_ = boost::bind(&fun2, 5);
  boost::function<void()> nullfun;
  fun1(nullfun);
  fun1(fun_);

  return 0;
}