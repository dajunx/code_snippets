#pragma once

#include <stdio.h>
#include <winsock2.h>
#include <string>
#include <vector>

#pragma comment(lib,"ws2_32.lib")

DWORD WINAPI HandleClientMsg(LPVOID lpParameter) {
  SOCKET* pAcceptClientSocket = static_cast<SOCKET*>(lpParameter);

  std::string strSrcData, strSend;
  int ret_send = 0;
  while (true) {
    if (strSrcData.compare("----------") == 0) {
      strSrcData.clear();
    }
    strSend = strSrcData + "\n";
    ret_send = send(*pAcceptClientSocket, strSend.c_str(), strSend.size(), 0);
    if (ret_send < 0) {
      std::cout << "server child err:" << WSAGetLastError() << std::endl;
      break;
    }
    strSrcData.append("-");
    Sleep(50);
  }

  closesocket(*pAcceptClientSocket);
  return 0L;
}

int handle_tcp_server()
{
  //初始化WSA
  WORD sockVersion = MAKEWORD(2, 2);
  WSADATA wsaData;
  if (WSAStartup(sockVersion, &wsaData) != 0)
  {
    return 0;
  }

  //创建套接字
  SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (slisten == INVALID_SOCKET)
  {
    printf("socket error !");
    return 0;
  }

  //绑定IP和端口
  sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(8888);
  sin.sin_addr.S_un.S_addr = INADDR_ANY;
  if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
  {
    printf("bind error !");
  }

  //开始监听
  if (listen(slisten, 5) == SOCKET_ERROR)
  {
    printf("listen error !");
    return 0;
  }

  //循环接收数据
  SOCKET sClient;
  sockaddr_in remoteAddr;
  int nAddrlen = sizeof(remoteAddr);
  while (true)
  {
    printf("等待连接...\n");
    sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
    if (sClient == INVALID_SOCKET)
    {
      printf("accept error !");
      continue;
    }
    printf("接受到一个连接：%s, port:%d \r\n", inet_ntoa(remoteAddr.sin_addr), remoteAddr.sin_port);

    //另起线程 交互数据
    HANDLE thread_handler = CreateThread(NULL, 0, HandleClientMsg, &sClient, 0, NULL);
  }

  closesocket(slisten);
  WSACleanup();
  return 0;
}