#include <iostream>

#include "client.h"
#include "server.h"

// �����߳� ģ��ͻ���;
DWORD WINAPI client_server(LPVOID lpParameter) {
  handle_client();
  return 0L;
}

// �����߳� ģ������;
DWORD WINAPI server_thread(LPVOID lpParameter) {
  handle_server();
  return 0L;
}

int main() {
  HANDLE thread_server_handler = CreateThread(NULL, 0, server_thread, NULL, 0, NULL);
  HANDLE thread_client_handler = CreateThread(NULL, 0, client_server, NULL, 0, NULL);

  WaitForSingleObject(thread_server_handler, INFINITE);
  WaitForSingleObject(thread_client_handler, INFINITE);

  CloseHandle(thread_server_handler);
  CloseHandle(thread_client_handler);

  //while (true) {
  //  Sleep(1000);
  //}

  return 0;
}