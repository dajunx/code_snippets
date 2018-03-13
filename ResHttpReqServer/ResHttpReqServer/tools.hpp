
#ifndef HTTP_MIME_TYPES_HPP
#define HTTP_MIME_TYPES_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

/*
�ڴ��� http ����չ�ֵ�ͷ���ݣ����£�
GET /ReadMe.txt HTTP/1.1
Host: 127.0.0.1:9999
Connection: keep-alive
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.186 Safari/537.36

Ŀ���� /ReadMe.txt �ı�,ʹ�÷��� getTargetContent ��ȡ
*/

class Http {
public:
  Http() {}
  ~Http() {}

  void getTargetContent(char* receiveContent, std::string& targetContent) {
    std::string content(receiveContent);
    std::string::size_type target_begin = content.find_first_of(" ");
    std::string::size_type target_end = content.find(" ", target_begin+1);
    targetContent = content.substr(target_begin+2, target_end - target_begin - 1);
  }

  void produceResponse(const std::string& targetContent, std::string& reply) {
    if (false == reply.empty()) {
      return;
    }

    reply.append("HTTP/1.0 200 OK\r\n");
    reply.append("Content-Length: 29\r\n");
    reply.append("Content-Type: text/plain\r\n\r\n");

    std::string filePath("E:\\vs2010\\ResHttpReqServer\\ResHttpReqServer\\");
    filePath += targetContent;
    std::ifstream file(filePath, std::fstream::in);
    std::string s;
    while (getline(file, s)) {
      s.append("\r\n");
      reply += s;
    }

    file.close();
  }
};


#endif // HTTP_MIME_TYPES_HPP