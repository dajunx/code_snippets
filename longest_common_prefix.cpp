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
      if (pos >= static_cast<int>(strs[i].length())) {
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

//�ܵ��㷨��
/*
** 1��vector�գ� 2��vectorֻ��1��Ԫ�أ� 
** 3���Ա��߼���a�������ַ����Ҳ�������ǰ׺ --> return �մ�
**            b����ȡ����ַ�ǰ׺ tmp����tmp��vector<string>����һ�� ���жԱ�
**            c������
*/
string longestCommonPrefix2(vector<string>& strs)
{
  //�㷨��ÿ��ȥ�ַ���������2���ַ������ǰ׺��Ȼ�������ǰ׺��ȥ����һ���ַ����Աȣ�����
  string equal_str;
  if (strs.size() == 0) { return equal_str;}

  int strs_size = strs.size();
  int pos = 0, i = 1, mix_pos = 0;
  equal_str = strs[0];
  while (i < strs_size)
  {
    pos = 0;
    mix_pos = equal_str.length() < strs[i].length() 
              ? equal_str.length() : strs[i].length();
    while(pos < mix_pos && equal_str.at(pos) == strs[i].at(pos)) {
      pos++;
    }

    ///TODO string��swap�����й��� linux�˱������ʾ����error
    /*
    **error: cannot bind non-const lvalue reference of type 'std::__cxx11::basic_string<char>&' 
    ** to an rvalue of type 'std::__cxx11::string {aka std::__cxx11::basic_string<char>}'
    */
    string tmp(equal_str, 0, pos);
    equal_str.swap(tmp);
    //�������ַ���û����ͬ������ؿ�ǰ׺
    if (equal_str.empty()) {
      break;
    }
    i++;
  }

  return equal_str;
}

int main()
{
  vector<string> vec_str;
  vec_str.push_back("c");
//   vec_str.push_back("acc");
//   vec_str.push_back("ccc");
  longestCommonPrefix2(vec_str);

  return 0;
}