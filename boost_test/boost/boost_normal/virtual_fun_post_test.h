// 测试c++中 virtual function 功能，使用boost投递
#include "boost_common.h"

using namespace boost;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
typedef boost::shared_ptr<boost::asio::io_service::work> io_work_ptr;

void fun1() { int i = 0; }

class test_virtual_fun_class1 {
public:
  test_virtual_fun_class1() {}
  ~test_virtual_fun_class1() {}
  virtual void show() { std::cout<<"test_virtual_fun_class1"<<std::endl; }
};

class test_virtual_fun_class3 : public test_virtual_fun_class1 {
public:
  test_virtual_fun_class3() {}
  ~test_virtual_fun_class3() {}
  void show() { std::cout<<"test_virtual_fun_class3"<<std::endl; }
};

bool test_cpp_virtual_fun_post_test() {
  io_service_ptr ptr_io_service = boost::make_shared<boost::asio::io_service>();
  io_work_ptr ptr_io_work = boost::make_shared<boost::asio::io_service::work>(
      boost::ref(*ptr_io_service));

  // boost::thread th(work_fun, ptr_io_service);
  boost::thread th(boost::bind(&boost::asio::io_service::run, ptr_io_service));
  th.detach();

  boost::shared_ptr<test_virtual_fun_class1> ptr_t1 = boost::make_shared<test_virtual_fun_class1>();
  boost::shared_ptr<test_virtual_fun_class3> ptr_t3 = boost::make_shared<test_virtual_fun_class3>();

  /* 如下调用，输出:
     test_virtual_fun_class3
     test_virtual_fun_class1
  */
  ptr_io_service->post(boost::bind(&test_virtual_fun_class1::show, ptr_t3));
  ptr_io_service->post(boost::bind(&test_virtual_fun_class1::show, ptr_t1));

  boost::this_thread::sleep(boost::posix_time::milliseconds(100));
  return true;
}