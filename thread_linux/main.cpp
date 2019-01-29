#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "simple_thread.h"
#include "thread_incr.h"
#include "thread_incr_mutex.h"

void test_thread() {
  // 简单实用Linux 线程
  //test_simple_thread();

  // 线程间资源竞争
  //test_thread_increase();

  // 实用锁来解决线程间资源竞争问题
  test_thread_increase_with_lock();

}

int main() {
  test_thread();

  return 0;
}