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
#include <map>

int main(int argc, char* argv[])
{
    std::string str_src, str_tmp;
    while(std::cin >> str_tmp)
    {
        str_src.append(str_tmp);
    }
    
    char target_char;
    std::map<char, int> map_char_counts;
    std::map<char, int>::iterator it_map;
    std::pair<std::map<char, int>::iterator, bool> ret;
    
    std::string::iterator it_char = str_src.begin();
    for(; it_char != str_src.end(); it_char++)
    {
        if (!((*it_char >= 65 && *it_char <= 90)
              || (*it_char >= 97 && *it_char <= 122)))
        {
          continue;
        }
        
        ret = map_char_counts.insert(std::pair<char, int>(*it_char, 1));
        if(false == ret.second) {
            ret.first->second++;
        } else {
            continue;
        }
        
        if(ret.first->second >= 3) {
            target_char = ret.first->first;
            break;
        }
    }
    
    std::cout<<target_char<<std::endl;
    return 0;
}