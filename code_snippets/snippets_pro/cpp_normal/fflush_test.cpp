/* c-sytle io test
  c���io���ԣ������� ����ˢ�»���������
  1.��û�� fflush(stdin)���������
    ���� 123abc�س�
    ��ʾ a = 123, c = a
  2.���� fflush(stdin)���������
    ���� 123abc�س�
        xyz�س�
    ��� a = 123, c = x

*/
#include <stdio.h>
#include <stdlib.h>
int main(){
  int a;
  char c;

  scanf("%d", &a);
  fflush(stdin); // ˢ�»�����
  c = getchar();
  printf("a = %d, c = %c \n", a, c);
  return 0;
}