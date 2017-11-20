//vector ����capacity�Ͳ�capacity�ٶȲ���
/*
��release�汾���ֱ���2���߳����У�ÿ������10000000�Σ�ȡ100��ƽ��ֵ��reserve�汾�ڷ�reserve�汾һ��ʱ�䣬40����롣
��debug�汾�����ûɶ���죬���⡣ÿ������10000000�Σ�ȡ10��ƽ��ֵ��ʱ����3300�����㡣
*/

#include <iostream>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#define loop_num (100)

void fun2()
{
  long total_costtime = 0;
  for (int j=0;j<loop_num;++j)
  {
    boost::posix_time::ptime start_time = boost::posix_time::microsec_clock::local_time();
    std::vector<int> vec_int;
    vec_int.reserve(10000000);
    for (int i=0;i<10000000;++i)
    {
      vec_int.push_back(i);
    }
    boost::posix_time::ptime end_time = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration cost = end_time - start_time;
    total_costtime += cost.total_milliseconds();
  }  
  std::cout<<"cost time2:"<<total_costtime/loop_num<<" ms."<<std::endl;
}

void fun1()
{
  long total_costtime = 0;
  for (int j=0;j<loop_num;++j)
  {
    boost::posix_time::ptime start_time = boost::posix_time::microsec_clock::local_time();
    std::vector<int> vec_int;
    for (int i=0;i<10000000;++i)
    {
      vec_int.push_back(i);
    }
    boost::posix_time::ptime end_time = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration cost = end_time - start_time;
    total_costtime += cost.total_milliseconds();
  }  
  std::cout<<"cost time1:"<<total_costtime/loop_num<<" ms."<<std::endl;
}

int main()
{
  boost::thread th1(fun1);
  boost::thread th2(fun2);
  th1.join();
  th2.join();
  return 0;
}