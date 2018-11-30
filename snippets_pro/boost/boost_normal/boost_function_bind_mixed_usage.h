// boost function bind 混合使用

#include "boost_common.h"

void mix_use_bind(int i, int j) {
  std::cout << "fun1 i:" << i << ", j:" << j << std::endl;
}

bool test_boost_function_bind_mixed_usage () {
  boost::function<void(int, int)> ff =
      boost::bind(&mix_use_bind, boost::lambda::_1, boost::lambda::_2);
  boost::function<void(int)> ff1 = boost::bind(ff, 9, boost::lambda::_1);
  ff1(10);

  int i = 0;

  return true;
}