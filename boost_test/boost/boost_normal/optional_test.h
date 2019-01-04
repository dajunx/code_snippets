
#include "boost_common.h"
// 参考url: https://blog.csdn.net/mmzsyx/article/details/8163259

bool test_optional() {
  boost::optional<int> op_int0; // 一个未初始化的optional对象
  boost::optional<int> op_int1(boost::none); // 同上，使用none赋予未初始化值
  assert(!op_int0);
  assert(op_int0 == op_int1);
  assert(op_int1.get_value_or(253) == 253); //获取可选值

  boost::optional<std::string> op_string("test"); //初始化为字符串test

  std::string str = *op_string; //用解引用操作符获取值
  std::cout<<str.c_str()<<std::endl;
  std::vector<int> vec_int(10);

  boost::optional<std::vector<int> &> op_vec_int(vec_int); //容纳一个容器的引用
  assert(op_vec_int);
  op_vec_int->push_back(5); // 使用箭头操作符操纵容器
  assert(op_vec_int->size() == 11);
  op_vec_int = boost::none;
  assert(!op_vec_int);

  return true;
}