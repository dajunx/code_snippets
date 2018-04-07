#ifndef H_BANK_H
#define H_BANK_H

#include "db_manage.h"
#include "users.h"

class user;
class db;

class bank{
public:
  bank() {}
  ~bank() {}

  //����
  int decrease_money();

  //ȡ��
  int borrow_money_to_users();

  //�յ�����
  int get_giveback();

  //��ѯ�û����
  int scan_user_leave_money(user* pUser)
  {
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    db_.scan_money(pUser->uid);
  }

  //��ѯ�û�������Ŀ
  int scan_user_borrow_totals();

  //�û���ת��
  int exchange_money();

  //����û�
  int add_user_account();

  //��Ǯ
  int stone_money(user* pUser, int money)
  {
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    db_.stone_money(pUser->uid, money);

    return 0;
  }

  //�����û����ö��
  int manage_user_credit_card_max();

  //�����û��˺�
  int freeze_user_account();

private:
  db db_;
};

#endif
