#include <iostream>
#include <vector>
#include <stdio.h>
#include <map>
using namespace std;

// ����
string longestPalindrome(string s)
{
	if(1 == s.size()) return s;
	string str_ret;

	vector<int> pos_near;//1. �ҳ����������ַ�λ��
	vector<int> pos_1_near;//2. �ҳ����������ַ����һ��λ��
	for(int i=0;i<s.size();++i)
	{
		if(i+1 < s.size() && s.at(i) == s.at(i+1))
		{
			pos_near.push_back(i);
		}
		if(i+2 < s.size() && s.at(i) == s.at(i+2))
		{
			pos_1_near.push_back(i);
		}
	}

	//����1
	string temp;
	for (vector<int>::iterator it=pos_near.begin(); it!= pos_near.end(); ++it)
	{
		temp.clear();
		int pos1 = *it;
		int pos2 = pos1+1;
		while(pos1 != -1 && pos2 <s.size() && s.at(pos1) == s.at(pos2)) // ǰ���ƶ�Ԫ��ֵ��ͬ
		{
			pos1--;pos2++; // �����෴�����ƶ�
		}
		++pos1;
		temp.append(s.begin()+pos1, s.begin() + pos2);
		if(str_ret.size() < temp.size())
		{
			str_ret.clear();
			str_ret.append(temp);
		}
	}

	//����2
	for (vector<int>::iterator it=pos_1_near.begin(); it!= pos_1_near.end(); ++it)
	{
		temp.clear();
		int pos1 = *it;
		int pos2 = pos1+2;
		while(pos1 != -1 && pos2 <s.size() && s.at(pos1) == s.at(pos2)) // ǰ���ƶ�Ԫ��ֵ��ͬ
		{
			pos1--;pos2++; // �����෴�����ƶ�
		}
		++pos1;
		temp.append(s.begin()+pos1, s.begin() + pos2);
		if(str_ret.size() < temp.size())
		{
			str_ret.clear();
			str_ret.append(temp);
		}
	}

	return str_ret;
}

int main()
{
	string ss1("abcddcba");
	string ss2("abcddcbaeabcddcbae");
	string ss3("abcdedcba");
	string ss4("abcdedcbaeabcdfdcbae");
	string ss5("ccc");
	string ret = longestPalindrome(ss5);
	return 0;
};