#ifndef H_DB_MANAGE_H
#define H_DB_MANAGE_H

#include <iostream>
#include <map>

#include "object_manage.h"

struct user_with_money {
  user_with_money(int uid, float money, int credit_money = 0)
    :uid_(uid), money_(money)/*, credit_money_(credit_money)*/ {}
  int uid_;
  float money_;
  //int credit_money_;
};

class db {
public:
  db() {}
  ~db() {}

  //��ʼ�����ÿ����
  int increase_money(int uid, float money) {
    std::map<int, user_with_money>::iterator it = map_dbs_.find(uid);
    if(it == map_dbs_.end()) {
      // Ĭ���Զ����� (�����괢��Ľ��ף�
      user_with_money temp(uid, money, 0);
      map_dbs_.insert(std::pair<int, user_with_money>(uid, temp));
    } else {
      if (money > 0) {
        it->second.money_ += money;
      } else {
        std::cout<<"���д�Ǯ��֧�ִ��븺ֵ"<<std::endl;
        return -1;
      }
    }
    
    return 0;
  }

  //����ѯ
  int scan_money(int uid, float& left_money) {
    std::map<int, user_with_money>::iterator it = map_dbs_.find(uid);
    if(it == map_dbs_.end()) {
      return -1;
    } else {
      left_money = it->second.money_;
      std::cout<<"left money total is:"<<it->second.money_<<std::endl;
    }

    return 0;
  }

  //��Ǯ
  int reduce_money(int uid, float money) {
    if (money <= 0) {
      return -1;
    }

    //δ�ҵ��û�
    std::map<int, user_with_money>::iterator it = map_dbs_.find(uid);
    if(it == map_dbs_.end()) {
      std::cout<<"user not found in system, uid:"<<uid<<std::endl;
      return -1;
    }
    
    //����
    if (it->second.money_ < money)
    {
      std::cout<<"user bank saving is not enough!"<<std::endl;
      return -1;
    }

    it->second.money_ -= money;
    std::cout<<"after shopping, left money total is:"<<it->second.money_<<std::endl;

    return 0;
  }

private:
  std::map<int, user_with_money> map_dbs_;
};
#endif
