#ifndef H_BANK_H
#define H_BANK_H

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
  int scan_user_leave_money();

  //��ѯ�û�������Ŀ
  int scan_user_borrow_totals();

  //�û���ת��
  int exchange_money();

  //����û�
  int add_user_account();

  //�����û����ö��
  int manage_user_credit_card_max();

  //�����û��˺�
  int freeze_user_account();
};

#endif
