/*
	��Ŀ����: ����һ�����ӣ�ֻ������ĸ�Ϳո񣩣� �������еĵ���λ�÷�ת�������ÿո�ָ�, ����֮��ֻ��һ���ո�ǰ��û�пո� ���磺 ��1�� ��hello xiao mi��-> ��mi xiao hello��
	��������: ���������ж��飬ÿ��ռһ�У�����һ������(���ӳ���С��1000���ַ�)
	�������: ����ÿ������ʾ����Ҫ����������е��ʷ�ת���γɵľ���.

	ʾ��1:
		���룺hello xiao mi
		�����mi xiao hello
*/
#include <iostream>
#include <string>

int main()
{
    std::string str_src, str_tmp;
    while(std::cin >> str_tmp)
    {
        str_src.append(str_tmp + " ");
    }
    str_src.pop_back();
    
    std::string target_string;
    std::string::size_type space_pos;
    while ((space_pos = str_src.find_first_of(" ", 0)) != std::string::npos)
    {
        target_string.insert(0, str_src.substr(0, space_pos));
        target_string.insert(0, " ");
        str_src.erase(0, space_pos+1);
    }

    target_string.insert(0, str_src);
    std::cout<<target_string<<std::endl;
    
    return 0;
}