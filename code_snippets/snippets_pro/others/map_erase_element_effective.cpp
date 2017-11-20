#include <iostream>
#include <vector>
#include <map>
#include <boost/date_time/posix_time/posix_time.hpp>

//���� map�������ݺ�ɾ�����ݵ�Ч�ʣ����������Ϊ 1~1000000��
//�� gcc�еĽ��Ϊ time1:430ms time2:78ms

void cost_time(std::map<int, int>& map_data)
{
  std::map<int, int>::iterator it = map_data.begin();
  while(it != map_data.end())
  {
    map_data.erase(it);
    it = map_data.begin();
  }
}

int main(int argc, char *argv[])
{
  boost::posix_time::ptime start, end;
  std::map<int, int> map_large_data;
  start = boost::posix_time::microsec_clock::local_time();
  for (int i=0; i < 1000000; ++i)
  {
    map_large_data.insert(std::pair<int, int>(i, i));
  }
  end = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration cost = end - start;
  std::cout<<"time1:"<<cost.total_milliseconds()<<"ms"<<std::endl;

  start = boost::posix_time::microsec_clock::local_time();
  cost_time(map_large_data);
  end = boost::posix_time::microsec_clock::local_time();

  cost = end - start;
  std::cout<<"time2:"<<cost.total_milliseconds()<<"ms"<<std::endl;

  int i = 0;
  return 0;
}
