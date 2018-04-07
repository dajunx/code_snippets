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
  
  // -.- ��Ǯ(����)
  phone ph;
  ph.stone_money(ugr, &lin001, 1000);
  ph.stone_money(ugr, &lin002, 1000);

  //����Ǯ��Ȼ�ǿ��������û������
  ph.scan_personal_money(&lin001, bank_card);
  ph.scan_personal_money(&lin002, bank_card);

  //�������Ϳ����������ˣ�����
  //phone::buy_something_from_shop(lin001);
  //phone::scan_personal_money(lin001, bank_card); //���ֺ�����鿴


  return 0;
}