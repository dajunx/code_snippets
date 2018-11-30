//程序计算 时间差
//转换ptime 为string类型：boost::posix_time::to_simple_string
#include "boost_common.h"

void cost_time_fun() {
  std::map<std::string, int> mm;
  std::stringstream map_key;
  for (int i = 1000; i < 100000; ++i) {
    map_key.str("");
    map_key << i;
    mm.insert(std::pair<std::string, int>(map_key.str(), i));
  }
}

bool test_calculate_fun_duration_time() {
  boost::posix_time::ptime start_time, end_time;
  boost::posix_time::time_duration time_costs;
  
  start_time = boost::posix_time::microsec_clock::local_time();
  cost_time_fun();
  end_time = boost::posix_time::microsec_clock::local_time();

  time_costs = end_time - start_time;

  std::cout<<"start time:"　<< boost::posix_time::to_simple_string(start_time) << std::endl;
    //output: start time:2018-Jun-11 17:01:09.910169
  std::cout<<"end time:"　<< boost::posix_time::to_simple_string(end_time) << std::endl;
    //output: end time:  2018-Jun-11 17:01:25.580065
  std::cout << "cost_time_fun 运算耗时:" << time_costs.total_milliseconds() << "ms" << std::endl;
  
  return true;
}