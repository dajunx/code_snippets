// boost 协程例子
/*
结果:
foo1 1
foo2 101
foo2 3
*/
#include "boost_common.h"
///TODo 搁置，待以后在补足 2018.11.29 ljj
/*
boost::asio::coroutine c;

void foo(int i) {
  reenter(c) {
    yield std::cout << "foo1 " << i << std::endl;
    fork foo(100);
    yield std::cout << "foo2 " << i + 1 << std::endl;
  }
}

bool test_coroutine() {
  foo(1);
  foo(2);
  foo(3);

  return true;
}
*/