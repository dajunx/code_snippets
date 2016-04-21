#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdint.h>

int64_t myAtoi(std::string str) {
	// ���ַ���
	if(str.length() == 0)
		return 0;
	bool bnegativeNum = false; //����
	std::string str_tmp = str;
	char bad_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";


	// ȥ������ո�
	for (;str_tmp.find(" ") == 0 || str_tmp.find(" ") == str_tmp.length()-1;)
	{
		str_tmp.erase(str_tmp.find(" "),1);
	}

	// �ַ���ͷ+ - ����
	if(str_tmp.find("-") == 0)
	{
		bnegativeNum = true;
		str_tmp.erase(0,1);
	}
	else if (str_tmp.find("+") == 0)
	{
		str_tmp.erase(0,1);
	}

	// ���ַ���
	if(str_tmp.length() == 0)
		return 0;

	// У���ת���ַ����Ƿ��зǷ��ַ�
	for(int i=0;bad_chars[i] != '\0' ;i++)
	{
		int pos = str_tmp.find(bad_chars[i]);
		if(pos != std::string::npos && pos == 0)
		{
			return 0;
		}
		else if(pos != std::string::npos && pos > 0) // ����123a45 �� a֮���ַ�
		{
			str_tmp.erase(pos, str_tmp.length() - pos);
		}
	}

	// ȥ����ͷ��
	for (;str_tmp.find("0") == 0;)
	{
		str_tmp.erase(0,1);
	}

	// ���ַ���
	if(str_tmp.length() == 0)
		return 0;

	// ȥ������ո�
	for (;str_tmp.find(" ") == 0 || str_tmp.find(" ") == str_tmp.length()-1;)
	{
		str_tmp.erase(str_tmp.find(" "),1);
	}

	int str_size = str_tmp.length() - 1;

	int64_t iRes = 0; // iRes = str_tmp[0]*10000 + str_tmp[1]* 1000 ...
	for(int i=0;i < str_tmp.length(); i++)
	{
		int64_t temp = static_cast<int64_t>(pow(10.0,static_cast<double>(str_size)));
		if (iRes + (str_tmp.at(i) - 48) * temp < 0)
		{
			iRes = 9223372036854775807;
			break;
		}
		iRes += (str_tmp.at(i) - 48) * temp;
		str_size--;
	}
	
	if(!bnegativeNum && iRes >= 2147483648)
		//iRes--;
		return 2147483647;
	else if (bnegativeNum && iRes >= 2147483648)
	{
		return -2147483648;
	}
	if(bnegativeNum) iRes = -iRes;
	return iRes;
}

int test(std::string tmp)
{
	return atoi(tmp.c_str());
}

int main()
{
	//std::string aaa = "    010 ";
	//std::string aaa = "   +0 1c23";
	//std::string aaa = "    +0a32";
	//std::string aaa = "   +0 123";
 	//std::string aaa = "2147483648";
	//std::string aaa = "-2147483649";
	//std::string aaa = "-2147483648";
	//std::string aaa = "-2147483650";
	//std::string aaa = "      -11919730356x";
	//std::string aaa = "    +11191657170";
	//std::string aaa = "9223372036854775809";
	std::string aaa = "-9223372036854775809";
 	std::cout<<"myAtoi:"<<myAtoi(aaa)<<std::endl;
	return 0;
}