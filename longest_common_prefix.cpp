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

string longestCommonPrefix2(vector<string>& strs)
{
  //�㷨��ÿ��ȥ�ַ���������2���ַ������ǰ׺��Ȼ�������ǰ׺��ȥ����һ���ַ����Աȣ�����
  string str_ret;
  if (strs.size() == 0) { return str_ret;}

  int strs_size = strs.size();
  int pos = 0, i = 1, mix_pos = 0;
  string equal_str;
  str_ret = strs[0];
  while (i < strs_size)
  {
    pos = 0;
    equal_str.clear();
    mix_pos = str_ret.length() < strs[i].length() 
              ? str_ret.length() : strs[i].length();
    while(pos < mix_pos && str_ret.at(pos) == strs[i].at(pos)) {
      equal_str.append(1, str_ret.at(pos));
      pos++;
    }

    str_ret.swap(equal_str);
    //�������ַ���û����ͬ������ؿ�ǰ׺
    if (equal_str.empty()) {
      break;
    }
    i++;
  }

  return str_ret;
}

int main()
{
  vector<string> vec_str;
  //vec_str.push_back("c");
  vec_str.push_back("aa");
  vec_str.push_back("ab");
  longestCommonPrefix2(vec_str);

  return 0;
}