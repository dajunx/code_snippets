#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /*�ļ�����*/
#include <sys/select.h>
#include <sys/time.h> /*ʱ�䷽��ĺ���*/
#include <errno.h> /*�йش�����ĺ�*/
#include<sys/poll.h> //poll()
#include<fcntl.h>
#include<string.h> //memset()

int main(void)
{
  int fd,key_value,ret;
  struct pollfd event; //����һ��struct pollfd�ṹ�����������ļ���������Ҫ�ȴ��������¼�
  /* fd=open("/dev/key",O_RDWR); */
  fd=open("/opt/peterlin/test/net_test/poll/kk",O_RDWR);
  if(fd<0){
    perror("open /dev/key error!\n");
    exit(1);
  }
  printf("open /dev/key sucessfully!\n");
  while(1){ //poll������struct pollfd�ṹ����������ݱ�ȫ�����㣬��Ҫ�ٴ�����
    memset(&event,0,sizeof(event)); //memst�����Զ������������Ϊͬһֵ
    event.fd=fd; //��Ŵ򿪵��ļ�������
    /* event.events=POLLIN; //���Ҫ�ȴ��������¼� */
    event.events=POLLIN; //���Ҫ�ȴ��������¼�
    ret=poll((struct pollfd *)&event,1,5000); //���event��һ�����󣬵ȴ�5000�����ʱ,-1Ϊ���޵ȴ�

    //�ж�poll�ķ���ֵ�������ǳ���0���趨��ʱ�䳬ʱ��������ʾ�ȴ���ʱ�䷢��
    if(ret<0){
      printf("poll error!\n");
      exit(1);
    }
    if(ret==0){
      printf("Time out!\n");
      continue;
    }
    if(event.revents&POLLERR){ //revents�����ں˼�¼��ʵ�ʷ������¼���events�ǽ��̵ȴ����¼�
      printf("Device error!\n");
      exit(1);
    }
    if(event.revents&POLLIN){
      char buffer[80];
      /* ssize_t i = read(fd,&key_value,sizeof(key_value)); */
      read(fd,&buffer,sizeof(buffer));
      printf("Key value is '%s'\n",buffer);
    }
  }
  close(fd);
  return 0;
}