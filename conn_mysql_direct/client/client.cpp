#include <iostream>
#include <sstream>
#include <string>

#include "client_net.h"

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
  // client ������
  Sleep(200);

  net_manage net(tNetClient);
  int ret = net.conn_server();
  if (ret) {
    std::cout << "connecting server failed, error code:" << ret << std::endl;
  } else {
    std::stringstream ssql;
    std::string strResponse;
    for (int i = 0; i < 1000; i++) {
      ssql << "insert into test.test values(" << i << ", " << i << i << ");";
      int ret = net.send_data(ssql.str());

      // ���ܻذ�����˴����벻���ذ��������죿
      // (���ݷ��棺���������͵��������׽ضϣ����������ݴ�����)
      net.receive_data(strResponse);
      if (strResponse.compare("OK") != 0) {
        std::cout << "sql: " << ssql.str() << ", is not execute right."
                  << "content: " << strResponse << std::endl;
      }

      IO io;
      ssql << " result:" << strResponse << "\n";
      std::string ss_log = ssql.str();
      appendTimeFollowedByString(ss_log);
      io.wrapSave("client_req_rsp.log", ss_log);
      strResponse.clear();

      ssql.str("");
      //Sleep(10);
    }
    std::cout << "send datas finished." << std::endl;
  }

  do {
    Sleep(1000);
  } while (true);

  return 0;
}