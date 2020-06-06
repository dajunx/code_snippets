#pragma once

//#include <windows.h>
#include <WINSOCK2.H>
#include <STDIO.H>
#include <Ws2tcpip.h>

#pragma  comment(lib,"ws2_32.lib")

bool showSubNetErr()
{
  bool b_ret = false;
  switch (WSAGetLastError()) 
  {
  case WSAECONNREFUSED:
  {
    std::cout << "Connection refused." << std::endl;
    b_ret = true;
    break;
  }
  default:
    ;
    //std::cout<<"unknow err."<<std::endl;
  }

  return b_ret;
}

int handle_tcp_client()
{
  // 初始化网络
  WORD sockVersion = MAKEWORD(2, 2);
  WSADATA data;
  if (WSAStartup(sockVersion, &data) != 0)
  {
    return 0;
  }

  // 创建客户端 socket
  SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sclient == INVALID_SOCKET)
  {
    printf("invalid socket !");
    return 0;
  }

  sockaddr_in serAddr;
  serAddr.sin_family = AF_INET;
  serAddr.sin_port = htons(8888);
  serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

  while (true)
  {
    // 链接sever端
    int ret_conn = connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr));
    if (ret_conn == SOCKET_ERROR) 
    {
      std::cout << "connect server err:" << WSAGetLastError() << std::endl;
      break;
    }

    // 优化连接服务端：若没连接上服务端则sleep 1秒，直到连接上服务端；
    if (showSubNetErr()) {
      Sleep(1000);
      continue;
    }

    //接收客户端发送的数据并打印
    while (true) {
      char recData[255];
      int ret = recv(sclient, recData, 255, 0);
      if (ret > 0)
      {
        recData[ret] = 0x00;
        std::cout << recData/*<<std::endl*/;
      } else {
        std::cout << "recv server data err:" << WSAGetLastError() << std::endl;
        break;
      }
    }
  }

  // 清理网络资源
  closesocket(sclient);
  WSACleanup();
  return 0;
}