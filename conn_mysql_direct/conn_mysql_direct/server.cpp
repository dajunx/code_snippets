#include <iostream>
#include <string>

#include "server_net.h" //server_net.h ���岻�ܷ� windows.hͷ�ļ�
#include "db.h"

int main() {
  net_manage net(tNetServer);
  net.accept_new_conn();
  
  worker w;
  std::string strReceiveData;
  w.chooseDatabase();
  w.start_handle_request();

  do 
  {
    net.receive_data(strReceiveData);

    //��¼һ��TCP�յ���sql����
    ///TODO ���⣺server�˽��ܵ��� sql����п��ܲ��������ģ��ر����ڵ�һ����¼��ʱ��
    ///��һ����¼����Ӷ���sql��䣡����
    IO io;
    io.wrapSave("server_receive_sql.log", strReceiveData + "\n");

    enumSqlType iSqlType = tInsert;
    data_box(tINPUT, iSqlType, strReceiveData);
    strReceiveData.clear();
    net.send_data("OK"); //Response
    //Sleep(1000);
  } while (true);

  return 0;
}