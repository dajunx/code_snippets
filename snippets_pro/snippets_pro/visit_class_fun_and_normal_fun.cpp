//�������Ա��������ͨ����
//link:http://stackoverflow.com/questions/10231330/how-to-get-a-methods-address-in-a-class

#include <iostream>
#include <boost/function.hpp>

class test1
{
public:
  test1() {}
  ~test1() {}
  void fun() {}
};

void fun1()
{
  int i = 0;
}

int main()
{
  // �������Ա���� ԭʼ��ʽ
  void (test1::*ff)(void);
  ff = &test1::fun;

  test1 t1;
  (t1.*ff)();

  // ������ͨ����ָ�뷽ʽ
  void (*pfun)();
  pfun = &fun1;
  pfun();

  // boost function ��ʽ
  boost::function<void(test1*)> ff1(&test1::fun);
  ff1(&t1);
  return 0;
}