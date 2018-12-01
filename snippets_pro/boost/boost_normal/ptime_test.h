//获取 ptime 时间细分粒度，年月日时分秒
#include "boost_common.h"

bool boost_ptime_usage_test() {
  // 1.由 ptime转换成 tm结构:
  using namespace boost::posix_time;
  ptime now_time1 = microsec_clock::local_time();
  struct tm t = to_tm(now_time1);
  std::cout << "year:" << t.tm_year + 1900
    << ", month:" << t.tm_mon
    << ", day:" << t.tm_mday
    << ", hour:" << t.tm_hour
    << ", min:" << t.tm_min
    << ", sec:" << t.tm_sec << std::endl;

  // 2.月份函数、类型
  std::cout << "type:" << typeid(now_time1.date().month()).name()
    << std::endl;
  std::cout << "time:" << now_time1.date().month() << std::endl;

  ptime now_time2 = microsec_clock::local_time();
  if (now_time1.date().month() == now_time2.date().month()) {
    std::cout<<"mounth is equal."<<std::endl;
  }

  ///TODO 更多... to be continued

  return true;
}