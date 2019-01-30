#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "simple_thread.h"
#include "thread_incr.h"
#include "thread_incr_mutex.h"
#include "prod_no_condvar.h"
#include "prod_condvar.h"

// 自有的多线程示例
#include "thread_call_classFun.h"
#include "postFun2Thread.h"
#include "inputdata_and_localdata_threasafe.h"

void test_thread() {
  // 简单实用Linux 线程
  //test_simple_thread();

  // 线程间资源竞争
  //test_thread_increase();

  // 实用锁来解决线程间资源竞争问题
  //test_thread_increase_with_lock();

  // 在线程中如何调用 class的成员函数
  //test_call_classFun();

  // 多个生产者 + 一个消费者
  //test_prod_no_condvar();

  // 使用条件变量 来协调生产者和消费者线程
  //test_prod_condvar();

  // 条件变量运用
  //test_post_fun2thread();

  // 
  test_inputdata_and_localdata_thread_safe();
}

int main() {
  test_thread();

  return 0;
}