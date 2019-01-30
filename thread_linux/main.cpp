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

// ���еĶ��߳�ʾ��
#include "thread_call_classFun.h"
#include "postFun2Thread.h"
#include "inputdata_and_localdata_threasafe.h"

void test_thread() {
  // ��ʵ��Linux �߳�
  //test_simple_thread();

  // �̼߳���Դ����
  //test_thread_increase();

  // ʵ����������̼߳���Դ��������
  //test_thread_increase_with_lock();

  // ���߳�����ε��� class�ĳ�Ա����
  //test_call_classFun();

  // ��������� + һ��������
  //test_prod_no_condvar();

  // ʹ���������� ��Э�������ߺ��������߳�
  //test_prod_condvar();

  // ������������
  //test_post_fun2thread();

  // 
  test_inputdata_and_localdata_thread_safe();
}

int main() {
  test_thread();

  return 0;
}