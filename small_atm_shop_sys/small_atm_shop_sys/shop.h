#ifndef H_SHOP_H
#define H_SHOP_H

#include "users.h"
#include "bank.h"

class shop{
public:
  shop() {}
  ~shop() {}

  //���� (����ֻʵ�ֿۿ���Թ���ʵ��������);
  int doShopping(user* pUser, bank& bk)
  {
    if (NULL == pUser) {
      return -1;
    }

    //ÿ��������ʱ��λ 10 ����λ
    return bk.reduce_money(pUser, 10);
  }
};

#endif
