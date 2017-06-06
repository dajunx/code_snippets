
#include "network_mgr.h" //����
//#include "message_dispatch.h" // ��Ϣ�ַ�

int main()
{
  boost::asio::io_service io_service;
  boost::asio::io_service::work work(io_service);
  boost::thread th(boost::bind(&boost::asio::io_service::run, boost::ref(io_service)));
  th.detach();

  boost::uint32_t port = 9999;
  server s(io_service, port);
  s.accept_client_conn_loop();

  return 0;
}