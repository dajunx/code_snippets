#include <iostream>
// tcp
#include "normal_tcp/tcp_client.h"
#include "normal_tcp/tcp_server.h"
// udp
#include "normal_udp/udp_client.h"
#include "normal_udp/udp_server.h"

enum {e_TCP = 1, e_UDP};

/**
 * TCP
 */
// 另起线程 模拟客户端;
DWORD WINAPI tcp_client_server(LPVOID lpParameter) 
{
  handle_tcp_client();
  return 0L;
}

// 另起线程 模拟服务端;
DWORD WINAPI tcp_server_thread(LPVOID lpParameter) 
{
  handle_tcp_server();
  return 0L;
}

/**
 * UDP
 */
 // 另起线程 模拟客户端;
DWORD WINAPI udp_client_server(LPVOID lpParameter) 
{
  handle_udp_client();
  return 0L;
}

// 另起线程 模拟服务端;
DWORD WINAPI udp_server_thread(LPVOID lpParameter) 
{
  handle_udp_server();
  return 0L;
}

void dispatch_request(int type) {
  HANDLE thread_server_handle = NULL, thread_client_handle = NULL;

  // 分别启动两个线程，一个跑服务端、一个跑客户端
  switch (type) {
  case e_TCP:
  {
    thread_server_handle = CreateThread(NULL, 0, tcp_client_server, NULL, 0, NULL);
    thread_client_handle = CreateThread(NULL, 0, tcp_server_thread, NULL, 0, NULL);
  }
  break;
  case e_UDP:
  {
    thread_server_handle = CreateThread(NULL, 0, udp_client_server, NULL, 0, NULL);
    thread_client_handle = CreateThread(NULL, 0, udp_server_thread, NULL, 0, NULL);
  }
  break;
  default:
    break;
  }

  // 阻塞主线程，等待网络线程返回
  if (thread_server_handle && thread_client_handle) 
  {
    WaitForSingleObject(thread_server_handle, INFINITE);
    WaitForSingleObject(thread_client_handle, INFINITE);

    CloseHandle(thread_server_handle);
    CloseHandle(thread_client_handle);
  }  
}


int main()
{
  dispatch_request(e_TCP);

  return 0;
}