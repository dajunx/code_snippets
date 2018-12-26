//非boost库使用 function和bind

#include "cplusplus_common_def.hpp"
// header file.
//#include <functional>
//#include <iostream>

class test_non_boost_bind_and_function {
public:
  test_non_boost_bind_and_function() {}
  ~test_non_boost_bind_and_function() {}
  void do_something(int) {}
};

bool test_non_boost_function_bind_usage() {
  test_non_boost_bind_and_function t1;
  std::tr1::function<void(int)> f1 =
      std::bind(&test_non_boost_bind_and_function::do_something,
                t1, std::placeholders::_1);
  std::tr1::function<void(test_non_boost_bind_and_function &, int)> f2 
      = std::bind(&test_non_boost_bind_and_function::do_something, 
                  std::placeholders::_1, std::placeholders::_2);

  f1(9);
  f2(t1, 11);

  return true;
}