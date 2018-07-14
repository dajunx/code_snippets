#include <iostream>
#include <sstream>
#include <string>

#include "client_net.h"

int main() {
  // client ������
  Sleep(200);

  net_manage net(tNetClient);
  int ret = net.conn_server();
  if (ret) {
    std::cout << "connecting server failed, error code:" << ret << std::endl;
    return 0;
  }

  ///TODO ҵ���߼�������ּ�
  std::stringstream ssql;
  std::string strResponse;
  for (int i = 0; i < 1000; i++) {
    ssql << "insert into test.test values(" << i << ", " << i << i << ");";
    int ret = net.send_data(ssql.str());

    // ���ܻذ�������server�˽�����why��(���ݷ��棺���������͵��������׽ضϣ����������ݴ�����)
    net.receive_data(strResponse);
    if (strResponse.compare("OK") != 0) {
      std::cout << "sql: " << ssql.str() << ", is not execute right."
        << "content: " << strResponse << std::endl;
    } else {
      IO io;
      ssql << " result:" << strResponse << "\n";
      std::string ss_log = ssql.str();
      io.wrapSave("client_req_rsp.log", ss_log);
      strResponse.clear();
    }      

    ssql.str("");
    //Sleep(10);
  }
  std::cout << "send datas finished." << std::endl;

  do {
    Sleep(1000);
  } while (true);

  return 0;
}