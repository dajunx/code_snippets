//������

#include <iostream>

class test1
{
public:
  test1() {
    impl_ptr = new impl();
  }
  ~test1() {}

  class impl
  {
  public:
    impl() {}
    ~impl() {}
    int b;
  };
  impl* impl_ptr;

  void set_impl_value()
  {
    impl_ptr->b = 9;
  }
  int a;
};

int main()
{
  test1 t1;
  t1.set_impl_value();
  return 0;
}

//------------------------------------------------
  //2����ֿ��������������cpp��:
//test.cpp:

#include <iostream>
#include "test.h"
#include "impl.h"

test1::test1() {
  impl_ptr = new impl();
}

void test1::set_impl_value()
{
  impl_ptr->b = 9;
}

int main()
{
  test1 t1;
  t1.set_impl_value();
  return 0;
}
//-----------------------

  //impl.h:

class impl
{
public:
  impl(){}
  ~impl() {}
  int b;
};
//-----------------------

  //test.h:

class impl;
class test1
{
public:
  test1();
  ~test1() {}

  void set_impl_value();

  impl* impl_ptr;
  int a;
};

//------------------------------------------------
//�����࣬test1���ж���impl�࣬impl�ඨ���������ط�:
//test.cpp:

#include <iostream>
#include "common1.h"
#include "common.h"

test1::test1(impl* ptr)
  :impl_ptr(ptr) 
{
}

void test1::set_impl_value()
{
  impl_ptr->b = 9;
  a = 9;
}

int main()
{
  test1::impl* p = new test1::impl();
  test1 t1(p);
  // here accept "test1::impl *" input
  t1.set_impl_value();
  return 0;
}

//--------------------------------
  //impl.h:

class test1::impl
{
  //friend class test1;
public:
  impl(){
    b = 9;
  }
  ~impl() {}
  int b;
};

//-------------------------------
  //test.h:

class test1
{
public:
  class impl;
  test1(impl* p);
  ~test1() {}

  void set_impl_value();

  impl* impl_ptr;
  int a;
};
