//Remove Duplicates from Sorted Array
/*
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.
*/
#include <iostream>
#include <vector>

int removeDuplicates(std::vector<int>& nums) 
{
  int* p_previous_data = NULL;
  bool begin_filled = false;
  std::vector<int>::iterator it_begin_filled_pos = nums.end();
  std::vector<int>::iterator it_checking_pos = nums.begin();

  while (it_checking_pos != nums.end())
  {
    if (NULL == p_previous_data || *it_checking_pos != *p_previous_data) {
      p_previous_data = new int;
      *p_previous_data = *it_checking_pos++;
      if (begin_filled){
        *it_begin_filled_pos++ = *p_previous_data;
      }
    } else {
      if (begin_filled) {
        // �ظ���¼��pass�����ᱻ������¼����
        it_checking_pos++;
      } else {
        // ��ʼ�����ظ���¼��
        it_begin_filled_pos = it_checking_pos++;
        begin_filled = true;
      }
    }
  }

  //��β��������it_left��ʼ��������
  nums.erase(it_begin_filled_pos, nums.end());

  return nums.size();
}

int main(int argc, char** argv)
{
  //1; 1,1; 0,0,0,0,0 //���������
  int a[] = {0,0,0,0,0};
  std::vector<int> vec_int(a, a + sizeof(a)/sizeof(int));
  int newVectorSize = removeDuplicates(vec_int);

  int i = 0;
  return 0;  
}