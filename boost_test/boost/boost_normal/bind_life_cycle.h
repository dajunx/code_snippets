// bind 生命周期的例子！
/*
bind绑定，写在函数调用位置，生命周期就会随着函数调度结束而结束，其他地方要使用该
bind绑定的代码段得值拷贝，而不能使用 const& 存储值。
eg: boost::bind(&bind_life_cycle_test1::call_back) 写在 fun2中，声明周期会随着函数调度完成而结束
*/

//精简版本:
#include "boost_common.h"

typedef boost::function<void()> test2_callback1;

class bind_life_cycle_test1 {
public:
  void registe_callback() {
    test2_callback1 const &ff = fun2(boost::bind(&bind_life_cycle_test1::call_back));
    ff();
  }
  test2_callback1 const &fun2(test2_callback1 const &f) { return f; }
  static void call_back() { int i = 0; }
};

bool bind_life_cycle_version1() {
  bind_life_cycle_test1 t1;
  t1.registe_callback();

  return true;
}