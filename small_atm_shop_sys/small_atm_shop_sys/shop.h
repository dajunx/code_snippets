#ifndef H_SHOP_H
#define H_SHOP_H

#include "users.h"
#include "bank.h"

class shop{
public:
  shop() {}
  ~shop() {}

  //���� (����ֻʵ�ֿۿ���Թ���ʵ��������);
  int doShopping(user* pUser)
  {
    if (NULL == pUser) {
      return -1;
    }


  }
};

#endif
