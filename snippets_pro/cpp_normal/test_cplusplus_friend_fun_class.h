//友元函数 友元类
#include "cplusplus_common_def.hpp"

class test {
public:
  test() {}
  ~test() {}

private:
  void doSomeThing() { int i = 0; }
  // 友元函数
  friend void do_private_fun(test *pT);
  // 友元类
  friend class test_friend;
};

class test_friend {
public:
  test_friend() {}
  ~test_friend() {}
  void do_class_private_fun(test *pT) { pT->doSomeThing(); }
};

void do_private_fun(test *pT) { pT->doSomeThing(); }

bool test_cplusplus_friend_usage() {
  test tt;
  do_private_fun(&tt);

  test_friend tf;
  tf.do_class_private_fun(&tt);

  return true;
}