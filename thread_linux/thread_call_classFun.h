/*
  linux下线程测试调用 class的成员函数：
    限制：线程只能绑定 static类型的成员函数；还有若想在线程函数中访问类的
  非static成员，必须传递类对象进来
  参考链接：https://stackoverflow.com/questions/1151582/pthread-function-from-a-class
*/

class test_call_class {
public:
  static void *fun1(void *arg) {
    test_call_class *p1 = (test_call_class *)arg;
    std::cout << "fun1 called." << std::endl;
    p1->show();
    return (void *)0;
  }
  void show() { std::cout << "show call" << std::endl; }
};

int test_call_classFun() {
  pthread_t t1;
  void *res;
  int s;

  test_call_class tt1;
  s = pthread_create(&t1, NULL, &test_call_class::fun1, &tt1);
  s = pthread_join(t1, &res);

  return 0;
}