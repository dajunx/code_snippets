#include <iostream>
#include <vector>
#include <string>
using namespace std;

string longestCommonPrefix(vector<string>& strs)
{
  //�㷨��˫��ѭ��do_while + for �����ַ��������������ַ���Ч�ʽϵ�
  string str_ret;
  int vec_size = strs.size();
  int pos = 0;
  while (vec_size > 0) //case strsΪ��
  {
    char c_tmp;
    int i = 0;
    for (;i < vec_size;++i)
    {
      //�������ַ���������ĳ���ַ�ĩβ
      if (pos >= strs[i].length()) {
        break;
      }

      //�����ַ�����������ͬpos�ϲ�ͬ���ַ�
      if ( i != 0 && strs[i].at(pos) != c_tmp) {
        break;
      }
      c_tmp = strs[i].at(pos);
    }
    if (i != vec_size) {break;} //�ַ�������pos���ַ���һ��
    str_ret.append(1, c_tmp);
    pos ++;
  }

  return str_ret;
}

int main()
{
  vector<string> vec_str;
//   vec_str.push_back("-ab");
//   vec_str.push_back("abc");
//   vec_str.push_back("abcd");
  longestCommonPrefix(vec_str);

  return 0;
}