#include <unistd.h>
#include <arpa/inet.h>  /* inet(3) functions */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <sys/select.h> /* select function*/
#include <sys/socket.h> /* basic socket definitions */
#include <sys/types.h>  /* basic system data types */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 10240
#define max(a, b) ((a) > (b) ? (a) : (b))
// typedef struct sockaddr  SA;

void handle_select_client(int sockfd);

bool test_select_client(/*int argc, char **argv*/) {
  char *servInetAddr = "127.0.0.1";
  int servPort = 6888;
  char buf[MAXLINE];
  int connfd;
  struct sockaddr_in servaddr;

  connfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(servPort);
  inet_pton(AF_INET, servInetAddr, &servaddr.sin_addr);

  int connect_server_ret = -1;
  do
  {
    sleep(1);
    connect_server_ret = connect(connfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("connect_server_ret: %d\n", connect_server_ret);
  } while (connect_server_ret < 0);


  printf("welcome to selectechoclient\n");
  handle_select_client(connfd); /* do it all */
  close(connfd);
  printf("exit\n");
  exit(0);

  return true;
}

void handle_select_client(int connfd) {
  FILE *fp = stdin;
  char sendline[MAXLINE], recvline[MAXLINE];
  fd_set all_fds;
  FD_ZERO(&all_fds);
  int maxfds = max(fileno(fp), connfd) + 1;
  int nread;

  for (;;) {
    FD_SET(fileno(fp), &all_fds);
    FD_SET(connfd, &all_fds);

    if (select(maxfds, &all_fds, NULL, NULL, NULL) == -1) {
      perror("select error");
      continue;
    }

    // 响应服务端传输数据
    if (FD_ISSET(connfd, &all_fds)) {
      //接收到服务器响应
      nread = read(connfd, recvline, MAXLINE);
      if (nread == 0) {
        printf("server close the connection\n");
        break;
      } else if (nread == -1) {
        perror("read error");
        break;
      } else {
        // server response
        write(STDOUT_FILENO, recvline, nread);
      }
    }

    // 收到键盘输入事件，发送输入数据到服务端
    if (FD_ISSET(fileno(fp), &all_fds)) {
      //标准输入可读
      if (fgets(sendline, MAXLINE, fp) == NULL) {
        // eof exit
        break;
      } else {
        write(connfd, sendline, strlen(sendline));
      }
    }
  }
}