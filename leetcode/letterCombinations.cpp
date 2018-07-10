/*
17. Letter Combinations of a Phone Number
Given a string containing digits from 2-9 inclusive, 
  return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below. 
Note that 1 does not map to any letters.

˼·��ʹ�õݹ����ÿ�����ַ�������ϣ��㷨�о������׶�;
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void combinSubStrings(vector<string> inputStrings, vector<string>& retStrings, int index, string strTemp) {
  string currentStr = inputStrings.at(index);

  string::iterator it = currentStr.begin();
  for (;it != currentStr.end();++it)
  {
    stringstream currentTemp;
    currentTemp << strTemp << *it;

    if (index == 0) {
      retStrings.push_back(currentTemp.str());
    } else {
      combinSubStrings(inputStrings, retStrings, index-1, currentTemp.str());
    }
  }
}

vector<string> letterCombinations(string digits) {
  vector<std::string> retStrings;

  do 
  {
    if (digits.empty() || digits.find('0') != string::npos) {
      break;
    }

    int digitsNum = atoi(digits.c_str());
    string number2Strings[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<std::string> transferedStrings;

    // ����digits������ת���ɶ�Ӧ�Ź����ַ���
    for (; digitsNum != 0;)
    {
      transferedStrings.push_back(number2Strings[digitsNum%10]);
      digitsNum = digitsNum/10;
    }

    string temp;
    combinSubStrings(transferedStrings, retStrings, transferedStrings.size()-1, temp);
    
  } while (0);

  return retStrings;
}

///TODO ������ string��ȡ����������������
void testStringContentNum(string digits) {
  string::iterator it = digits.begin();
  for (; it != digits.end();++it)
  {
    //int temp = atoi(&(*it));
    // �޸ĳ����¼��ɣ�
    char temp = *it;
    int i = atoi(&temp);

    std::cout<<"temp: "<<i<<std::endl;
  }
}

int main()
{
  std::string inputStr("23");
  letterCombinations(inputStr);

  return 0;
}