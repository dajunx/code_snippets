//c++ ��̬�� ��̬��
/*
pD->DoSomething(); pB->DoSomething(); �Ǿ�̬�󶨣����ø�����ĳ�Ա������
��pD->vfun(); pB->vfun(); �Ƕ�̬�󶨵ģ������� D���vfun������
*/
// url: http://blog.csdn.net/chgaowei/article/details/6427731

#include <iostream>

class B
{
public:
  void DoSomething() {};
  virtual void vfun() {};
};

class C : public B
{
public:
  void DoSomething() {};
  virtual void vfun() {};
};

class D : public B
{
public:
  void DoSomething() {};
  virtual void vfun() {};
};

int main()
{
  D* pD = new D();
  B* pB = pD;

  pD->DoSomething();
  pB->DoSomething();

  pD->vfun();
  pB->vfun();

  return 0;
}