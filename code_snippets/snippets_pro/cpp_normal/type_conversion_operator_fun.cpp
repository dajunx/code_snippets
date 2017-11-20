//����ת�������� operator int() const
/*
����ת�������� ��һ����������Ա�����������彫������ֵת��Ϊ��������ֵ��ת����ת�����������ඨ�������������ڱ����� operator ֮�����ת����Ŀ�����͡�
1. ת�����������ǳ�Ա����������ָ���������ͣ������βα����Ϊ�գ�����ֵ�������ģ�����ֵ����ת����������ͬ�ģ���Ϊ����ԭ���е�T2��
2. T2��ʾ������������built-in type��������������class type���������ͱ�����typedef����������֣�
  ���κο���Ϊ�����������͵����ͣ����� void ֮�⣩�����Զ���ת��������һ����ԣ�������ת��Ϊ����������ͣ�ת��Ϊָ�����ͣ����ݺͺ���ָ�룩�Լ����������ǿ��Եģ�
3. ת������һ�㲻Ӧ�øı䱻ת���Ķ������ת��������ͨ��Ӧ����Ϊ const ��Ա��
4. ֧�ּ̳У�����Ϊ�麯����
5. ֻҪ����ת�������������ڿ���ʹ������ת���ĵط��Զ���������
�ɸ�дΪ ģ�庯��
*/

#include <iostream>
using namespace std;
class D
{
public:
  D(double d):
    d_(d) {}
  operator int()const
  {
    cout << "(int)d called!!" << endl;
    return static_cast<int>(d_);
  }
  /*
  template <typename T>
  operator T()const
  {
    cout << "(int)d called!!" << endl;
    return static_cast<T>(d_);
  }
  */
private:
  double d_;
};

int add(int a, int b)
{
  return a + b;
}

int main()
{
  D d1 = 1.1;
  D d2 = 2.2;
  cout << "add(d1,d2)=" << add(d1, d2) << endl;
  return 0;

}