#include <iostream>

//user defined headers
#include "users.h"
#include "terminal.h"
#include "shop.h"
#include "bank.h"
#include "db_manage.h"

int main() 
{
  //��ʼ״̬��������û�������Ա ʵ��
  user lin001(661, normal_user), lin002(662, normal_user), lin_admin(991, admin);
  
  //��ӵ�����ϵͳ��
  user_manage::add_user(&lin001, normal_user);
  user_manage::add_user(&lin002, normal_user);
  user_manage::add_user(&lin_admin, admin);
  
  // -.- ��Ǯ(����)
  user_manage::stone_money(&lin001, 1000);
  user_manage::stone_money(&lin002, 1000);

  //����Ǯ��Ȼ�ǿ��������û������
  user_manage::scan_personal_money(lin001, bank_card);
  user_manage::scan_personal_money(lin002, bank_card);

  //�������Ϳ����������ˣ�����
  user_manage::buy_something_from_shop(lin001);
  user_manage::scan_personal_money(lin001, bank_card); //���ֺ�����鿴



  return 0;
}