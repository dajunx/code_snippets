#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int lengthOfLongestSubstring(string s)
{
	unordered_map<char,int> cache_substr;
	int iSubStrLength = 0,lengthTemp = 0;
	char* str_temp = new char[s.length() + 1];
	strcpy(str_temp, s.c_str());
	str_temp[s.length()] = '\0';
	while ( '\0' != *str_temp)
	{
		if(cache_substr.find(*str_temp) == cache_substr.end())
		{
			cache_substr.insert(pair<char,int>(*str_temp,1));
			lengthTemp++;
		}
		else if(iSubStrLength <= lengthTemp) // �ҵ��ظ�ֵ ���ҳ��Ȳ�С�ڻ��泤��
		{
			iSubStrLength = lengthTemp;
			cache_substr.clear();// ����
			cache_substr.insert(pair<const char,int>(*str_temp,1)); // ��¼��ǰ����
			lengthTemp = 1;
		}
		str_temp ++;
	}
	if(iSubStrLength < lengthTemp) iSubStrLength = lengthTemp;
	return iSubStrLength;
}
int main(int argCount,char ** args)
{
	string input_str("c");
	lengthOfLongestSubstring(input_str);
	return 0;
};