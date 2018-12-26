//简单委托

#include "cplusplus_common_def.hpp"

void englishgreeting(std::string name) {
  std::cout << "Morning, " << name << std::endl;
}

void chinesegreeting(std::string name) {
  std::cout << "早上好, " << name << std::endl;
}

void GreetPople(std::string name, boost::function<void(std::string)> fun) {
  fun(name);
}

bool test_delegate() {
  GreetPople("lin", boost::bind(chinesegreeting, _1));
  GreetPople("xxx", boost::bind(chinesegreeting, _1));

  return true;
}