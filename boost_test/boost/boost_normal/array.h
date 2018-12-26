/*
  兼容STL的容器，是固定大小的数组的包装
*/
#include "boost_common.h"

bool test_boost_array() {
  typedef boost::array<std::string, 4> boost_array;
  boost_array a;
  a[0] = "lin";
  a.at(1) = "jian";
  *a.rbegin() = "jun";
  boost_array b = {"lin", "jian", "jun"};
  std::sort(a.begin(), a.end());
  for (boost_array::const_iterator it = a.begin(); it != a.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << a.size() << std::endl;
  std::cout << a.max_size() << std::endl;

  return true;
}