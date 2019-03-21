#include <unistd.h>
#include <arpa/inet.h>  /* inet(3) functions */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <sys/socket.h> /* basic socket definitions */
#include <sys/types.h>  /* basic system data types */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024
// typedef struct sockaddr  SA;
void handle_net_normal_server(int connfd);

bool test_net_noraml_server() {
  int listenfd, connfd;
  int serverPort = 6888;
  int listenq = 1024;
  pid_t child_pid;
  char buf[MAXLINE];
  socklen_t socklen;

  struct sockaddr_in cliaddr, servaddr;
  socklen = sizeof(cliaddr);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(serverPort);

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0) {
    perror("socket error");
    return -1;
  }

  // 处理 address already in use. 错误
  int enable = 1;
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) <
      0) {
    perror("setsockopt(SO_REUSEADDR) failed");
    return -1;
  }

  if (bind(listenfd, (struct sockaddr *)&servaddr, socklen) < 0) {
    perror("bind error");
    return -1;
  }
  if (listen(listenfd, listenq) < 0) {
    perror("listen error");
    return -1;
  }
  printf("echo server startup,listen on port:%d\n", serverPort);
  for (;;) {
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &socklen);
    if (connfd < 0) {
      perror("accept error");
      continue;
    }

    printf("accept form %s:%d\n", inet_ntoa(cliaddr.sin_addr),
           cliaddr.sin_port);

    child_pid = fork();
    if (child_pid == 0) { //child process
      //close(listenfd); // close listening socket ??? 为啥要关闭掉
      handle_net_normal_server(connfd);
      exit(0);
    } else if (child_pid > 0) {
      // parent process
      //close(connfd); // closes connected socket ??? 为啥要关闭掉
    } else {
      perror("fork error");
    }
  }

  return true;
}

void handle_net_normal_server(int connfd) {
  size_t n;
  char buf[MAXLINE];

  for (;;) {
    n = read(connfd, buf, MAXLINE);
    if (n < 0) {
      if (errno != EINTR) {
        perror("read error");
        break;
      }
    }
    if (n == 0) {
      // connfd is closed by client
      close(connfd);
      printf("client exit\n");
      break;
    }
    write(connfd, buf, n); // write maybe fail,here don't process failed error
  }
}