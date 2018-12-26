// c++ 动态绑定 静态绑定
/*
pD->DoSomething(); pB->DoSomething(); 是静态绑定，调用各自类的成员函数。
而pD->vfun(); pB->vfun(); 是动态绑定的，都调用 D类的vfun函数。
*/
// url: http://blog.csdn.net/chgaowei/article/details/6427731

#include "cplusplus_common_def.hpp"
// header file.
//#include <iostream>

class B {
public:
  void DoSomething(){};
  virtual void vfun(){};
};

class C : public B {
public:
  void DoSomething(){};
  virtual void vfun(){};
};

class D : public B {
public:
  void DoSomething(){};
  virtual void vfun(){};
};

bool test_virtual_usage() {
  D *pD = new D();
  B *pB = pD;

  pD->DoSomething();
  pB->DoSomething();

  pD->vfun();
  pB->vfun();

  return true;
}