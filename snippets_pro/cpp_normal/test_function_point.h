//类函数 指针
//参考链接：https://stackoverflow.com/questions/1485983/calling-c-class-methods-via-a-function-pointer

#include "cplusplus_common_def.hpp"

class test_function_point1 {
public:
  test_function_point1() {}
  ~test_function_point1() {}
  void show() {
    int i = 0;
    std::cout << "i am show function" << std::endl;
  }
};

//高级应用
class test_function_point2 {
public:
  test_function_point2() {}
  ~test_function_point2() {}
  struct ff {
    void null() { std::cout << "i am class test2::ff function." << std::endl; }
  };

  typedef void (ff::*null)();
  operator null() {
    int i = 0;
    return &ff::null;
  }
  ff f1;
};

//获取 operator()  函数地址
struct cop {
  bool operator()(const int &a, const int &b) const {
    return a < b;
  }
};

void fun1() { std::cout << "fun1" << std::endl; }\

/*
**另一种定义函数指针方式:
*/
typedef void tp_func_point(int &i);
void incrNum(int &i) {
  i++; 
}
void show(tp_func_point *f1, int &input) { 
  f1(input); 
}

bool test_function_point() {
  test_function_point1 t1;
  void (test_function_point1::*p)() = NULL;
  p = &test_function_point1::show;
  (t1.*p)();

  test_function_point2 t2;
  void (test_function_point2::ff::*p1)() = NULL;
  p1 = t2;
  (t2.f1.*p1)();

  void (*p2)() = NULL;
  p2 = &fun1;
  (*p2)();

  // 测试获取 operator() 函数指针;
  bool (cop::*ff)(const int &a, const int &b) const;
  ff = &cop::operator();
  cop cop_temp;
  (cop_temp.*ff)(1, 2);

  // 传参函数指针参数给函数:
  tp_func_point *f1 = incrNum;
  int i = 0;
  show(f1, i);

  return true;
}