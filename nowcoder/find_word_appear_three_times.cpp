/*
	��Ŀ����: ����һ��Ӣ���ַ���,��дһ�δ����ҳ�����ַ��������ȳ������ε��Ǹ�Ӣ���ַ���
	��������: ��������һ���ַ�����������ĸ,���ֵȡ�
	�������: ������ȳ������ε��Ǹ�Ӣ���ַ�.

	ʾ��1:
		���룺Have you ever gone shopping and
		�����e
*/
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string str_src, str_tmp;
    while(std::cin >> str_tmp)
    {
        str_src.append(str_tmp);
    }
    
    int char_array[123] = {0};    
    std::string::iterator it_char = str_src.begin();
    for(; it_char != str_src.end(); it_char++)
    {
        if (!((*it_char >= 65 && *it_char <= 90)
              || (*it_char >= 97 && *it_char <= 122)))
        {
          continue;
        }
        
        char_array[*it_char]++;
        
        if(char_array[*it_char] >= 3) {
            std::cout<<*it_char<<std::endl;
            break;
        }
    }
    
    return 0;
}