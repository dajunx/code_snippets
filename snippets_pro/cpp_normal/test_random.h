// c++ random 列子
#include "cplusplus_common_def.hpp"

// header file define
/* rand example: guess the number */
//#include <stdio.h>  /* printf, scanf, puts, NULL */
//#include <stdlib.h> /* srand, rand */
//#include <time.h>   /* time */

void test_random() {
  int iSecret;

  /* initialize random seed: */
  srand(time(NULL));

  // 产生1~10随机数
  iSecret = rand() % 10 + 1;

  return true;
}