#include <stdio.h>
#include <winsock2.h>
#include <string>
#include <vector>

#pragma comment(lib,"ws2_32.lib")

DWORD WINAPI HandleClientMsg(LPVOID lpParameter) {
  SOCKET* pAcceptClientSocket = static_cast<SOCKET*>(lpParameter);

  //ʹ�����֣�Ϊ�˲鿴ʹ��clumsy�����¸����������������ݲ������
  std::vector<std::string> strvec;
  strvec.push_back("1");
  strvec.push_back("22");
  strvec.push_back("333");
  strvec.push_back("4444");
  strvec.push_back("55555");
  strvec.push_back("666666");
  strvec.push_back("7777777");

  int index = 0;
  while (true) {
    std::string strSrcData;
    if (7 == index) {
      index = 0;
    }
    strSrcData.append(strvec[index]);
    strSrcData.append("\n");
    send(*pAcceptClientSocket, strSrcData.c_str(), strSrcData.size(), 0);
    index++;
    Sleep(10);
  }

  //std::string strSrcData;
  //while (true) {
  //  if (strSrcData.compare("----------") == 0) {
  //    strSrcData.clear();
  //  }
  //  send(*pAcceptClientSocket, strSrcData.c_str(), strSrcData.size(), 0);
  //  strSrcData.append("-");
  //  Sleep(50);
  //}  

  closesocket(*pAcceptClientSocket);
  return 0L;
}

int main(int argc, char* argv[])
{
  //��ʼ��WSA
  WORD sockVersion = MAKEWORD(2,2);
  WSADATA wsaData;
  if(WSAStartup(sockVersion, &wsaData)!=0)
  {
    return 0;
  }

  //�����׽���
  SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(slisten == INVALID_SOCKET)
  {
    printf("socket error !");
    return 0;
  }

  //��IP�Ͷ˿�
  sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(8888);
  sin.sin_addr.S_un.S_addr = INADDR_ANY; 
  if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
  {
    printf("bind error !");
  }

  //��ʼ����
  if(listen(slisten, 5) == SOCKET_ERROR)
  {
    printf("listen error !");
    return 0;
  }

  //ѭ����������
  SOCKET sClient;
  sockaddr_in remoteAddr;
  int nAddrlen = sizeof(remoteAddr);
  while (true)
  {
    printf("�ȴ�����...\n");
    sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
    if(sClient == INVALID_SOCKET)
    {
      printf("accept error !");
      continue;
    }
    printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));

    //�����߳� ��������
    HANDLE thread_handler = CreateThread(NULL, 0, HandleClientMsg, &sClient, 0, NULL);
  }

  closesocket(slisten);
  WSACleanup();
  return 0;
}