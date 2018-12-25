//从文本读取内容到 char*中

#include "cplusplus_common_def.hpp"
// header file.
//#include <fstream>
//#include <iostream>
using namespace std;

bool test_load_file_content_into_pchar() {
  std::ifstream file("E:\\boost_例子\\asio.cpp",
                     std::ios::in | std::ios::binary | std::ios::ate);
  if (file.is_open()) {
    file.seekg(0, ios::end);
    int size = file.tellg();
    char *contents = new char[size];
    file.seekg(0, ios::beg);
    file.read(contents, size);
    contents[size] = '\0';
    file.close();
    //... do something with it
    delete[] contents;
  }

  return true;
}