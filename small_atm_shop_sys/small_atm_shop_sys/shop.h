#ifndef H_SHOP_H
#define H_SHOP_H

#include "object_manage.h"

class shop{
public:
  shop() {}
  ~shop() {}

  //���� (����ֻʵ�ֿۿ���Թ���ʵ��������);
  int doShopping(user* pUser, float money = 100)
  {
    bank& bk = object_manage::get_instance()->get_bank();
    if (NULL == pUser) {
      return -1;
    }

    //ÿ��������ʱ��λ 10 ����λ
    return bk.reduce_money(pUser, money);
  }
};

#endif
