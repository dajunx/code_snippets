#include <iostream>
#include <map>
#include <string>
using namespace std;
/*
** Given a roman numeral, convert it to an integer.
** Input is guaranteed to be within the range from 1 to 3999.
*/
int romanToInt(string s) {
  map<char, int> map_roman_int;
  map_roman_int['I'] = 1;
  map_roman_int['V'] = 5;
  map_roman_int['X'] = 10;
  map_roman_int['L'] = 50;
  map_roman_int['C'] = 100;
  map_roman_int['D'] = 500;
  map_roman_int['M'] = 1000;

  string roman_str("IVXLCDM");

  //2.������У��
  ///TODO

  /*3.��ִ���
  ** 399 CCCXCIX �������������100 100 1000 10 100 1 10
  **  1�������Լ���ȣ�����Ӳ��ۼƣ�
  **  2���������Լ�����Ӳ��ۼƣ�
  **  3�����С���Լ������ۼ�ֵ��ȥ��ࣻ
  */
  int last_ch_num = 0, total_num = 0, ch_num = 0;
  for (string::reverse_iterator it=s.rbegin(); it != s.rend();++it)
  {
    //1.�Ƿ��ַ�У��
    if(roman_str.find(*it) == string::npos) {
      //���зǷ��ַ�
      return 0;
    }

    ch_num = map_roman_int.find(*it)->second;
    if(ch_num >= last_ch_num) {
      total_num += ch_num;
    } else if (ch_num < last_ch_num) {
      total_num -= ch_num;
    }
    last_ch_num = ch_num;
  }

  return total_num;
}

int main()     
{
  string input_romain_str("MCMXCVI");
  romanToInt(input_romain_str);

  int i = 0;
  return 0;
}