// shared_ptr 引用计数use_count_
/*
1、fun1 函数传递方式，在函数内部use_count_为2，传引用是1；
2、使用 io_service post 到函数内部是4，引用是3；
3、使用线程去执行，到函数内部是 3，引用是2。
4、传递函数 const& 不会增加use_count，而bind const&参数 会增加use_count
  (ps:若用boost::ref包裹这个const&参数 则不会增加use_count)
*/
#include "boost_common.h"

using namespace boost;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
typedef boost::shared_ptr<boost::asio::io_service::work> io_work_ptr;

struct shared_ptr_class {
  shared_ptr_class() {}
  ~shared_ptr_class() {}
  void show() {}
};

enum call_fun_type{
  FUNC = 0,
  ASIO,
  THREAD
};

void fun1(boost::shared_ptr<shared_ptr_class> const &ptr_test1,
  boost::shared_ptr<shared_ptr_class> ptr_test2,
  int type, bool do_loop = false) {
    while (do_loop) {
      boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}

bool shared_ptr_use_count_in_multiuse_method() {
  io_service_ptr ptr_io_service = boost::make_shared<boost::asio::io_service>();
  io_work_ptr ptr_io_work = boost::make_shared<boost::asio::io_service::work>(
    boost::ref(*ptr_io_service));

  boost::thread th(boost::bind(&boost::asio::io_service::run, ptr_io_service));
  th.detach();

  boost::shared_ptr<shared_ptr_class> ptr_fun_1 = boost::make_shared<shared_ptr_class>();
  boost::shared_ptr<shared_ptr_class> ptr_fun_2 = boost::make_shared<shared_ptr_class>();
  boost::shared_ptr<shared_ptr_class> ptr_asio_1 = boost::make_shared<shared_ptr_class>();
  boost::shared_ptr<shared_ptr_class> ptr_asio_2 = boost::make_shared<shared_ptr_class>();
  boost::shared_ptr<shared_ptr_class> ptr_thread_1 = boost::make_shared<shared_ptr_class>();
  boost::shared_ptr<shared_ptr_class> ptr_thread_2 = boost::make_shared<shared_ptr_class>();

  fun1(ptr_fun_1, ptr_fun_2, FUNC);

  ptr_io_service->post(boost::bind(&fun1, ptr_asio_1, ptr_asio_2, ASIO, true));
  boost::this_thread::sleep(boost::posix_time::seconds(20));

  boost::thread th1(boost::bind(&fun1, ptr_thread_1, ptr_thread_2, THREAD, true));
  boost::this_thread::sleep(boost::posix_time::seconds(20));

  return true;
}