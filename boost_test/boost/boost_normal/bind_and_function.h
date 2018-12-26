// bind 测试
/*
bind中第二个参数
若是指针，则在内部不会调用对应的拷贝构造函数；否则要调用多次拷贝构造函数.
boost::lambda 参数只有3个，有限制，使用 _1 _2这种方式可以防止8个参数到bind中
*/
#include "boost_common.h"

class bind_and_fun_test {
public:
  bind_and_fun_test() {}
  bind_and_fun_test(const bind_and_fun_test &p) {}
  ~bind_and_fun_test() {}
  void do_something1(int &i, int &j) {
    i = 9;
    j = 11;
  }
  void do_something2(int &x_, int &y_, int &z_, int &f_, int &g_, int &h_,
    int &i_, int &j_) {
      x_ = 7;
      y_ = 7;
      z_ = 7;
      f_ = 7;
      g_ = 7;
      h_ = 7;
      i_ = 7;
      j_ = 7;
  }
  // 第三种方式
  void bind() {
    int x = 0, y = 0;
    //test1 *p = this;
    boost::bind(&bind_and_fun_test::do_something1, this, boost::lambda::_1,
      boost::lambda::_2)(x, y);
  }
};

bool test_bind_and_funcion() {
  bind_and_fun_test t1;
  int x = 0, y = 0, z = 0, f = 0, g = 0, h = 0, i = 0, j = 0;

  // 1.常规使用 boost 的bind + function方式:
  t1.bind();
  boost::function<void(int&, int&)> fun1(boost::bind(&bind_and_fun_test::do_something1, &t1,
    boost::lambda::_1,
    boost::lambda::_2)); 
  fun1(x, y);

  // 2.绑定并调用，使用了 boost::lambda::_? 会有占位参数限制
  // bind中第二个参数
  // 若是指针，则在内部不会调用对应的拷贝构造函数；否则要调用多次拷贝构造函数
  boost::bind(&bind_and_fun_test::do_something1, /*t1*/&t1, boost::lambda::_1, boost::lambda::_2)(x, y);
  ///TODO 如下调用为何会调用 拷贝构造函数7次这么多???
  boost::bind(&bind_and_fun_test::do_something1, t1, boost::lambda::_1, boost::lambda::_2)(x, y);
  int temp = 0;

  // 3.绑定并调用，使用了 _? 可以增加到8个占位参数
  // 这种方式 可以解决 boost::lambda 只能定义三个参数问题了
  //  (即 boost::lambda::_1、 boost::lambda::_2、 boost::lambda::_3)
  // 可以用_1 ~ _8 定义超过三个占位参数
  boost::bind(&bind_and_fun_test::do_something2, &t1, _1, _2, _3, _4, _5, _6, _7,
    _8)(x, y, z, f, g, h, i, j);
  return true;
}