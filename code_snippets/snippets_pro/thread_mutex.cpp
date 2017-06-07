//boost thread��mutexʹ��
//������������������ں�����ʼ��������return ֮���ٽ�������return������ѹջ���������о�
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp> // lock_guard ͷ�ļ�
#include <boost/thread/lock_types.hpp> // unique_lock ͷ�ļ�
#include <boost/thread/shared_mutex.hpp> // shared_lock ��Ҫ
#include <boost/thread/thread.hpp>

boost::mutex mutex_;
boost::shared_mutex shared_mutex_;
int temp = 0;
#define FOR_LOOP_COUNT (10000)

void fun1()
{
  for (int i = 0; i < FOR_LOOP_COUNT; ++i) {
    mutex_.lock();
    temp++;
    mutex_.unlock();
  }
}

void fun2()
{
  //lock_guard ��fun1���ƣ�ֻ������RAII��񣬹���ʱlock������ʱ����unlock
  boost::lock_guard<boost::mutex> l(mutex_);
  for (int i = 0; i < FOR_LOOP_COUNT; ++i) {
    temp++;
  }
}

void fun3()
{
  //unique_lock �ڲ�����is_locked�ж��Ƿ����,��try_lock timed_lock
  boost::unique_lock<boost::mutex> l(mutex_);
  for (int i = 0; i < FOR_LOOP_COUNT; ++i) {
    temp++;
  }
}

void fun4()
{
  //shared_lock
  boost::shared_lock<boost::shared_mutex> l(shared_mutex_);
  for (int i = 0; i < FOR_LOOP_COUNT; ++i) {
    temp++;
  }
}

void fun5()
{
  //�� mutex �� unique_lock<mutex>
  boost::mutex::scoped_lock l(mutex_);
  for (int i = 0; i < FOR_LOOP_COUNT; ++i) {
    temp++;
  }
}

int main()
{
  boost::function<void()> ff = boost::bind(&fun5);
  boost::thread th1(ff);
  boost::thread th2(ff);
  th1.join();
  th2.join();

  std::cout << "temp :" << temp << std::endl;
  return 0;
}