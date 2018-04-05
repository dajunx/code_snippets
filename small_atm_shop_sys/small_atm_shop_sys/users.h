#ifndef H_USER_h
#define H_USER_h

enum em_user_type{normal_user, admin};
enum em_card_type{bank_card, credit_card};

class user {
public:
  user() {}
  user(int input_udi, em_user_type type)
    :uid(input_udi),
     utype(type)
  {}
  ~user() {}

private:
  int uid;
  em_user_type utype;
};

class user_manage {
public:
  user_manage() { }
  ~user_manage() { }

  // ������Ʒ (������ʱ���ɹ̶��ۿÿ�ο�һ�ٰɣ�)
  static int buy_something_from_shop(user* pUser);

  // ת�˸������û�
  static int exchange_money(user* pUserSrc, user* pUserDes);

  // ����
  static int borrow_money(user* pUser);

  // ����
  static int giveBack_money(user* pUser);

  // ��Ǯ
  static int stone_money(user* pUser, int money);

  // ����ѯ
  static int scan_personal_money(user* pUser, em_card_type type);

  // �鿴����������ˮ
  static int scan_personal_bank_detail(user* pUser);

  // ��¼(��ͨ�û���¼������Ա��¼)
  static int login(user* pUser);

  //�û����� �����磺����û����û�������á������û������ַ��ʵ�����
  static int add_user(user* pUser, em_user_type type){

  }

  static int set_user_credit_card_max(user* pUser);
  static int freeze_user(user* pUser);
};

#endif
