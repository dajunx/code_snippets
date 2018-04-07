#ifndef H_TERMINAL_H
#define H_TERMINAL_H

///TODO(linjianjun) 2018.04.05 �ն���γ��󣬺�������˼�����ֻ��ն˺�ATM�ն��ȸ���ʵ��
//class terminal {
//public:
//  terminal() {}
//  ~terminal() {}
//};

#include "users.h"
#include "bank.h"

class user;
class user_manage;

class ATM{
public:
  ATM() {}
  ~ATM() {}

  // ����
  int borrow_money(user* pUser);

  // ����
  int giveBack_money(user* pUser);

  // �û����ö������
  static int set_user_credit_card_max(user* pUser);
};

//�ֻ��ն���ʱ��֧�֣�1�����ÿ���Ǯ��2�������ÿ��� �ȼ��ն˹��ܣ���������˼����չ��
class phone
{
public:
  phone() {}
  ~phone() {}

  // ������Ʒ (������ʱ���ɹ̶��ۿÿ�ο�һ�ٰɣ�)
  static int buy_something_from_shop(user* pUser);

  // ת�˸������û�
  static int exchange_money(user* pUserSrc, user* pUserDes);

  // ��Ǯ
  int stone_money(user_manage& mgr, user* pUser, int money)
  {
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    if (!mgr.exist_pointed_user(pUser)) {
      return -1; // Ҫ��Ǯ���û������ڣ���Ը��û�����
    }

    return bank_.stone_money(pUser, money);
  }

  // ����ѯ
  int scan_personal_money(user* pUser, em_card_type type)
  {
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    bank_.scan_user_leave_money(pUser);
  }

  // �鿴����������ˮ
  static int scan_personal_bank_detail(user* pUser);

private:
  bank bank_;
};

#endif
