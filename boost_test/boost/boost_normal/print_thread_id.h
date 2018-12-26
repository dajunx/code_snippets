#include "boost_common.h"

bool print_thread_id() {
  int write_max = 10;
  while (--write_max > 0) {
    using namespace boost::posix_time;
    // 打印线程id + 当前时间
    std::cout<<__FUNCTION__
      <<", now_time: " << to_simple_string(microsec_clock::local_time())
      << ", this_thread id: " << boost::this_thread::get_id()
      << std::endl;

    boost::this_thread::sleep(boost::posix_time::seconds(1));
  }

  return true;
}

void test_print_thread_id() {
  boost::thread th(boost::bind(&print_thread_id));
  th.detach();

  boost::this_thread::sleep(boost::posix_time::seconds(100));
}