// io_service wrap 使用
#include "boost_common.h"

using namespace boost::asio;
io_service service;
#define SHOW_FUN_POSION_AND_THRAD_ID \
std::cout <<"fun: " <<__FUNCTION__ \
          <<", line: "<<__LINE__ \
          <<", thread id: " << boost::this_thread::get_id() \
          <<std::endl;
/*
  dispatched_func_1、dispatched_func_2、service_run 都在 th线程中执行
*/

void dispatched_func_1() { 
  SHOW_FUN_POSION_AND_THRAD_ID;
}

void dispatched_func_2() { 
  SHOW_FUN_POSION_AND_THRAD_ID;
}

void test(boost::function<void()> func) {
  SHOW_FUN_POSION_AND_THRAD_ID;
  service.dispatch(dispatched_func_1);
  func();
}
void service_run() {
  SHOW_FUN_POSION_AND_THRAD_ID;
  service.run();
}

bool use_io_service_wrap() {
  SHOW_FUN_POSION_AND_THRAD_ID;

  test(service.wrap(dispatched_func_2));
  boost::thread th(service_run);
  boost::this_thread::sleep(boost::posix_time::millisec(500));
  th.join();

  return true;
}