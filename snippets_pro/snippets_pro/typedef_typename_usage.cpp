//typedef typename ����
/*
�����ע��ȡ�����ͻ����������󡣱���ʹ�ùؼ���typename��ԭ����T��һ��template parameter��
��ʵ����֮ǰ����������Tһ����֪����˲�֪��A::a_type �������һ��type����һ��member function����һ��data member��
ʹ��typename���Ը��߱���������һ��typeʹ�ñ�����˳��ͨ����
*/
// link:http://blog.csdn.net/fallstones/article/details/6265764

#include <iostream>
template<typename T>
class A
{
public:
  typedef T a_type;
};
template<typename A>
class B
{
public:
  //typedef A::a_type b_type;
  typedef typename A::a_type b_type;
  b_type x;
};

int main()
{
  B<A<int>> b;
  b.x = 9;
  return 0;
}