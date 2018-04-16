#ifndef H_TERMINAL_H
#define H_TERMINAL_H

#include "object_manage.h"

class user;
class user_manage;

class terminal{
public:
  terminal() {}
  ~terminal() {}

  int init_credit_card(user* pUser, float money)
  {
    bank& bk = object_manage::get_instance()->get_bank();
    if (NULL == pUser || money < 0) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    return bk.increase_money(pUser, money);
  }

  // ת�˸������û�
  int borrow_money_from_user(user* pUserSrc, user* pUserDes, float money)
  {
    bank& bk = object_manage::get_instance()->get_bank();
    //����У��
    if(NULL == pUserSrc || NULL == pUserDes || money < 0) {
      std::cout<<"parameter is not allow!"<<std::endl;
    }

    //�鿴����Ǯ����Ǯ������
    float left_money = 0;
    bk.scan_user_leave_money(pUserSrc, left_money);
    if (left_money < money) {
      std::cout<<"user has not enough to borrow to others."<<std::endl;
    }

    //��Ǯ
    bk.reduce_money(pUserSrc, money);
    bk.increase_money(pUserDes, money);
    std::cout<<"user: "<<pUserSrc->uid
      <<"borrow "<<money
      <<" money to user: "<<pUserDes->uid
      <<" success."<<std::endl;

    return 0;
  }

  // �������ÿ�Ǯ
  int return_money(user* pUser, float money)
  {
    user_manage& mgr = object_manage::get_instance()->get_user_manage();
    bank& bk = object_manage::get_instance()->get_bank();
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    if (!mgr.active_user(pUser)) {
      return -1; // Ҫ��Ǯ���û������ڣ���Ը��û�����
    }

    return bk.increase_money(pUser, money);
  }

  // ����ѯ
  int scan_personal_money(user* pUser)
  {
    bank& bk = object_manage::get_instance()->get_bank();
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    ///TODO. ����ط��е����ţ��ٸĸ�
    float left_money = 0;
    return bk.scan_user_leave_money(pUser, left_money);
  }

  int borrow_money_from_bank(user* pUser, float money)
  {
    bank& bk = object_manage::get_instance()->get_bank();
    if (NULL == pUser) {
      return -1;
    }

    //ÿ��������ʱ��λ 10 ����λ
    return bk.reduce_money(pUser, money * 1.05);
  }

  // �鿴����������ˮ
  static int scan_personal_bank_detail(user* pUser);
};

#endif
