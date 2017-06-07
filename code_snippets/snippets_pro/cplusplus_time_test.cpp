//c++ time ��� ��������

#include <iostream>
#include <ctime> //���� #include <time.h>
#include <Windows.h> //Sleep()
#include <string>

int main()
{
  //ϵͳ�ĵ�ǰ����ʱ�䣬�� 1970��1��1����������������(ʱ���)�����ϵͳû��ʱ�䣬�򷵻� .1��
  //time_t time(time_t *time);
  time_t tt, tt1;
  tt = time(NULL);
  tt1 = time(NULL);


  //�ú�������һ��ָ���ʾ����ʱ��� tm �ṹ��ָ�롣
  //struct tm *localtime(const time_t *time);
  struct tm* p_tm1;
  p_tm1 = localtime(&tt);

  //�ú�������һ��ָ�� time ��ָ�룬time Ϊ tm �ṹ����Э������ʱ��UTC��Ҳ����Ϊ�������α�׼ʱ�䣨GMT����ʾ��
  //struct tm *gmtime(const time_t *time);
  memset(p_tm1, 0, sizeof(struct tm));
  p_tm1 = gmtime(&tt);


  //�÷���һ����ʾ����ʱ����ַ���ָ�룬�ַ�����ʽ day month year hours:minutes:seconds year\n\0��
  //char *ctime(const time_t *time);
  char* time_sz = (char*)malloc(sizeof(char)*31);
  time_sz = ctime(&tt);

  //�ú�������һ��ָ���ַ�����ָ�룬�ַ��������� time ��ָ��ṹ�д洢����Ϣ��
  //  ������ʽΪ��day month date hours:minutes:seconds year\n\0��
  //char * asctime ( const struct tm * time );
  memset(time_sz, 0, sizeof(char)*31);
  time_sz = asctime(p_tm1);


  //�ú�����������ʱ�䣬�൱�� time ��ָ��ṹ�д洢��ʱ��
  //time_t mktime(struct tm *time);
  memset(&tt, 0, sizeof(time_t));
  tt = mktime(p_tm1);


  //�ú������س���ִ����һ��Ϊ����Ŀ�ͷ����������ʱ����ʹ�õ�ʱ�䡣���ʱ�䲻���ã��򷵻� .1
  //clock_t clock(void);
  clock_t cbe = clock();
  Sleep(3);
  clock_t ced = clock();
  int clock_leg = ced - cbe;


  //�ú������� time1 �� time2 ֮������������
  //double difftime ( time_t time2, time_t time1 );
  double time_leng = difftime(tt1, tt);


  //�ú��������ڸ�ʽ�����ں�ʱ��Ϊָ���ĸ�ʽ��
  //size_t strftime();
  char* strptr = (char*)malloc(sizeof(char)*32);
  size_t st = strftime(strptr, sizeof(char)*31, "%A", p_tm1);

  int i = 0;
  return 0;
}

/*
asctime���� ����(struct tm)ת�����ַ���
ctime���� ����ת�����ַ���
gettimeofday�����ݸ�������1970��1��1��������������õ�ʱ�������
gmtime�����ݸ�������1970��1��1�������������ȡ��ʱ�������
localtime�����ݸ�������1970��1��1�������������ȡ�õ��ص�ʱ����ʱ�������
mktime����ʱ��ṹ����ת���ɾ���������
settimeofday��������ϵͳʱ�䣬ֻ�У�����û�������
*/