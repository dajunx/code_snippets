//c++ ��ֵ������ �� �������� ����������

#include <iostream>
#include <map>
#include <vector>
#include <string>

struct test1
{
  int x;
  test1(int w=0) {x= w;}
  
  //������ֵ���أ������copying �� ���캯����ѭ��
  //const test1 operator = (const test1& o)

  const test1& operator = (const test1& o)
  {
    x = o.x;
    return *this;
  }
  test1(const test1& o)
  {
    *this = o;
  }
};
int main()
{
  test1 tt1(5);
  test1 tt2 = tt1;
  return 0;
}