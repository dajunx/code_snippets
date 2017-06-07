//shared_ptr ���ü���use_count_
/*
1��fun1 �������ݷ�ʽ���ں����ڲ�use_count_Ϊ2����������1��  
2��ʹ�� io_service post �������ڲ���4��������3��   
3��ʹ���߳�ȥִ�У��������ڲ��� 3��������2��
4�����ݺ��� const& ��������use_count����bind const&���� ������use_count 
  (ps:����boost::ref�������const&���� �򲻻�����use_count)
*/
#include <iostream>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/ref.hpp>

using namespace boost;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
typedef boost::shared_ptr<boost::asio::io_service::work> io_work_ptr;

struct test1
{
  test1() {}
  ~test1() {}
};

struct test2
{
  test2() {}
  ~test2() {}
};

boost::function<void(boost::shared_ptr<test1> const&)> f;
void fun2(boost::shared_ptr<test1> const& ptr_test1)
{
  int i = 0;
}

void fun1(boost::shared_ptr<test1> const& ptr_test1)
{
  // ��4�㣺��������Ϊ const& ��������use_count����bind const&���� ������use_count
  boost::shared_ptr<test2> ptr_temp = boost::make_shared<test2>();
  int i = 0;
  f = boost::bind(&fun2, ptr_test1);
  i = 1;
}

int main()
{
  io_service_ptr ptr_io_service = boost::make_shared<boost::asio::io_service>();
  io_work_ptr ptr_io_work = boost::make_shared<boost::asio::io_service::work>
    (boost::ref(*ptr_io_service));

  boost::thread th(boost::bind(&boost::asio::io_service::run, ptr_io_service));
  th.detach();

  boost::shared_ptr<test1> ptr_test1 = boost::make_shared<test1>();
  fun1(ptr_test1);
  //ptr_io_service->post(boost::bind(&fun1, ptr_test1));
  //boost::thread th1(boost::bind(&fun1, ptr_test1));

  boost::this_thread::sleep(boost::posix_time::milliseconds(100));

  return 0;
}