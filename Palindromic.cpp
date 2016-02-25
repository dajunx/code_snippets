#include "define.h"
#include <map>

// ����
string longestPalindrome(string s)
{
	if(1 == s.size()) return s;
	char* substr_temp = new char[s.length() + 1];
	strcpy(substr_temp, s.c_str());
	substr_temp[s.length()] = '\0';
	char* p_substr = substr_temp;
	
	vector<char *> pos_near;//1. �ҳ����������ַ�λ��
	vector<char *> pos_1_near;//2. �ҳ����������ַ����һ��λ��
	pair<int,string> palindrome_pair = make_pair(0,"0");
	while(*p_substr != '\0' && p_substr+1 != NULL)
	{
		if(*p_substr == *(p_substr+1))
		{
			pos_near.push_back(p_substr);
		}
		if(*p_substr == *(p_substr+2) && *p_substr != *(p_substr+1))
		{
			pos_1_near.push_back(p_substr);
		}
		p_substr++;
	}

	//����1
	string temp;
	for (vector<char *>::iterator it=pos_near.begin(); it!= pos_near.end(); ++it)
	{
		temp.clear();
		char* p1 = *it;
		char* p2 = p1+1;
		while(p1 != NULL && p2 != NULL && *p1 == *p2) // ǰ���ƶ�Ԫ��ֵ��ͬ
		{
			p1--;p2++; // �����෴�����ƶ�
		}
		temp.append(++p1,p2);
		if(palindrome_pair.first < temp.size()) palindrome_pair = make_pair(temp.size(),temp);
	}

	//����2
	for (vector<char *>::iterator it=pos_1_near.begin(); it!= pos_1_near.end(); ++it)
	{
		temp.clear();
		char* p1 = *it;
		char* p2 = p1+2;
		while(p1 != NULL && p2 != NULL && *p1 == *p2) // ǰ���ƶ�Ԫ��ֵ��ͬ
		{
			p1--;p2++; // �����෴�����ƶ�
		}
		//temp.append(++p1,p2);
		temp.append(s,p1-substr_temp,p2-p1);
		if(palindrome_pair.first < temp.size()) palindrome_pair = make_pair(temp.size(),temp);
	}

	return palindrome_pair.second;
}

int main()
{
	string ss1("abcddcba");
	string ss2("abcddcbaeabcddcbae");
	string ss3("abcdedcba");
	string ss4("abcdedcbaeabcdfdcbae");
	string ss5("bb");
	string ret = longestPalindrome(ss3);
	return 0;
};