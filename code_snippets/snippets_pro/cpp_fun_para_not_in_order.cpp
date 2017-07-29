/*
���� effective c++ item.17 
c++�������ò��� �����������ض�������ɺ��������ĺ��㣬��54�д���ĵ���˳��
    ���������� new man,boost::shared_ptr,right ��˳��
    ��ʵ˳���� new man,right��boost::shared_ptr ��˳�򣡣���
*/

#include <iostream>
#include <string>
#include <fstream>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
using namespace std;

void write(std::string& data)
{
  std::fstream file("file.txt",
    std::fstream::in | std::fstream::out | std::fstream::app);
  file<<data;
  file.close();
}

class Man
{
public:
  Man() {
    std::string tmp("new man");
    write(tmp);
  }
  ~Man() {
    std::string tmp("releaes man");
    write(tmp);
    std::cout<<"i'm a man."<<std::endl;
  }
  void show_data() {
    std::cout<<"man show data."<<std::endl;
  }
};

void fun1(boost::shared_ptr<Man> ptr_tmp, int rights)
{
  ptr_tmp->show_data();
}

int right()
{
  throw 0;
  return 5;
}

int main()
{
  // ����ʹ�� Man�������ʱ���� �ڴ�й¶������
  try
  {
    fun1(boost::shared_ptr<Man>(new Man()), right());
  }
  catch (...)
  {
    int j = 0;
  }

  int i = 0;
  return 0;
}