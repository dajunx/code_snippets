//vector ������ʧЧ����
//��vector��ɾ��ĳ��Ԫ�ز���Ԫ��insert��ĩβ����Ӧ�ĵ�������ʧЧ

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/typeof/typeof.hpp>
#include <stdlib.h>

int main()
{
  std::vector<int> test;
  test.push_back(1);
  test.push_back(2);
  test.push_back(3);
  test.push_back(4);
  test.push_back(5);

  BOOST_AUTO(it, test.begin());
  int times = 1, size = test.size();
  for (;it!=test.end() && times <= size;++times )
  {
    if(*it == 5)
    {
      int temp = *it;
      it = test.erase(it);
      test.insert(test.end(), temp);
    }
    else
    {
      std::cout<<*it++<<std::endl;
    }
  }
  return 0;
}