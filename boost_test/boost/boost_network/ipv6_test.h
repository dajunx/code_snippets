﻿// ipv6 转换测试

// header file.
//#include "boost/bind.hpp"
//#include <boost/asio.hpp>
//#include <iostream>
//#include <string>

const short multicast_port = 9999;

class receiver {
public:
  receiver(boost::asio::io_service &io_service,
           const boost::asio::ip::address &listen_address,
           const boost::asio::ip::address &multicast_address)
      : socket_(io_service) {
    // linjj test begin
    multicast_address.is_v6();
    // linjj test end
    // Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(listen_address,
                                                   multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    // Join the multicast group.
    socket_.set_option(
        boost::asio::ip::multicast::join_group(multicast_address));

    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(&receiver::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive_from(const boost::system::error_code &error,
                           size_t bytes_recvd) {
    std::cout << socket_.local_endpoint().address().to_string() << std::endl;
    if (!error) {
      std::cout.write(data_, bytes_recvd);
      std::cout << std::endl;

      socket_.async_receive_from(
          boost::asio::buffer(data_, max_length), sender_endpoint_,
          boost::bind(&receiver::handle_receive_from, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    }
  }

private:
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];
};

bool ipv6_test() {
  try {
    //     if (argc != 3)
    //     {
    //       std::cerr << "Usage: receiver <listen_address>
    //       <multicast_address>\n"; std::cerr << "  For IPv4, try:\n";
    //       std::cerr << "    receiver 0.0.0.0 239.255.0.1\n";
    //       std::cerr << "  For IPv6, try:\n";
    //       std::cerr << "    receiver 0::0 ff31::8000:1234\n";
    //       return 1;
    //     }
    std::string input_addr1 = "0::0";
    std::string input_addr2 = "ff31::8000:1234";

    boost::asio::io_service io_service;
    receiver r(io_service, boost::asio::ip::address::from_string(input_addr1),
               boost::asio::ip::address::from_string(input_addr2));
    io_service.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
