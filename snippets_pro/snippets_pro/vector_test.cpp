//vector ����
/*
(1) empty container constructor (default constructor)
Constructs an empty container, with no elements.
(2) fill constructor
Constructs a container with n elements. Each element is a copy of val.
(3) range constructor
Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
(4) copy constructor
Constructs a container with a copy of each of the elements in x, in the same order.
*/
#include <iostream>
#include <vector>

class test1
{
public:
  test1() {}
  ~test1() {}
  test1 (const test1& a) {}
};

int main()
{
  // Construct
  int a[10] = {0,1,2,3,4,5,6,7,8,9};
  std::vector<int> vec_int;
  std::vector<int> vec_int1(&a[0], &a[9]+1); //������&ȡ�����鿪ʼ������ַ  [first,last)
  std::vector<int> vec_int4(a, a + sizeof(a)/sizeof(int));
  std::vector<int> vec_int2(4, 5);
  std::vector<int> vec_int3(vec_int2);  
  //vec_int2.clear(); // copy constructor ��Դ��������޹�

  // operator= ���·������ݣ�����ö�Ӧ���졢��������������
  test1 b1, b2;
  std::vector<test1> vec_test1, vec_test2;
  vec_test1.push_back(b1);
  vec_test2.push_back(b1);
  vec_test2.push_back(b2);
  vec_test1 = vec_test2;

  // size max_size:3FFFFFFF capacity��������Ŀ
  std::vector<int> vec_int01;
  int size = 0, max_size = 0, capacity = 0;
  for (int i = 0;i < 10; i++)
  {
    vec_int01.push_back(i);
    size = vec_int01.size();
    capacity = vec_int01.capacity();
    max_size = vec_int01.max_size();
  }

  // operator[] �� at ���� at �ɲ����쳣��[]����
  try
  {
    vec_int01.at(10) = 8;
    vec_int01[10] = 9;
  }
  catch(std::underflow_error& e)
  {
    std::cout<<"error reasion:" << e.what();
  }
  catch(std::out_of_range& e1)
  {
    std::cout<<"error reasion:" << e1.what();
  }

  // swap �����ٺ�������֯����
  std::vector<test1> vec_obj1, vec_obj2;
  vec_obj1.push_back(b1);
  vec_obj2.push_back(b2);
  vec_obj1.swap(vec_obj2);

  // front ������Ϊ�� ��Ϊδ����
  std::vector<int> vec_int11;
  //   std::vector<int>::reference it = vec_int11.front();
  //   it = 9;
  return 0;
}