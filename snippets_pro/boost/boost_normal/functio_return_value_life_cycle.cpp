//函数返回值的生命周期
#include "boost_common.h"

typedef boost::shared_ptr<int> PTR_INT;
PTR_INT ptr_int;

inline PTR_INT fun2();
PTR_INT fun1() { return fun2(); }

PTR_INT fun2() { return ptr_int; }

bool test_functio_return_value_life_cycle() {
  ptr_int = boost::make_shared<int>(9);
  fun1();

  return true;
}