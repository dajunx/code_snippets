//new ����һ����ʽ
/*
new ��ʱ�����Ѿ������ڴ�ĵ�ַ���ظ��������ڴ�ָ�롣�Ƚ�����
*/

#include <iostream>
class test
{
public:
  test() {}
  ~test() {}
};

int main()
{
  void* pp = new int(5);
  //int* pp = new int(5); // this way has the same result
  int* p = new(pp) int();
  return 0;
}