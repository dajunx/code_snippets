//在windows端 精确计算 时间间隔
// 参考链接：http://blog.csdn.net/midle110/article/details/8068014

#include "cplusplus_common_def.hpp"
// header file.
//#include <iostream>
//#include <windows.h>
using namespace std;

bool calculate_costs_time() {
  LARGE_INTEGER Frequency;              //计数器频率
  LARGE_INTEGER start_PerformanceCount; //起始计数器
  LARGE_INTEGER end_PerformanceCount;   //结束计数器
  double run_time;                      //运行时间
  QueryPerformanceFrequency(&Frequency);

  for (int i = 0; i < 10; ++i) {

    QueryPerformanceCounter(&start_PerformanceCount);

    //耗时运算
    Sleep(1000);

    QueryPerformanceCounter(&end_PerformanceCount);
    run_time =
        (end_PerformanceCount.QuadPart - start_PerformanceCount.QuadPart) /
        (double)Frequency.QuadPart;
    cout << run_time << endl;
  }

  return true;
}