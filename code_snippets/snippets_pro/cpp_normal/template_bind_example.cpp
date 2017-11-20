//ģ��bind����(ģ�巽ʽ)
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>
#include <string>
namespace
{
  class placeholder {};
  placeholder _1;
  placeholder _2;
}

class Test
{
public:
  Test() {}
  Test(const Test& p) {}
  ~Test() {}
  void do_stuff(const std::vector<int>& v)
  {
    std::vector<int>::const_iterator it = v.begin();
    for (; it != v.end(); ++it) {
      std::cout << *it << std::endl;
    }
  }
  void do_something(int& i, int& j)
  {
    i = 9;
    j = 11;
  }
};
// 1 class ����������ͨ��const���÷�ʽ
template <typename R, typename T, typename Arg>
class simple_bind_t
{
  typedef R(T::*fn)(Arg);
  fn fn_;
  T t_;
public:
  simple_bind_t(fn f, const T& t): fn_(f), t_(t) {}

  R operator()(Arg& a)
  {
    return (t_.*fn_)(a);
  }
};

template <typename R, typename T, typename Arg>
simple_bind_t<R, T, Arg> simple_bind(
  R(T::*fn)(Arg), const T& t/*, const placeholder&*/)
{
  return simple_bind_t<R, T, Arg>(fn, t);
}
// 2 class ����ʹ�� ָ�뷽ʽ
template <typename R, typename T, typename Arg1, typename Arg2>
class simple_bind_t2
{
  typedef R(T::*fn)(Arg1, Arg2);
  fn fn_;
  T* t_;
public:
  simple_bind_t2(fn f, const T* t): fn_(f), t_(const_cast<T*>(t)) {
    int i = 0;
  }

  R operator()(Arg1& a, Arg2& b)
  {
    return (t_->*fn_)(a, b);
  }
};

template <typename R, typename T, typename Arg1, typename Arg2>
simple_bind_t2<R, T, Arg1, Arg2> simple_bind(
  R(T::*fn)(Arg1, Arg2), const T* t, const placeholder&, const placeholder&)
{
  return simple_bind_t2<R, T, Arg1, Arg2>(fn, t);
}

int main()
{
  Test t;
  Test* p_t = new Test();
  boost::shared_ptr<Test> ptr_test = boost::make_shared<Test>();
  std::vector<int> vec;
  vec.push_back(42);
  simple_bind(&Test::do_stuff, t/*, _1*/)(vec); //��ͬ������2�д����߼�, _1���Բ���Ҫ
  int x = 0, y = 0;
  //simple_bind(&Test::do_something, p_t, _1, _2)(x, y); //��ͬ������2�д����߼�
  boost::function<void(int&, int&)> f(simple_bind(&Test::do_something, &(*ptr_test), _1, _2));
  ptr_test.reset(); //����� ���������������f����Ҳû���⡣class ָ����ͬ
  f(x, y);

  std::string s = typeid(p_t).name();
  return 0;
}