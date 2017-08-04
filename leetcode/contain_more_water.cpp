#include <iostream>
#include <vector>
#include <map>
//11. Container With Most Water
/*
**Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the 
**two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains 
**the most water.
**Note: You may not slant the container and n is at least 2.
*/

/*
** Ч��ƫ�ͣ����Ż�
** ˼·���ȴ��߶���͵Ŀ�ʼa����������Զ���߶�x����¼a��x���γɵ��ݻ���ȥ��a�߶Σ��Դ����ƣ�������height �����ҵ�����ݻ�
*/
int maxArea(std::vector<int>& height) {
  if (height.size() < 2) {
    return 0;
  }

  std::multimap<int, int> map_arpe, map_height;
  std::multimap<int, int>::iterator it_map;
  std::vector<int>::iterator it = height.begin();
  int height_size = height.size();
  int res_array[3] = {0};

  for (int i = 1; it != height.end(); ++it, ++i)
  {
    map_arpe.insert(std::pair<int, int>(*it, i));
    map_height.insert(std::pair<int, int>(i, *it));
  }

  for (it_map = map_arpe.begin(); it_map != map_arpe.end(); ++it_map)
  {
    int left_length = it_map->second - (map_height.begin())->first;
    int right_length = (map_height.rbegin())->first - it_map->second;
    int area_tmp = 0;
    left_length > right_length
      ? (area_tmp = left_length * it_map->first)
      : (area_tmp = right_length * it_map->first);

    if (area_tmp > res_array[2]) {
      res_array[0] = it_map->second;
      res_array[1] = left_length > right_length 
        ? (map_height.begin())->first
        : (map_height.rbegin())->first;
      res_array[2] = area_tmp;
    }
    map_height.erase(it_map->second);
  }

  return res_array[2];
}

//�����Լ�����Զ,˫��forѭ����Ч��̫��
int maxArea1(std::vector<int>& height) {
  if (height.size() < 2) {
    return 0;
  }

  int height_size = height.size();
  int res_array[3] = {0};
  for (int i=0; i < height_size; i++)
  {
    for (int j=0; j < height_size; j++)
    {
      if (height.at(i) <= height.at(j)
          && abs(j-i) * height.at(i) >= res_array[2]) {
        res_array[0] = i;
        res_array[1] = j;
        res_array[2] = abs(j-i) * height.at(i);
      }
    }
  }

  return res_array[2];
}

int main()
{
  //int a[] = {3, 7, 5, 4};
  int a[] = {1,3,2,5,25,24,5};
  std::vector<int> height(a, a + sizeof(a)/sizeof(int));
//   maxArea(height);
//   maxArea1(height);

  int i = 0;
  return 0;
}