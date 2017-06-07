//c++ ��ģ��
/*
ģ�屻ʵ����2�Σ�1����ʵ����ǰ�ȼ��ģ����뱾���﷨�Ƿ���ȷ��2������ʵ�����ڼ䣬���ģ����룬�鿴�Ƿ����еĵ��ö���Ч��
������ģ�壬��Ա����ֻ���ڱ�ʹ�õ�ʱ��Żᱻʵ�������Ƚ�Լ�˿ռ��ʱ�䣬���ܱ�֤���ڡ�δ���ṩ���г�Ա���������в����ġ����͵İ�ȫ
*/
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class stack
{
private:
  std::vector<T> elems;

public:
  void push(T const&);
  T pop();
  T top() const;
  bool empty()
  {
    return elems.empty();
  }
};

template <typename T>
void stack<T>::push(T const& add_elems)
{
  elems.push_back(add_elems);
}

template <typename T>
T stack<T>::pop()
{
  if (elems.empty()) {
    return;
  }

  T tmp = elems.back();
  elems.pop_back();
  return tmp;
}

template <typename T>
T stack<T>::top() const
{
  if (elems.empty()) {
    return;
  }

  return elems.back();
}

int main()
{
  stack<int> sta_int;
  stack<std::string> str_string;

  sta_int.push(1);
  str_string.push("lin");
  return 0;
}