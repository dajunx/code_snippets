//类中类

#include "cplusplus_common_def.hpp"
//#include <iostream>

class test_inner_class {
public:
  test_inner_class() { impl_ptr = new impl(); }
  ~test_inner_class() {}

  class impl {
  public:
    impl() {}
    ~impl() {}
    int b;
  };
  impl *impl_ptr;

  void set_impl_value() { impl_ptr->b = 9; }
  int a;
};

bool test_class_in_class() {
  test_inner_class t1;
  t1.set_impl_value();
  
  return true;
}