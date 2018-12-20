// new 的另一种形式
/*
new 的时候，用已经分配内存的地址返回给待分配内存指针。比较特殊
*/

#include "cplusplus_common_def.hpp"

bool test_another_new() {
  void *pp = new int(5);
  // int* pp = new int(5); // this way has the same result

  // 获取到的内存地址会被初始化成1，即 pp 和 p 都指向相同地址且 值为1
  int *p = new (pp) int(1);
  
  return true;
}