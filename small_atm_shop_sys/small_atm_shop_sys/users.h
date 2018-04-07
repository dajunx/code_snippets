#ifndef H_USER_h
#define H_USER_h

#include <vector>

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
//private:
  int uid;
  em_user_type utype;
};

class user_manage {
public:
  user_manage() { }
  ~user_manage() { }

  // ��¼(��ͨ�û���¼������Ա��¼)
  int login(user* pUser);

  //����û� �����磺����û����û�������á������û������ַ��ʵ�����
  int add_user(user* pUser, em_user_type type)
  {
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    switch(type) {
    case normal_user:
      {
        vec_normal_users_.push_back(pUser);
      }
      break;
    case admin:
      {
        pAdmin_ = pUser;
      }
      break;
    default:
      break;
    }

    return 0;
  }

  // �����û�
  int freeze_user(user* pUser);

  // У���û�
  bool exist_pointed_user(user* pUser)
  {
    if (NULL == pUser) {
      return false; //������û�ָ�벻��Ϊ��
    }

    bool exist_pointed_user = false;
    std::vector<user*>::iterator it = vec_normal_users_.begin();
    for (; it!= vec_normal_users_.end(); ++it)
    {
      if (pUser == *it) {
        exist_pointed_user = true;
        break;
      }
    }

    return exist_pointed_user;
  }

//private:
  std::vector<user*> vec_normal_users_;
  user* pAdmin_;
};

#endif
