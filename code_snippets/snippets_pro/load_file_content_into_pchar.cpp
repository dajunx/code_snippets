//���ı���ȡ���ݵ� char*��

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  std::ifstream file("E:\\boost_����\\asio.cpp", std::ios::in | std::ios::binary | std::ios::ate);
  if (file.is_open()) {
    file.seekg(0, ios::end);
    int size = file.tellg();
    char* contents = new char [size];
    file.seekg(0, ios::beg);
    file.read(contents, size);
    contents[size] = '\0';
    file.close();
    //... do something with it
    delete [] contents;
  }
}