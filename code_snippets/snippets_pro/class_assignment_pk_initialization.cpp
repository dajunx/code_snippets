
// class �� ��ʼ���͸�ֵ��ͬ�㣬ע��25~28�д��붯�������ȶ�t2����default���죬28���ڵ��ô���һ��int�����Ĺ��캯��������
#include <iostream>
#include <string>

#define call_with_max(a, b) 

class test2
{
public:
  test2() {j = 0;}
  test2(int a) { j = a;}
  test2& operator=(const test2& t2)
  {
    this->j = t2.j;
    return *this;
  }
  ~test2() {}
  int j;
};

class test1
{
public:
  test1(test2& t2)
  {
    int i = 0;
    a = t2;
  }
  ~test1() {}
  test2 a;
};

int main()
{
  test2 t2(5);
  test1 t1(t2);

  return 0;
}