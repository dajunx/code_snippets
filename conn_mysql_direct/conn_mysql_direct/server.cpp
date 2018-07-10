#include <iostream>
#include <string>

#include "server_net.h" //server_net.h ���岻�ܷ� windows.hͷ�ļ�
#include "db.h"

#include <Windows.h>

void appendTimeFollowedByString(std::string& str) {
  SYSTEMTIME tt;
  std::stringstream str_date;

  GetLocalTime(&tt);
  str_date << "[" << tt.wYear << "-" << tt.wMonth << "-" << tt.wDay << " "
    << tt.wHour << ":" << tt.wMinute << ":" << tt.wSecond
    << ":" << tt.wMilliseconds << "] ";
  str_date << str;
  str.swap(str_date.str());
}

int main() {
  net_manage net(tNetServer);
  net.accept_new_conn();
  
  worker w;
  std::string strReceiveData, strReceiveDataTemp;
  w.chooseDatabase();
  w.start_handle_request();

  do 
  {
    net.receive_data(strReceiveData);
    strReceiveDataTemp = strReceiveData;

    //��¼һ��TCP�յ���sql����
    ///TODO ���⣺server�˽��ܵ��� sql����п��ܲ��������ģ��ر����ڵ�һ����¼��ʱ��
    ///��һ����¼����Ӷ���sql��䣡����

    enumSqlType iSqlType = tInsert;
    data_box(tINPUT, iSqlType, strReceiveData);

    IO io;
    appendTimeFollowedByString(strReceiveDataTemp);
    io.wrapSave("server_receive_sql.log", strReceiveDataTemp + "\n");
    strReceiveData.clear();
    net.send_data("OK"); //Response
    //Sleep(1000);
  } while (true);

  return 0;
}