﻿//模仿bind例子(非模板)
#include "cplusplus_common_def.hpp"

// header file.
//#include <iostream>
//#include <vector>

namespace {
class placeholder {};
placeholder _1;
} // namespace

class Test {
public:
  Test() {}
  Test(const Test &p) {}
  ~Test() {}
  void do_stuff(const std::vector<int> &v) {
    std::vector<int>::const_iterator it = v.begin();
    for (; it != v.end(); ++it) {
      std::cout << *it << std::endl;
    }
  }
};

class simple_bind_t {
  typedef void (Test::*fn)(const std::vector<int> &);
  fn fn_;
  Test t_;

public:
  simple_bind_t(fn f, const Test &t) : fn_(f), t_(t) { int i = 0; }
  ~simple_bind_t() { int i = 0; }

  void operator()(const std::vector<int> &a) { return (t_.*fn_)(a); }
};

simple_bind_t simple_bind(void (Test::*fn)(const std::vector<int> &),
                          const Test &t /*, const placeholder&*/) {
  return simple_bind_t(fn, t);
}

bool test_non_boost_bind_example() {
  Test t;
  // boost::shared_ptr<Test> ptr_test = boost::make_shared<Test>();
  std::vector<int> vec;
  vec.push_back(42);
  simple_bind(&Test::do_stuff, t /*, _1*/)(vec); //等同于下面2行代码逻辑
  // boost::function<void(const std::vector<int>&)>
  // f(simple_bind(&Test::do_stuff, *ptr_test, _1)); ptr_test.reset(); //绑定完后
  // 就算对象析构掉后，f调用也没问题。 f(vec);
  return true;
}