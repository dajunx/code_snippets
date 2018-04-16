#ifndef H_USER_h
#define H_USER_h

#include <iostream>
#include <vector>
#include <set>

#include "object_manage.h"

enum em_user_type{normal_user, admin};
enum em_card_type{bank_card, credit_card};

class user {
public:
  user() {}
  user(int input_udi, em_user_type type)
    :uid(input_udi),
     utype(type),
     bFreeze(false)
  {}
  ~user() {}
//private:
  int uid;
  em_user_type utype;
  bool bFreeze;
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
  int freeze_user(user* pUser, em_user_type type)
  {
    if (NULL == pUser) {
      return -1; //������û�ָ�벻��Ϊ��
    }

    switch(type) {
    case normal_user:
      {
        std::cout<<"normal user no right to manage user right."<<std::endl;
      }
      break;
    case admin:
      {
        std::vector<user*>::iterator it = vec_normal_users_.begin();
        for (; it!= vec_normal_users_.end(); ++it)
        {
          if (pUser == *it) {
            pUser->bFreeze = true;
            break;
          }
        }
      }
      break;
    default:
      break;
    }

    return 0;
  }

  // У���û�
  bool active_user(user* pUser)
  {
    if (NULL == pUser) {
      return false; //������û�ָ�벻��Ϊ��
    }

    bool is_active = false;
    std::vector<user*>::iterator it = vec_normal_users_.begin();
    for (; it!= vec_normal_users_.end(); ++it)
    {
      if (pUser == *it && pUser->bFreeze == false) {
        is_active = true;
        break;
      }
    }

    return is_active;
  }

//private:
  std::vector<user*> vec_normal_users_;
  user* pAdmin_;
};

#endif
