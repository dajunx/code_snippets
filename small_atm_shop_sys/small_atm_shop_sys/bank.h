#ifndef H_BANK_H
#define H_BANK_H

#include <sstream>

#include "object_manage.h"
#include "db_manage.h"
#include "users.h"
#include "tools.h"

class user;
class db;
class object_manage;

class bank{
public:
  bank() {}
  ~bank() {}

  //���� or ����
  int reduce_money(user* pUser, float money)
  {
    db& db_temp = object_manage::get_instance()->get_db();
    if (NULL == pUser) {
      return -1;
    }

    return db_temp.reduce_money(pUser->uid, money);
  }

  //ȡ��
  int borrow_money_to_users();

  //�յ�����
  int get_giveback();

  //��ѯ�û����
  int scan_user_leave_money(user* pUser, float& left_money)
  {
    db& db_temp = object_manage::get_instance()->get_db();
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    return db_temp.scan_money(pUser->uid, left_money);
  }

  //��ѯ�û�������Ŀ
  int scan_user_borrow_totals();

  //�û���ת��
  int exchange_money();

  //��Ǯ
  int increase_money(user* pUser, float money)
  {
    db& db_temp = object_manage::get_instance()->get_db();
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    db_temp.increase_money(pUser->uid, money);

    return 0;
  }

  //��ʼ���û��ʻ�
  int init_user_account(user* pUser, float money)
  {
    db& db_temp = object_manage::get_instance()->get_db();
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    db_temp.increase_money(pUser->uid, money);

    records& record_temp = object_manage::get_instance()->get_records();
    std::stringstream strLog;
    strLog << "[��ʼ���û�]:" << pUser->uid << " ���ÿ��ʻ�" << std::endl;
    record_temp.saveContentToFile("ATM.log", strLog.str());
    return 0;
  }

  //�����û����ö��
  int manage_user_credit_card_max();

  //�����û��˺�
  int freeze_user_account();
};

#endif
