/*3Sum
  Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.
Note: The solution set must not contain duplicate triplets.
For example, given array S = [-1, 0, 1, 2, -1, -4],
A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <sstream>
using namespace std;

struct comparer
{
public:
  bool operator()(const std::string a, const std::string b)
  {
    if (a.size() < b.size())
      return true;
    if (a.size() == b.size() && a.compare(b) < 0)
      return true;
    return false;
  }
};

//a + b + c = 0?
//�ر���ԭʼ��ʽ
vector<vector<int> > threeSum1(vector<int>& nums) 
{
  vector<vector<int> > vec_ret;
  vector<int>::iterator it;
  std::unordered_multimap<int, int> mul_map_content;
  std::unordered_multimap<int, int>::iterator it_mul_map1,it_mul_map2, it_mul_find;
  int pos = 0;
  for (it = nums.begin(); it != nums.end(); ++it)
  {
    mul_map_content.insert(std::pair<int, int>(*it, pos++));
  }

  it_mul_map1 = mul_map_content.begin();
  int value_tmp = 0;
  vector<int> sub_vec;
  std::multiset<std::string, comparer> mul_set_compare;
  std::stringstream tmp;
  for (; it_mul_map1 != mul_map_content.end(); ++it_mul_map1)
  {
    it_mul_map2 = it_mul_map1;
    it_mul_map2++;
    for (; it_mul_map2 != mul_map_content.end(); ++it_mul_map2)
    {
      value_tmp = it_mul_map1->first + it_mul_map2->first;
      it_mul_find = mul_map_content.find(0 - value_tmp);
      if (it_mul_find != mul_map_content.end() 
        && it_mul_find->second != it_mul_map1->second
        && it_mul_find->second != it_mul_map2->second) {
          sub_vec.push_back(it_mul_map1->first);
          sub_vec.push_back(it_mul_map2->first);
          sub_vec.push_back(it_mul_find->first);
          std::sort(sub_vec.begin(), sub_vec.end());
          tmp<<sub_vec[0];
          tmp<<sub_vec[1];
          tmp<<sub_vec[2];
          if (mul_set_compare.find(tmp.str()) == mul_set_compare.end()) {
            mul_set_compare.insert(mul_set_compare.end(), tmp.str());
            vec_ret.push_back(sub_vec); //�������
          }
          tmp.str("");
          sub_vec.clear();
      }
    }
  }

  return vec_ret;
}

/*
�㷨��ţ�
  Լ���� С��0�Ķ���ȡ��������ֵ�ֱ�Ϊ a��b�� a<=b�����ڵ���0�Ķ���ȡ����ֵΪc;
        ���ݽṹ��multimap<abs(item), item>;
(1)�����Ȱ���������ֳɴ��ڵ���0��С��0���Ѳ��ֱ�����;
(2)�������С��0�Ķ��дӾ���ֵС��������ȡ������Ԫ��a��b������ڵ���0�Ķ���Ԫ�شӾ���ֵС����ȡ����c���жԱȣ�С�ڣ����ڣ����ڣ�;
(3)���������С�ڣ����Ҵ��ڵ���0�Ķ��и����ֵ���ٴν���(2)����;
(4)�����������ȣ����ҵ��㷨��Ҫ��һ����ϣ���¼����������b��c��ֵ���ٴ��ظ���2������;
(5)��������Ǵ��ڣ�������c��ֵ���ظ���2������;

(6)�������ڵ���0�Ķ��ѽ��Ա����֪�����������ߵ�ֵ���ظ���������;
2017-12-07 �Լ�д�Ĵ��뿴������ -.-!
*/
vector<vector<int> > threeSum(vector<int>& nums)
{
  vector<vector<int> > vv_ret;
  std::multimap<int, int> mul_less,mul_greater_or_equal;

  //��ִ��������Ϊ2����Ӫ��ʵ�� a+b=c����;
  for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
  {
    if (*it >= 0) {
      mul_greater_or_equal.insert(std::pair<int, int>(*it, *it));
    } else{
      mul_less.insert(std::pair<int, int>(-*it, *it));
    }
  }

  vector<int> vv_sub_ret;
  // 0 + 0 + 0 = 0 ��case
  if (mul_greater_or_equal.count(0) >= 3) {
    vv_sub_ret.push_back(0);
    vv_sub_ret.push_back(0);
    vv_sub_ret.push_back(0);
    vv_ret.push_back(vv_sub_ret);
    vv_sub_ret.clear();
  }

  std::multiset<std::string, comparer> mul_set_compare;
  // ���е�����ֻ����;
  std::multimap<int, int>::iterator it_left_a, it_left_b, it_right_c, it_right_init_item;
  std::stringstream tmp;
  int i = 2;
  while (i--)
  {
    it_left_a = mul_less.begin();
    it_right_init_item = mul_greater_or_equal.begin();    
    for (; it_left_a != mul_less.end() && it_right_init_item != mul_greater_or_equal.end(); ++it_left_a)
    {
      bool b_right_first_go_before = true;
      it_right_c = it_right_init_item;
      it_left_b = it_left_a;
      it_left_b++;

      for (;it_left_b != mul_less.end() && it_right_c != mul_greater_or_equal.end();)
      {
        int ab_total_value = it_left_a->first + it_left_b->first;

        if(ab_total_value < it_right_c->first) { // a + b < c�����b��ֵ
          b_right_first_go_before = false;
          it_left_b++;
        } else if(ab_total_value > it_right_c->first) {// a + b > c,���c��ֵ
          it_right_c++;
          // �ų�c�����в����ܵ�ֵ
          if(b_right_first_go_before) {it_right_init_item = it_right_c;}
        } else { // a + b = c
          //���غͲ������� a+b=c ���ֵ
          vv_sub_ret.push_back(it_left_a->second);
          vv_sub_ret.push_back(it_left_b->second);
          vv_sub_ret.push_back(it_right_c->second);
          tmp<<vv_sub_ret[0]<<vv_sub_ret[1]<<vv_sub_ret[2];
          if (mul_set_compare.find(tmp.str()) == mul_set_compare.end()) { //����
            mul_set_compare.insert(mul_set_compare.end(), tmp.str());
            vv_ret.push_back(vv_sub_ret); //�������
          }

          vv_sub_ret.clear();
          tmp.str("");
          b_right_first_go_before = false;
          it_left_b++;
          it_right_c++;
        }
      }
    }
    std::swap(mul_less, mul_greater_or_equal);// �����a+a' = c �л�Ϊ c + c' = a
  }

  return vv_ret;
}

void show_vv_items(vector<vector<int> >& vv)
{
  vector<vector<int> >::iterator it_vv = vv.begin();
  vector<int>::iterator it_v;
  std::stringstream out_print_str;

  for (;it_vv != vv.end();++it_vv)
  {
    it_v = (*it_vv).begin();
    out_print_str<<"data: [";
    for (;it_v != (*it_vv).end(); ++it_v)
    {
      out_print_str<<*it_v<<",";
    }
    std::string str = out_print_str.str();
    str.erase(str.end()-1);
    std::cout<<str<<"]"<<std::endl;
    out_print_str.str("");
  }
}

int main()
{
  //int a[] = {-1, 0, 1, 2, -1, -4};
  //int a[] = {-1,0,1,2,-1,-4};
  //int a[] = {-4,-3,-2,-2,-2,-1,0,1,2,3,5,9};
  //int a[] = {0,0,0};
  //int a[] = {0,0};
  //int a[] = {-1,0,1,0};
  int a[] = {-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
  vector<int> vec_input(a, a + sizeof(a)/sizeof(int));
  vector<vector<int> > vv;
  vv = threeSum(vec_input);
  show_vv_items(vv);

  vv.clear();
  std::cout<<"---------------------------------------"<<std::endl;
  vv = threeSum1(vec_input);
  show_vv_items(vv);

  return 0;
}