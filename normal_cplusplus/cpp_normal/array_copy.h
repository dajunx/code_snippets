#include "cplusplus_common_def.hpp"
//数组拷贝

bool test_copy_array_data() {
  // 拷贝数组
  int random_numb[10];
  int random_numb_tmp[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  
  int array_size = 10 * sizeof(int); //拷贝的size，注意size得和每个元素大小相乘;
  memcpy(reinterpret_cast<char*>(random_numb),
    reinterpret_cast<char*>(random_numb_tmp), array_size);
  return true;
}