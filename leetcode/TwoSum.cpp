// 1. Two Sum
/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
(���ٶ�λ����������ĳ����ֵ��ӵ���һ������ֵ������ֻ����һ������ ������Ԫ�ز����ظ�ʹ��)
Example:
Given nums = [2, 7, 11, 15], target = 9,
 Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void quick_sort(vector<int>& s, int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while(i < j && s[j] >= x) // ���������ҵ�һ��С��x����
				j--;  
			if(i < j) 
				s[i++] = s[j];

			while(i < j && s[i] < x) // ���������ҵ�һ�����ڵ���x����
				i++;  
			if(i < j) 
				s[j--] = s[i];
		}
		s[i] = x;
		quick_sort(s, l, i - 1); // �ݹ���� 
		quick_sort(s, i + 1, r);
	}
}

vector<int> twoSum(vector<int>& nums, int target)
{
	vector<int> return_vec;
	vector<int> temp = nums;
	quick_sort(temp,0,temp.size()-1);
	int nums_size = (int)nums.size();
	int i = 0,j = nums_size-1;
	for (;i != nums_size || j != nums_size;)
	{
		if(temp.at(i) + temp.at(j) == target)
		{
			i = temp.at(i);
			j = temp.at(j);
			break;
		}
		else if(temp.at(i) + temp.at(j) < target)
			i++;
		else
			j--;
	}
	int pos = 0;
	for(vector<int>::iterator it = nums.begin();it != nums.end(); ++ it,++pos)
	{
		if(i == *it || j == *it)
			return_vec.push_back(pos + 1);
		if ( 2 == return_vec.size()) break;
	}
	return return_vec;
}

int main()
{
	vector<int> vec_input, vec_ret;
	int target = 0;
	vec_ret = twoSum(vec_input, target);

	return 0;
}
