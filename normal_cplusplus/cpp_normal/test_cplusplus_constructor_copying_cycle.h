// c++ 赋值操作符 和 拷贝构造 产生的问题

#include "cplusplus_common_def.hpp"

struct test_constructor_copying_cycle {
  int x;
  test_constructor_copying_cycle(int w = 0) { x = w; }

  //如下若值返回，则会在copying 和 构造函数中循环
  // const test1 operator=(const test1& o) {
  const test_constructor_copying_cycle &operator=(const test_constructor_copying_cycle &o) {
    x = o.x;
    return *this;
  }
  test_constructor_copying_cycle(const test_constructor_copying_cycle &o) { *this = o; }
};

bool test_constructor_copy_cycle() {
  test_constructor_copying_cycle tt1(5);
  test_constructor_copying_cycle tt2 = tt1;
  return true;
}