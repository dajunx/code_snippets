//bind �������ڵ����ӣ�
/*
bind �󶨣�д�ں�������λ�ã��������ھͻ����ź������Ƚ����������������ط�Ҫʹ�ø� bind�󶨵Ĵ���ε�ֵ������������ʹ�� const& �洢ֵ��
*/

//����汾:
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/ref.hpp>

typedef boost::function<void()> test2_callback;


class test1
{
public:
  void registe_callback()
  {
    test2_callback const& ff = fun2(boost::bind(&test1::call_back));
    ff();
  }
  test2_callback const& fun2(test2_callback const& f)
  {
    return f;
  }
  static void call_back()
  {
    int i = 0;
  }
};

int main()
{
  test1 t1;
  t1.registe_callback();

  return 0;
}

//---------------------------------------------------------------------

#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/ref.hpp>

  typedef boost::function<void()> test2_callback;

class test2
{
public:
  test2(test2_callback const& f) : f_(f) {}
  static void call_back()
  {
    int i = 0;
  }

  void call_binded_function()
  {
    f_();
  }

  test2_callback /*const&*/ f_;
};

class test1 : boost::enable_shared_from_this<test1>
{
public:
  void registe_callback()
  {
    /*test2_callback ff = */fun2(boost::bind(&test2::call_back));
    /*ff()*/
  }
  void /*test2_callback*/ fun2(test2_callback const& f)
  {
    p_t2 = new test2(f);
    /*return f*/
  }
  void call_binded_function()
  {
    p_t2->call_binded_function();
  }

  test2* p_t2;
};

int main()
{
  test1 t1;
  t1.registe_callback();
  t1.call_binded_function();

  return 0;
}
