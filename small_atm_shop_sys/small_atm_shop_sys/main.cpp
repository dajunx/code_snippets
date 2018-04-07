#include <iostream>

//user defined headers
#include "users.h"
#include "terminal.h"
#include "shop.h"

int main() 
{
  //��ʼ״̬��������û�������Ա ʵ��
  user lin001(661, normal_user), lin002(662, normal_user), lin_admin(991, admin);
  
  //��ӵ�����ϵͳ��
  user_manage ugr;
  ugr.add_user(&lin001, normal_user);
  ugr.add_user(&lin002, normal_user);
  ugr.add_user(&lin_admin, admin);

  bank bk;
  
  // -.- ��Ǯ(����)
  phone ph;
  ph.stone_money(ugr, &lin001, bk, 10);
  ph.stone_money(ugr, &lin002, bk, 1000);

  //����Ǯ��Ȼ�ǿ��������û������
  ph.scan_personal_money(&lin001, bank_card, bk);
  ph.scan_personal_money(&lin002, bank_card, bk);

  //�������Ϳ����������ˣ�����
  shop sh;
  sh.doShopping(&lin001, bk);
  sh.doShopping(&lin001, bk);

  //�û�1���д��������û�2��Ǯ 100
  if ( 0 == ph.borrow_money(&lin002, &lin001, bk, 100)) {
    //�赽��Ǯ����������
    sh.doShopping(&lin001, bk);
  }

  return 0;
}