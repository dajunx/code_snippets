
#include "network_mgr.h" //����
//#include "message_dispatch.h" // ��Ϣ�ַ�
#include "data_mgr.h" //���ݲ�
#include "common_fun.h" //����������
#include "service.h"

void init(boost::shared_ptr<data_mgr>& ptr_data_mgr)
{
  ptr_data_mgr = boost::make_shared<data_mgr>();
}

int main()
{
  boost::shared_ptr<data_mgr> ptr_data_mgr;
  init(ptr_data_mgr);

  boost::asio::io_service io_service;
  boost::asio::io_service::work work(io_service);
  boost::thread th(boost::bind(&boost::asio::io_service::run, boost::ref(io_service)));
  th.detach();

  boost::uint32_t port = 9999;

  service ser;
  ser.init_net(io_service, port, ptr_data_mgr);
  ser.accept_connecter_loop();

  return 0;
}