/*
  ���ԣ��߳��������ж��У���������Ͷ�ݸ����̵߳���������
*/
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <deque>
#include <vector>
#include <unistd.h>
typedef void (*FUN)(int);
static std::deque<FUN> MsgDeq; //������Ϣ����
std::vector<int> vec_thread_datas;
static bool post_event_finished = false;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

class c_mutex{
public:
  c_mutex(){pthread_mutex_lock(&mutex);}
  ~c_mutex(){pthread_mutex_unlock(&mutex);}
};
// loop�߳�
void* fun2(void* arg)
{
  std::deque<FUN>::iterator it;
  int input_cb_data = 0;
  while(true)
  {
    pthread_mutex_lock(&mutex);
    // ��������ʹ�����ӣ�
    // ����������ʹ��Ŀ��Ҳ�Ǳ���������ƽ��ȥ���Լ����鿴�Ƿ��������ݵ���
    while(MsgDeq.empty()) {
      pthread_cond_wait(&cond, &mutex);
    }

    it = MsgDeq.begin();
    (*(*it))(input_cb_data++);
    MsgDeq.pop_front();
    pthread_mutex_unlock(&mutex);

    if (post_event_finished == true && true == MsgDeq.empty()) {
      break;
    }
  }
  return (void*)0;
}

void* fun1(void* arg)
{
  std::deque<FUN>::iterator it;
  int input_cb_data = 0;
  while(true)
  {
    if(false == MsgDeq.empty()) {
      c_mutex t;
      it = MsgDeq.begin();
      (*(*it))(input_cb_data++);
      MsgDeq.pop_front();
    } else {
      //printf("thread empty loop\n");
    }
    if (post_event_finished == true && true == MsgDeq.empty()) {
      break;
    }
  }
  return (void*)0;
}

void show_callback(int i){
  vec_thread_datas.push_back(i);
}
void post(){ MsgDeq.push_back(&show_callback); }

int main()
{
  pthread_t t1, t2;
  void* res;
  int s;

  s = pthread_create(&t1, NULL, fun2, NULL);
  //s = pthread_create(&t2, NULL, fun2, NULL);

  // �����߳�Ͷ������
  for(int i=0;i<1000000;i++)
  {
    c_mutex t;
    pthread_cond_signal(&cond);
    post();
  }
  post_event_finished = true;

  s = pthread_join(t1, &res);
  //s = pthread_join(t2, &res);

  // ��ӡ�̴߳�����Ĺ�������
  std::vector<int>::iterator it = vec_thread_datas.begin();
  printf("vector size:%d\n", vec_thread_datas.size());
  for(int i = 0;it != vec_thread_datas.end();it++, i++) {
    if (i != *it) {
      std::cout<<"pos:"<<i<<" data"<<*it<<std::endl;
    }
  }

  return 0;
}