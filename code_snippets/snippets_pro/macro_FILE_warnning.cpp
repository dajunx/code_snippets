//__FILE__ ȫ·�������·������
/*
__FILE__ ����debugģʽ�£�h��cpp�ļ�����ȫ·������releaseģʽ�£�h��ȫ·����cpp�����·��
*/

#include <iostream>
#include <string>
#include "common.h"
using namespace std;

int main(int argc, char* argv[])
{
  show();
  std::string path = __FILE__;
  cout << "__FILE__ => " << path << endl;
  return 0;
}