//�ټ���ģ��ʹ�÷���
#include <iostream>
class VV
{
public:
  static int getI()
  {
    return 100;
  }
};
class V
{
public:
  template<class K>
  void PrintK()
  {
    cout<<K::getI()<<endl;
  }
};
void m()
{
  V v;
  v.template PrintK<VV>();
}