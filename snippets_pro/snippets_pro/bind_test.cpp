//bind ����
/*
bind�еڶ������� ����ָ�룬�����ڲ�������ö�Ӧ�Ŀ������캯��������Ҫ���ö�ο������캯��.
boost::lambda ����ֻ��3���������ƣ�ʹ�� _1 _2���ַ�ʽ���Է�ֹ8��������bind��
*/
#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

class test1
{
public:
  test1() {}
  test1(const test1& p) {}
  ~test1() {}
  void do_something1(int& i, int& j)
  {
    i = 9;
    j = 11;
  }
  void do_something2(int& x_ , int& y_ , int& z_ , int& f_ , int& g_ , int& h_ ,
    int& i_ , int& j_)
  {
    x_ = 7;
    y_ = 7;
    z_ = 7;
    f_ = 7;
    g_ = 7;
    h_ = 7;
    i_ = 7;
    j_ = 7;
  }
  // �����ַ�ʽ
  void bind()
  {
    int x = 0, y = 0;
    test1* p = this;
    boost::bind(&test1::do_something1, p, boost::lambda::_1, boost::lambda::_2)(x, y);
  }
};
int main()
{
  test1 t1;
  //t1.bind();
  //   boost::function<void(int&)> f(boost::bind(&test1::do_something, t1, boost::lambda::_1));
  //   int x = 0;
  //   f(x);
  // �ڶ���ʹ��bind��ʽ
  int x = 0, y = 0, z = 0, f = 0, g = 0, h = 0, i = 0,j = 0;
  // bind�еڶ������� ����ָ�룬�����ڲ�������ö�Ӧ�Ŀ������캯��������Ҫ���ö�ο������캯��
  //boost::bind(&test1::do_something, /*t1*/&t1, boost::lambda::_1, boost::lambda::_2)(x, y);
  // ���ַ�ʽ ���ù˼� boost::lambda ֻ��_1 _2 _3��������������
  boost::bind(&test1::do_something2, &t1,
    _1, _2, _3, _4, _5, _6, _7, _8)(x , y , z , f , g , h , i , j);
  return 0;
}