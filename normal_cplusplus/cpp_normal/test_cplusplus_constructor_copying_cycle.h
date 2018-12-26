// c++ 赋值操作符 和 拷贝构造 产生的问题

#include "cplusplus_common_def.hpp"

struct test1 {
  int x;
  test1(int w = 0) { x = w; }

  //如下若值返回，则会在copying 和 构造函数中循环
  // const test1 operator=(const test1& o) {
  const test1 &operator=(const test1 &o) {
    x = o.x;
    return *this;
  }
  test1(const test1 &o) { *this = o; }
};

bool test_constructor_copy_cycle() {
  test1 tt1(5);
  test1 tt2 = tt1;
  return true;
}