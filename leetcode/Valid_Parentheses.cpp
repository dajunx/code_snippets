//�㷨�⣺Valid Parentheses
/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/

#include <iostream>
#include <map>
#include <list>
using namespace std;

//˼·1�������ַ���ֵ����1����2�����Դ������ұ�������������ַ�������list�У�����ƥ��
bool isValid(string s)
{
  bool ret = false;
  do 
  {
    //�ַ���������Ϊż��
    if(s.size()%2 != 0) {
      break;
    }

    std::map<char, bool> map_tag_str;
    std::map<char, bool>::iterator it;
    map_tag_str.insert(std::pair<char, bool>('(', true));
    map_tag_str.insert(std::pair<char, bool>(')', false));
    map_tag_str.insert(std::pair<char, bool>('[', true));
    map_tag_str.insert(std::pair<char, bool>(']', false));
    map_tag_str.insert(std::pair<char, bool>('{', true));
    map_tag_str.insert(std::pair<char, bool>('}', false));

    bool sub_ret = true;
    std::list<char> set_chs;
    std::string::iterator str_begin = s.begin();
    for (int i = 0; str_begin != s.end(); ++str_begin)
    {
      //���ܰ��������ַ�
      it = map_tag_str.find(*str_begin);
      if(it == map_tag_str.end()) {
        sub_ret = false;
        break;
      }

      if(it->second) {
        set_chs.push_back(*str_begin);
        continue;
      }

      if(it->first - *(set_chs.rbegin()) != 1 
        && it->first - *(set_chs.rbegin()) != 2) {
        sub_ret = false;
        break;
      }
      set_chs.pop_back();
    }

    if(set_chs.size() != 0) {
      sub_ret = false;
    }

    ret = sub_ret;
  } while (false);

  return ret;
}

int main(int argc, char** argv)
{
  std::string str_input[10];
  str_input[1].append("((([])))");
  str_input[2].append("(()()[])");
  isValid(str_input[1]);
  isValid(str_input[2]);

  int i = 0;
  return 0;  
}