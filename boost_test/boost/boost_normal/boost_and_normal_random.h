
#include "boost_common.h"
using namespace std;

// 分析统计set中随机数分布情况
void analys_random_data(std::multiset<int>& set_temp) {
  std::map<int, int> map_total_data;
  std::map<int, int>::iterator it_map;
  std::multiset<int>::iterator it = set_temp.begin();
  for (; it!=set_temp.end();++it)
  {
    map_total_data[*it]++;
  }

  for(it_map = map_total_data.begin(); it_map != map_total_data.end(); ++it_map) {
    std::cout<<"key: "<<it_map->first<<", value: "<<it_map->second<<std::endl;
  }
}

//---------------------- boost 产生随机数方式:----------------------------------
void product_random_num_fun1() {
  std::multiset<int> set_temp;

  int num = 0;
  typedef boost::mt19937 RNGType;
  RNGType rng;
  boost::uniform_int<> one_to_five(1, 5);
  boost::variate_generator<RNGType, boost::uniform_int<>> dice(rng, one_to_five);
  for (int i = 0; i < 10000; ++i) {
    num = dice();
    set_temp.insert(num);
  }

  analys_random_data(set_temp);
}

int product_random_num_fun2() {
  typedef boost::mt19937 RNGType;
  RNGType rng(time(0));
  boost::uniform_int<> one_to_five(1, 5);
  boost::variate_generator<RNGType, boost::uniform_int<>> dice(rng, one_to_five);
  return dice();
}

//---------------------- c++ 产生随机数方式:----------------------------------
class product_random_num_class {
public:
  product_random_num_class() { srand(static_cast<unsigned int>(time(NULL))); }
  static int test_fun3() {
    int iSecret = rand() % 5 + 1;
    return iSecret;
  }
};

void product_random_num_fun3() {
  std::multiset<int> set_temp;

  int num = 0;
  for (int i = 0; i < 10000; ++i) {
    num = product_random_num_class::test_fun3();
    set_temp.insert(num);
  }

  analys_random_data(set_temp);
}

bool test_boost_random() {
  product_random_num_fun3();
  product_random_num_fun1();
  return true;
}