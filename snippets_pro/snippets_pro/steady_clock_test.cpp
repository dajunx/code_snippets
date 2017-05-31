/*
std::chrono::steady_clock Ϊ�˱�ʾ�ȶ���ʱ��������һ�ε���now()�õ���ʱ�����Ǳ�ǰһ�ε�ֵ����仰����˼��ʵ�ǣ������;�޸���ϵͳʱ�䣬Ҳ��Ӱ��now()�Ľ������ÿ��tick����֤�����ȶ���ʱ������
duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();  ����Ǽ�¼�Ŀ��������ڵ�ʱ����
*/

#include <iostream>
#include <string>
#include <boost/date_time.hpp>
#include <boost/chrono.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

boost::posix_time::ptime base_at;
void fun()
{
  //boost::posix_time::ptime base_at;
  using namespace boost::chrono;
  // tick_count_now ��¼���������ڵ�ʱ��
  boost::int64_t tick_count_now = duration_cast<microseconds>(
    steady_clock::now().time_since_epoch()).count();

  boost::int64_t tick_count_now_ = duration_cast<seconds>(
    steady_clock::now().time_since_epoch()).count();

  std::string base_str;
  base_at = boost::posix_time::microsec_clock::local_time();
  base_str = boost::posix_time::to_simple_string(base_at);

  base_at -= boost::posix_time::microsec(tick_count_now);
  base_str = boost::posix_time::to_simple_string(base_at);

  int i = 0;
}

void fun3()
{
  using namespace boost::chrono;
  boost::posix_time::ptime time = base_at + boost::posix_time::microsec
    (duration_cast<microseconds>
    (steady_clock::now().time_since_epoch()).count());

  std::cout<<"localtime :"<<boost::posix_time::to_simple_string(time)<<std::endl;
}

void fun1()
{
  using namespace boost::chrono;

  system_clock::time_point tp = system_clock::now();
  system_clock::duration dtn = tp.time_since_epoch();

  std::cout << "current time since epoch, expressed in:" << std::endl;
  std::cout << "periods: " << dtn.count() << std::endl;
  std::cout << "seconds: " << dtn.count() * system_clock::period::num /
    system_clock::period::den;
  std::cout << std::endl;
}

int main()
{
  fun();
  fun3();

  return 0;
}