#include <unistd.h>
#include <arpa/inet.h>  /* inet(3) functions */
#include <netdb.h>      /*gethostbyname function */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <sys/socket.h> /* basic socket definitions */
#include <sys/types.h>  /* basic system data types */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

void handle_net_poll_client(int connfd);

bool test_net_poll_client() {
  char *servInetAddr = "127.0.0.1";
  int servPort = 88960;
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

  printf("welcome to echoclient\n");
  handle_net_poll_client(connfd); /* do it all */

  close(connfd);
  printf("exit\n");
  exit(0);

  return 0;
}

void handle_net_poll_client(int sockfd) {
  char sendline[MAXLINE], recvline[MAXLINE];
  int n;
  do {
    if (fgets(sendline, MAXLINE, stdin) == NULL) {
      break; // read eof
    }
    /*
    //也可以不用标准库的缓冲流,直接使用系统函数无缓存操作
    if (read(STDIN_FILENO, sendline, MAXLINE) == 0) {
        break;//read eof
    }
    */

    n = write(sockfd, sendline, strlen(sendline));
    n = read(sockfd, recvline, MAXLINE);
    if (n == 0) {
      printf("echo client: server terminated prematurely\n");
      break;
    }
    write(STDOUT_FILENO, recvline, n);
    //如果用标准库的缓存流输出有时会出现问题
    // fputs(recvline, stdout);
  } while (true);
}
