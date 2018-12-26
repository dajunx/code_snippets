
// tuple 测试，库功能：更易于定义返回多个数值的函数
#include "boost_common.h"

boost::tuple<int, double> fun_return_tuple_value() { 
  return boost::make_tuple(1, 1.5); 
}

class tuple_child_class {
public:
  tuple_child_class() {}
  tuple_child_class(const tuple_child_class &a) {}
  virtual ~tuple_child_class(){};
  virtual void test() { std::cout << "tuple_child_class::test()\n"; }
};

class tuple_parent_class : public tuple_child_class {
public:
  tuple_parent_class() {}
  tuple_parent_class(const tuple_parent_class &a) {}
  virtual void test() { std::cout << "tuple_parent_class::test()\n"; }
};

bool test_tuple() {
  // 1.构造对象
  boost::tuple<int, int, std::string> tuple_test1(1, 2, "lin");
  boost::tuple<int, int, std::string> tuple_test2;
  tuple_test2 = boost::make_tuple(1, 2, "jun");

  //参数为自定义类型
  boost::tuple<int, std::string, tuple_parent_class> tuple_test3(-5, "Tuples");
  boost::tuple<unsigned int, std::string, tuple_child_class> tuple_test4;
  tuple_test4 = tuple_test3;
  tuple_test3.get<2>().test();
  tuple_test4.get<2>().test();

  // 另外一种构造 tuple对象方式
  typedef boost::tuple<int, int> tuple_pair;
  int aaa = 1, bbb = 1;
  tuple_pair tuple_test5 = boost::tie(aaa, bbb);
  // To use tuples with streams, include the header file boost/tuple/tuple_io.hpp
  std::cout<<"print a tuple"<<tuple_test5<<std::endl;


  // 2.赋值
  boost::tuple<int, int, std::string> tuple_test6(10); //初始化部分值，其余部分填充默认值
  tuple_test6 = boost::make_tuple(1, 2, "jian"); // 初始化值后，还可以继续赋值，赋值会抹掉以前的数据；
  tuple_test6.get<2>() = "lin"; // 修改其中单个值


  // 3.取值
  int a = boost::tuples::get<0>(tuple_test6);
  int b = boost::tuples::get<1>(tuple_test6);
  std::string temp = boost::tuples::get<2>(tuple_test6);

  // 遍历元素
  int head = tuple_test6.get_head();
  int tailhead = tuple_test6.get_tail().get_head();
  std::string tail = tuple_test6.get_tail().get_tail().get_head();

  // 4.tuple 在函数返回值中使用
  boost::tuple<int, double> tuple_test7 = fun_return_tuple_value();

  // 5.对象之间的对比
  // 必须包含 boost/tuple/tuple_comparison.hpp
  std::cout<<"two tuple is same? " << (tuple_test1 == tuple_test2) << std::endl;
  tuple_test2 = boost::make_tuple(1, 2, "lin");
  std::cout<<"two tuple is same? " << (tuple_test1 == tuple_test2) << std::endl;

  // url 参考
  // https://theboostcpplibraries.com/boost.tuple

  return true;
}
