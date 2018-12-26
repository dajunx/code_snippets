/*
** 随机化 vector容器中一串数据;
*/
#include "cplusplus_common_def.hpp"

// header file.
//#include <algorithm> // std::random_shuffle
//#include <ctime> //time
//#include <iostream>
//#include <unordered_map>
//#include <vector>

// map_collect_random 中数据是随机的;
td::unordered_map<long long, long long> map_collect_random;

int myrandom(int i) { return std::rand() % i; }

void print_randomed_map() {
  std::unordered_map<long long, long long>::iterator it = map_collect_random.begin();
  for (; it != map_collect_random.end(); ++it)
  {
    std::cout<<"key: "<<it->first<<", value: "<<it->second<<std::endl;
  }
  std::cout<<std::endl;
  map_collect_random.clear();
}

void analys_randomed_vec(std::vector<int> &vec_tmp) {
  long long num = 0;
  std::vector<int>::reverse_iterator it = vec_tmp.rbegin();
  for (long long i = 1; it != vec_tmp.rend(); ++it) {
    num += (*it) * i;
    i *= 10;
  }

  if (map_collect_random.find(num) == map_collect_random.end()) {
    map_collect_random[num] = 1;
  } else {
    map_collect_random[num]++;
  }
}

bool test_random_some_numbers() {
  std::vector<int> vec_int;
  std::vector<int> vec_int_tmp;
  for (int i = 0; i < 10; ++i)
    vec_int.push_back(i);

  // 种子
  std::srand(unsigned(std::time(0)));

  // 第一种随机容器一串数据算法：
  for (int i = 0; i < 10; ++i) {
    vec_int_tmp = vec_int;
    std::random_shuffle(vec_int_tmp.begin(), vec_int_tmp.end());
    analys_randomed_vec(vec_int_tmp);
  }
  print_randomed_map();

  // 第二种随机容器一串数据算法：
  for (int i = 0; i < 10; ++i) {
    vec_int_tmp = vec_int;
    std::random_shuffle(vec_int_tmp.begin(), vec_int_tmp.end(), myrandom);
    analys_randomed_vec(vec_int_tmp);
  }
  print_randomed_map();

  return true;
}