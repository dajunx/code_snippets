#ifndef COMMON_FUN
#define COMMON_FUN

#include "common_def.h"

// �����������һ������/ֵ ��;
// set foo lin; get foo; shutdown;
///TODO ������� ��inline֮�� ���Ӵ�����ʾ main���� network_mgr �б�ʶ����ͻ
inline void parse_cmd_and_content(char* content, std::string& msg, std::string& key, std::string& value)
{
  if (!content) return;

  char* p_ch = content;
  std::string pair;
  bool first_para = true;

  while (*p_ch != '\0') {
    if (*p_ch != ' ') {
      pair.push_back(*p_ch);
    } else if (*p_ch == ' ') {
      if (!pair.empty() ) {
        first_para? msg = pair : key = pair;
        first_para = false;
      }
      pair.clear();
    }
    p_ch++;
  }

  if ( !pair.empty() ) {
    first_para? msg = pair : value = pair;
  }
}

inline void file_read()
{
  std::string str;
  std::fstream file("file.txt", std::fstream::in);
  file>>str;
  std::cout<<str;
  file.close();
}

inline void file_write()
{
  std::fstream file("file.txt",
    std::fstream::in | std::fstream::out | std::fstream::app);
  file<<"lin";
  file.close();
}

#endif