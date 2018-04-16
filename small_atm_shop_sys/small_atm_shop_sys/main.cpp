#include <iostream>

//user defined headers
#include "object_manage.h"
#include "bank.h"
#include "shop.h"
#include "terminal.h"
#include "users.h"
#include "db_manage.h"

int main() 
{
  object_manage* p_object_manage = object_manage::get_instance();
  //ע������û�
  p_object_manage->add_template_users();

  user& test_user1 = p_object_manage->get_user(661);
  user& test_user2 = p_object_manage->get_user(662);
  user& test_admin = p_object_manage->get_user(991);

  //��ʼ�����ÿ���ȣ�����15000)
  terminal& ter = p_object_manage->get_terminal();
  ter.init_credit_card(&test_user1,  15000);
  ter.init_credit_card(&test_user2,  15000);

  //�̵깺������
  shop& sh = p_object_manage->get_shop();
  sh.doShopping(&test_user1, 15000);
  sh.doShopping(&test_user2, 100);

  //�û�1���д��������û�2��Ǯ 100
  if ( 0 == ter.borrow_money_from_user(&test_user2, &test_user1, 100)) {
    //�赽��Ǯ����������
    sh.doShopping(&test_user1);
  }

  //��Ǯ
  ter.return_money(&test_user1, 15000);

  //����
  ter.borrow_money_from_bank(&test_user1, 100);

  /*
  ** �����û�
  */
  //�����û�
  user_manage& ugr = p_object_manage->get_user_manage();
  ugr.freeze_user(&test_user1, test_admin.utype);

  return 0;
}