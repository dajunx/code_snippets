//typedef �� ģ�庯�� ��ϲ����Ŀӣ�ԭ�������
/*
typedef �� ģ�庯�����ʹ�õ�ʱ��typedef ������ģ���������ͬ����
  ��2�����嶼����ͷ�ļ��У���ʹ�õ�ʱ�� �����ʹ�ôﲻ��Ԥ���Ч����
*/
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "common.h"

template <typename des>
void test1::fun1(boost::shared_ptr<base>const& ptr_base)
{
  boost::shared_ptr<des> ptr_ch
    = boost::dynamic_pointer_cast<des>(ptr_base);
  if (ptr_ch) {
    ptr_ch->show();
  } else {
    int i = 0;
  }
}

int main()
{
  boost::shared_ptr<child1> ptr_ch1 = boost::make_shared<child1>();
  boost::shared_ptr<child2> ptr_ch2 = boost::make_shared<child2>();

  test1 tt;
  tt.fun1<child1>(boost::dynamic_pointer_cast<base>(ptr_ch1));
  tt.fun1<child2>(boost::dynamic_pointer_cast<base>(ptr_ch2));

  return 0;
}


//---------------------------------------------------------------------------
  //common.h file:

class base{
public:
  base() {}
  virtual ~base() {}
};

class child1 : public base{
public:
  child1() {}
  ~child1() {}
  void show(){
    std::cout<<"child1"<<std::endl;
  }
};

class child2 : public base{
public:
  child2() {}
  ~child2() {}
  void show(){
    std::cout<<"child2"<<std::endl;
  }
};

class test1{
public:
  test1() {}
  ~test1() {}

  // �������棬��� typedef �����fun1��������������ĵڶ��ε���<child2> �������⣡
  // ����취��typedef child1 des; ����cpp�м���
  typedef child1 des;

  template <typename des>
  void fun1(boost::shared_ptr<base>const& ptr_base);
};

