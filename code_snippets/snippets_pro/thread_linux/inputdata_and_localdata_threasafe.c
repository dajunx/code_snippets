/*
  ��֤�̺߳�������� �������̺߳����ľֲ������Ƿ��� �̰߳�ȫ���ǹ��������
  TODO �ٶ�˼������������
*/
#include <pthread.h>
#include <time.h>
#include <stdio.h>

  void* fun1(void* arg)
{
  int* tmp = (int*)arg;
  int step = 0;
  printf("input data address:%ld\n", *tmp);
  for(int i=0;i<100000000;++i) {
    //(*tmp)++;
    step = *tmp;
    step++;
    *tmp = step;
  }   
  return 0;
}

int main()
{
  pthread_t t1, t2; 
  void* res;
  int s;

  int data1 = 1;
  s = pthread_create(&t1, NULL, fun1, &data1);
  printf("create thread1, result: %d\n", s); 

  int data2 = 2;
  s = pthread_create(&t2, NULL, fun1, &data2);
  printf("create thread2, result: %d\n", s); 

  s = pthread_join(t1, NULL);
  printf("join thread1, result: %d, data1:%d\n", s, data1);
  s = pthread_join(t2, NULL);
  printf("join thread2, result: %d, data2:%d\n", s, data2);

  return 0;
}
