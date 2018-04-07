#ifndef H_DB_MANAGE_H
#define H_DB_MANAGE_H

#include <iostream>
#include <map>

struct user_with_money {
  user_with_money(int uid, int money, int credit_money = 0)
    :uid_(uid), money_(money), credit_money_(credit_money) {}
  int uid_;
  int money_;
  int credit_money_;
};

class db {
public:
  db() {}
  ~db() {}

  //��Ǯ
  int stone_money(int uid, int money) {
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
  int scan_money(int uid) {
    std::map<int, user_with_money>::iterator it = map_dbs_.find(uid);
    if(it == map_dbs_.end()) {
      return -1;
    } else {
      std::cout<<"left money total is:"<<it->second.money_<<std::endl;
    }

    return 0;
  }

private:
  std::map<int, user_with_money> map_dbs_;
};
#endif
