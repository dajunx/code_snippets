// atomic 原子变量
// link: http://www.boost.org/doc/libs/1_53_0/doc/html/atomic.html
#include "boost_common.h"

// boost::atomic<int> a(0);
int a(0);

void atomic_fun() {
  for (int i = 0; i < 10000; ++i) {
    ++a;
  }
}

bool test_atomic() {
  for (int i = 0; i < 100; i++) {
    boost::thread t1(atomic_fun);
    boost::thread t2(atomic_fun);
    t1.join();
    t2.join();
    if (a != 20000) {
      std::cout << a << '\n';
    }
    a = 0;
  }

  return true;
}