#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "simple_thread.h"
#include "thread_incr.h"
#include "thread_incr_mutex.h"

void test_thread() {
  // ��ʵ��Linux �߳�
  //test_simple_thread();

  // �̼߳���Դ����
  //test_thread_increase();

  // ʵ����������̼߳���Դ��������
  test_thread_increase_with_lock();

}

int main() {
  test_thread();

  return 0;
}