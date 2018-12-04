/*
  boost::chrono 时间测试
*/
#include "boost_common.h"

// clock
void test_chrono_clock_time() {
  using namespace boost::chrono;
  /* 
    1.system_clock.
    This is the time usually displayed on the desktop of your computer. 
    If you change the time on your computer, boost::chrono::system_clock returns the new time.
    这个时钟是可以和外部时钟源同步的
  */
  std::cout << "system_clock::now(): " << system_clock::now()
            << "system_clock::now(), seconds: "
            << boost::chrono::system_clock::to_time_t(system_clock::now()) << std::endl;
  /*
    2.steady_clock.
    时间是单调增长的，其特性对于很多不允许时间错乱的系统是十分重要
    通常是基于系统启动时间来计时的，而且常常用来进行耗时、等待等工作使用
  */
  std::cout << "steady_clock::now(): " << steady_clock::now() 
            << "steady_clock::now(), since computer system boot seconds: " 
            << duration_cast<seconds>(steady_clock::now().time_since_epoch())
            << std::endl;
  std::cout<<__FUNCTION__ << ", end."<<std::endl;
}

// time_point, time_point = clock + duration.
void test_chrono_time_point_test() {
  using namespace boost::chrono;

  system_clock::time_point system_tp = system_clock::now();
  steady_clock::time_point steady_tp = steady_clock::now();
  std::cout << "system's seconds: " 
            << system_tp.time_since_epoch().count() * system_clock::period::num / 
               system_clock::period::den
            << std::endl;

  std::cout << "steady's seconds: " 
            << steady_tp.time_since_epoch().count() * steady_clock::period::num / 
            steady_clock::period::den
            << std::endl;
}

// duration
void test_chrono_duration_test() {
  using namespace boost::chrono;

  steady_clock::time_point steady_tp1 = steady_clock::now();
  boost::this_thread::sleep(boost::posix_time::seconds(10));
  steady_clock::time_point steady_tp2 = steady_clock::now();
  steady_clock::duration steady_duration = steady_tp2 - steady_tp1;
  seconds sec = duration_cast<seconds>(steady_duration);
  std::cout<< "duration: " << sec << std::endl;

  std::cout << "steady1's seconds: " 
    << steady_tp1.time_since_epoch().count() * steady_clock::period::num / 
    steady_clock::period::den
    << std::endl;
  std::cout << "steady2's seconds: " 
    << steady_tp2.time_since_epoch().count() * steady_clock::period::num / 
    steady_clock::period::den
    << std::endl;
}

bool chrono_time_test() {
  test_chrono_clock_time();
  test_chrono_time_point_test();
  test_chrono_duration_test();

  return true;
}