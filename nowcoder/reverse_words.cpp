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
    std::string target_str, str_tmp;
    while(std::cin >> str_tmp)
    {
        target_str.insert(0, " ");
        target_str.insert(0, str_tmp);
    }
    target_str.pop_back();
    std::cout<<target_str<<std::endl;
    
    return 0;
}