//��ί��

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/function.hpp>

void englishgreeting(std::string name)
{
  std::cout<<"Morning, "<<name<<std::endl;
}

void chinesegreeting(std::string name)
{
  std::cout<<"���Ϻ�, "<<name<<std::endl;
}

void GreetPople(std::string name, boost::function<void(std::string)> fun)
{
  fun(name);
}

int main()
{
  GreetPople("lin", boost::bind(chinesegreeting, _1));
  GreetPople("xxx", boost::bind(chinesegreeting, _1));
  return 0;
}