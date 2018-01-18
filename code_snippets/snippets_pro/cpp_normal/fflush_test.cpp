/* c-sytle io test
  getInputDataFromBuf:
  c���io���ԣ������� ����ˢ�»���������
  1.��û�� fflush(stdin)���������
    ���� 123abc�س�
    ��ʾ a = 123, c = a
  2.���� fflush(stdin)���������
    ���� 123abc�س�
        xyz�س�
    ��� a = 123, c = x

  ConnBufWithStream
  setbuf(stdout, outbuf) �ѻ�������������.
  �� fflush���Ⱥ�Ż�����Ļ��ӡ������ "This is a test of buffered output." �ַ�

  ������ӣ�
  1��http://c.biancheng.net/cpp/html/2506.html
  2��http://c.biancheng.net/cpp/html/265.html
*/
#include <stdio.h>
#include <stdlib.h>
char outbuf[BUFSIZ]; 

void getInputDataFromBuf()
{
  int a;
  char c;

  scanf("%d", &a);
  fflush(stdin); // ˢ�»�����
  c = getchar();
  printf("a = %d, c = %c \n", a, c);
}

void ConnBufWithStream()
{
  setbuf(stdout, outbuf);  // �ѻ�������������
  puts("This is a test of buffered output.\n");
  puts(outbuf);
  fflush(stdout);  // ˢ��
  puts(outbuf);  // ���
}

int main(){
  getInputDataFromBuf();
  ConnBufWithStream();
  return 0;
}