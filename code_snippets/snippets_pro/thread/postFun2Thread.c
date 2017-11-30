/*
  ���ԣ��߳��������ж��У���������Ͷ�ݸ����̵߳���������
*/
#include <stdio.h>
#include <pthread.h>
#include <deque>
#include <unistd.h>
typedef void (*FUN)(void);
static std::deque<FUN> MsgDeq;
static FUN p = NULL;

// loop�߳�
void* fun1(void* arg)
{
  std::deque<FUN>::iterator it; 
  while(true)
  {   
    if(false == MsgDeq.empty()) {
      it = MsgDeq.begin();
      (*(*it))();
      MsgDeq.pop_front();
    } else {
      printf("thread empty loop\n");
    }   
    sleep(2);
  }   
  return (void*)0;
}

void show_callback(){ printf("call show_callback\n"); }
void post(){ MsgDeq.push_back(&show_callback); }

int main()
{
  pthread_t t1; 
  void* res;
  int s;

  s = pthread_create(&t1, NULL, fun1, NULL);
  if(s != 0) {
    printf("pthrad_crate err\n");
  }   

  // �����߳�Ͷ�ݺ���
  for(int i=0;i<4;++i)
  {   
    post();
  }   
  s = pthread_join(t1, &res);
  if(s != 0) {
    printf("pthread_join err\n");
  }   

  return 0;
}
