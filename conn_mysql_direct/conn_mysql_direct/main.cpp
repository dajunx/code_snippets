#include <iostream>
#include <string>

#include "net.h" //net.h ���岻�ܷ� windows.hͷ�ļ�
#include "db.h"

int main() {
  net_manage net(tNetServer);

  worker w;
  w.chooseDatabase();
  w.execute_sql();

  return 0;
}