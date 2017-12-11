/*
  ����STL���������ǹ̶���С������İ�װ
*/
#include <iostream>
#include <boost/array.hpp>
#include <string>
#include <algorithm>
int main()
{
  typedef boost::array<std::string, 4> array;
  array a;
  a[0] = "lin";
  a.at(1) = "jian";
  *a.rbegin() = "jun";
  array b = {"lin", "jian", "jun" };
  std::sort(a.begin(), a.end());
  for (array::const_iterator it = a.begin(); it != a.end(); ++it) {
    std::cout<< *it <<std::endl;
  }
  std::cout<<a.size()<<std::endl;
  std::cout<<a.max_size()<<std::endl;
  return 0;
}