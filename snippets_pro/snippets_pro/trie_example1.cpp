//Trie�� ʵ�֣��ú����������нڵ�
// url:http://www.cnblogs.com/dlutxm/archive/2011/10/26/2225660.html

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define Max 26
using namespace std;

typedef struct node {
  struct node* next[Max];
  int num;
} Node;
//����һ���½ڵ�
Node* createNew()
{
  Node* p = new Node;
  for (int i = 0; i < Max; i++) {
    p->next[i] = NULL;
  }
  p->num = 0;
  return p;
}
//����һ���ַ���
void Insert_str(const char str[], Node* head)
{
  int len = strlen(str);
  Node* t, *p = head;
  for (int i = 0; i < len; i++) {
    int c = str[i] - 'a';
    if (p->next[c] == NULL) {
      t = createNew();
      p->next[c] = t;
      p->num++;
      //cout<<p->num<<endl;
      p = p->next[c];
    } else {
      p = p->next[c];
    }
  }
}
int Search_str(char str[], Node* head)
{
  Node* p = head;
  int len = strlen(str);
  int count = 0;
  for (int i = 0; i < len; i++) {
    int c = str[i] - 'a';
    if (p->next[c] == NULL) {
      cout << "�������ַ���" << endl;
      count = 0;
      return -1;
    } else {
      p = p->next[c];
      count += p->num;
    }
  }
  return count;
}

//��������Ԫ��
std::vector<char> vec_char;
void print_all_node(Node* head)
{
  Node* p = head;
  for (int i = 0; i < Max; ++i) {
    if (head->next[i]) {
      print_all_node(head->next[i]);
      vec_char.push_back(static_cast<char>(i + 'a'));
    }
  }
}

int main()
{
  Node* head = createNew();

  std::ifstream filein("word.txt");
  if (!filein.is_open()) {
    return -1;
  }

  for (std::string line; std::getline(filein, line);) {
    Insert_str(line.c_str(), head);
  }

  int c = Search_str("ab", head);
  cout << c << endl;

  print_all_node(head);

  return 0;
}