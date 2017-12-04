/*
  linux���̲߳��Ե��� class�ĳ�Ա������
    ���ƣ��߳�ֻ�ܰ� static���͵ĳ�Ա�����������������̺߳����з������ ��static��Ա�����봫����������
  �ο����ӣ�https://stackoverflow.com/questions/1151582/pthread-function-from-a-class
*/
#include <iostream>
#include <pthread.h>
#include <unistd.h>

class test1{
public:
  static void* fun1(void* arg)
  {   
    test1* p1 = (test1*)arg;
    std::cout<<"fun1 called."<<std::endl;
    p1->show();
    return (void*)0;
  }   
  void show()
  {   
    std::cout<<"show call"<<std::endl;
  }   

};

int main()
{
  pthread_t t1; 
  void* res;
  int s;

  test1 tt1;
  s = pthread_create(&t1, NULL, &test1::fun1, &tt1);
  s = pthread_join(t1, &res);

  return 0;
}