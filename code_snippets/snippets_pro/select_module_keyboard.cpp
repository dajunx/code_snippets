//select ģ��֮ ��������
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
  char buf[10]="";
  fd_set rdfds;
  struct timeval tv; 
  int ret;
  FD_ZERO(&rdfds);
  FD_SET(0,&rdfds); //�ļ�������0��ʾstdin��������
  tv.tv_sec = 3;
  tv.tv_usec = 500;
  ret = select(1,&rdfds,NULL,NULL,&tv);
  if(ret<0)
    printf("\n ret:%d selcet", ret);
  else if(ret == 0)
    printf("\n ret:%d timeout", ret);
  else
    printf("\n ret = %d",ret);

  if(FD_ISSET(0,&rdfds))//��������룬��stdin�л�ȡ�����ַ�
  {
    printf("\n reading\n");
    fread(buf,9,1,stdin);
  }   
  write(1,buf,strlen(buf));
  printf("\n %d \n",strlen(buf));
  return 0;
}
