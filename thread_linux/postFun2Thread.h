/*
  测试，线程用作串行队列，用来处理投递给子线程的任务请求
*/
#include <deque>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>

typedef void (*FUN)(int);
static std::deque<FUN> MsgDeq; //共享消息队列
std::vector<int> vec_thread_datas;
static bool post_event_finished = false;
static pthread_mutex_t mutex_postFun2Thread = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_postFun2Thread = PTHREAD_COND_INITIALIZER;

// loop线程
void *test_postFun2Thread_fun(void *arg) {
  std::deque<FUN>::iterator it;
  int input_cb_data = 0;
  while (true) {
    pthread_mutex_lock(&mutex_postFun2Thread);
    // 条件变量使用例子，
    // 条件变量的使用目的也是避免消费者平凡去尝试加锁查看是否又新数据到来
    while (MsgDeq.empty()) {
      pthread_cond_wait(&cond_postFun2Thread, &mutex_postFun2Thread);
    }

    it = MsgDeq.begin();
    (*(*it))(input_cb_data++);
    MsgDeq.pop_front();
    pthread_mutex_unlock(&mutex_postFun2Thread);

    if (post_event_finished == true && true == MsgDeq.empty()) {
      break;
    }
  }
  return (void *)0;
}

void show_callback(int i) { vec_thread_datas.push_back(i); }
void post() { MsgDeq.push_back(&show_callback); }

int test_post_fun2thread() {
  pthread_t t1;
  void *res;
  int s;

  s = pthread_create(&t1, NULL, test_postFun2Thread_fun, NULL);

  // 在主线程投递请求
  for (int i = 0; i < 1000000; i++) {
    pthread_mutex_lock(&mutex_postFun2Thread);
    pthread_cond_signal(&cond_postFun2Thread);
    post();
    pthread_mutex_unlock(&mutex_postFun2Thread);
  }
  post_event_finished = true;

  s = pthread_join(t1, &res);

  // 打印线程处理完的归总数据
  std::vector<int>::iterator it = vec_thread_datas.begin();
  printf("vector size:%d\n", vec_thread_datas.size());
  for (int i = 0; it != vec_thread_datas.end(); it++, i++) {
    if (i != *it) {
      std::cout << "pos:" << i << " data" << *it << std::endl;
    }
  }

  return 0;
}