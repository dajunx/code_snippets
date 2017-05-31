//ͷ�ļ�static���� �����cpp���� ���ݹ�������
/*
��hͷ�ļ��к���static��������ͷ�ļ������cpp�ļ������Ҵ˷��������ݹ����ʱ�� ������������ڣ�
1����static�����������У��� ���cpp�ļ������� static�������ݡ���֮ static�����У�����
2����static���� ���ܷ���ͷ�ļ��У��������ӳ���(error LNK2005: "void __cdecl fun3(void)" 
(?fun3@@YAXXZ) already defined in test.obj��fatal error LNK1169: one or more multiply defined symbols found)��
���е��޸ķ�ʽ�Ƿ�static������������ͷ�ļ����������һ��cpp�ļ��С�
*/
#include <boost/thread/thread.hpp>
#include <vector>
#include "common.h"
std::map<int, int> map_int;
test2 t2;
boost::mutex mutex_main;

void fun1()
{
  int index = 0;
  for (int i=0;i< 1000; ++i) {
    boost::mutex::scoped_lock l(mutex_main);
    index = t2.show();
    map_int.insert(std::make_pair<int,int>(index, index));
  }  
}

void fun2()
{
  int index = 0;
  for (int i=0;i< 1000; ++i) {
    boost::mutex::scoped_lock l(mutex_main);
    index = test2::get_request_id();
    map_int.insert(std::make_pair<int,int>(index, index));
  }
}

void check()
{
  for (int i=0;i< 2000; ++i) {
    if(i != map_int[i]) {
      std::cout<<"err,index: "<<i<<", value: "<<map_int[i]<<std::endl;
    }
  }
}

int main(int argc, char* argv[])
{
  boost::thread th1(fun1);
  boost::thread th2(fun2);
  th1.detach();
  th2.detach();

  boost::this_thread::sleep(boost::posix_time::seconds(5));
  check();
  return 0;
}

//-----------------------------------------------------------
//  common.h:
#include <boost/thread/mutex.hpp>

class test2
{
public:
  test2();
  ~test2();
  int show();

  static int get_request_id()
  {
    int ret;
    static boost::mutex mutex_request_id_seq_;
    static volatile int request_id_seq_;
    {
      boost::mutex::scoped_lock l(mutex_request_id_seq_);
      request_id_seq_ ++;
      if (request_id_seq_ == 0) {
        request_id_seq_++;
      }
      ret = request_id_seq_;
    }

    return ret;
  }
};

//-----------------------------------------------------------
//  test2.cpp:

#include "common1.h"

test2::test2()
{

}

test2::~test2()
{

}

int test2::show()
{
  return get_request_id();
}
