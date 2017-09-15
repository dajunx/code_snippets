#ifndef SERVICE
#define SERVICE

#include "network_mgr.h"

class service
{
public:
  service() {
    running_ = false;
  }
  ~service() {}
  void init_net(boost::asio::io_service& io_service, short port, boost::shared_ptr<data_mgr>& ptr_data_mgr);

  // �����Ӵ� socket ����
  void accept_connecter_loop();

  // ? ���ݷַ�

public:
  bool running_;
  boost::shared_ptr<network_mgr> net_mgr;
};

#endif