#ifndef H_TERMINAL_H
#define H_TERMINAL_H

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
  int borrow_money(user* pUserSrc, user* pUserDes, bank& bk, int money)
  {
    //����У��
    if(NULL == pUserSrc || NULL == pUserDes || money < 0) {
      std::cout<<"parameter is not allow!"<<std::endl;
    }

    //�鿴����Ǯ����Ǯ������
    int left_money = 0;
    bk.scan_user_leave_money(pUserSrc, left_money);
    if (left_money < money) {
      std::cout<<"user has not enough to borrow to others."<<std::endl;
    }

    //��Ǯ
    bk.reduce_money(pUserSrc, money);
    bk.stone_money(pUserDes, money);
    std::cout<<"user: "<<pUserSrc->uid
            <<"borrow "<<money
            <<" money to user: "<<pUserDes->uid
            <<" success."<<std::endl;

    return 0;
  }

  // ��Ǯ
  int stone_money(user_manage& mgr, user* pUser, bank& bk, int money)
  {
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    if (!mgr.exist_pointed_user(pUser)) {
      return -1; // Ҫ��Ǯ���û������ڣ���Ը��û�����
    }

    return bk.stone_money(pUser, money);
  }

  // ����ѯ
  int scan_personal_money(user* pUser, em_card_type type, bank& bk)
  {
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    ///TODO. ����ط��е����ţ��ٸĸ�
    int left_money = 0;
    return bk.scan_user_leave_money(pUser, left_money);
  }

  // �鿴����������ˮ
  static int scan_personal_bank_detail(user* pUser);
};

#endif
