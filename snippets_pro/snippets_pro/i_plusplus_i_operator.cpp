//i++ ��++i ����������
/*
Time operator++();//����++i;
Time operator++(int);//����i++��
C++Լ������������/�Լ����������һ��int�Ͳ�����
*/

#include <iostream>

class test1
{
public:
  test1():x(0) {}
  test1& operator++()
  {
    ++x;
    return *this;
  }
  test1& operator++(int)
  {
    test1 t1(*this);
    ++this->x;
    return *this;
  }
  int x;
};
int main()
{
  test1 t1;
  t1++;
  ++t1;
  return 0;
}