/* 
  测试boost 中function使用：
*/
#include "boost_common.h"

class test_boost_function_class {
public:
  test_boost_function_class() {}
  ~test_boost_function_class() {}
  void do_something(int) {}
};

bool test_function_lib() {
  test_boost_function_class t1;
  // 1.类对象在调用位置传入
  boost::function<void(test_boost_function_class &, int)> f1 =
    boost::bind(&test_boost_function_class::do_something, boost::lambda::_1, boost::lambda::_2);
  f1(t1, 9);

  // 2.类对象在绑定时传入
  boost::function<void(int)> f2 =
    boost::bind(&test_boost_function_class::do_something, t1, boost::lambda::_1);
  f2(9);

  return true;
}