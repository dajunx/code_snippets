#include <unistd.h>
#include <arpa/inet.h>  /* inet(3) functions */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <sys/socket.h> /* basic socket definitions */
#include <sys/types.h>  /* basic system data types */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>
#include <poll.h> /* poll function */

#define MAXLINE 10240

#ifndef OPEN_MAX
#define OPEN_MAX 40960
#endif

void handle_net_poll_server(struct pollfd *p_clients, int maxClient,
                            int readyClient);

bool test_net_poll_server() {
  int servPort = 88960;
  int listenq = 1024;
  int listenfd, connfd, maxfd;
  socklen_t socklen = sizeof(struct sockaddr_in);
  struct sockaddr_in cliaddr, servaddr;
  char buf[MAXLINE];
  int nready;

  // 1.定义pollfd 结构体
  struct pollfd clients[OPEN_MAX];
  memset(clients, -1, sizeof(pollfd) * OPEN_MAX);

  bzero(&servaddr, socklen);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(servPort);

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0) {
    perror("socket error");
  }

  // 处理 address already in use. 错误
  int opt = 1;
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("setsockopt error");
  }

  if (bind(listenfd, (struct sockaddr *)&servaddr, socklen) == -1) {
    perror("bind error");
    exit(-1);
  }
  if (listen(listenfd, listenq) < 0) {
    perror("listen error");
  }

  // 2.初始化pollfd 结构，定义需要监听的动作
  clients[0].fd = listenfd;
  clients[0].events = POLLIN;
  maxfd = listenfd + 1;

  printf("poll echoserver startup, listen on port:%d\n", servPort);
  printf("max connection is %d\n", OPEN_MAX);

  for (;;) {
    nready = poll(clients, maxfd /* + 1*/, -1); // 3.开始监听
    if (nready == -1) {
      perror("poll error");
      continue;
    }

    if (clients[0].revents & POLLIN) { // 4.查看监听返回的是否是指定的事件
      connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &socklen);
      sprintf(buf, "accept form %s:%d\n", inet_ntoa(cliaddr.sin_addr),
              cliaddr.sin_port);
      printf(buf, "");

      int i = 0;
      for (; i < OPEN_MAX; i++) {
        if (clients[i].fd == -1) {
          clients[i].fd = connfd;
          clients[i].events = POLLIN;
          break;
        }
      }

      if (i == OPEN_MAX) {
        fprintf(stderr, "too many connection, more than %d\n", OPEN_MAX);
        close(connfd);
        continue;
      }

      if (i > maxfd)
        maxfd = i;

      /* --nready; */
    }

    handle_net_poll_server(clients, maxfd, nready);
  }

  return true;
}

void handle_net_poll_server(struct pollfd *p_clients, int maxClient, int nready) {
  int connfd;
  int i, nread;
  char buf[MAXLINE];

  if (nready == 0)
    return;

  for (i = 1; i < maxClient; i++) {
    connfd = p_clients[i].fd;
    if (connfd == -1)
      continue;

    if (p_clients[i].revents & (POLLIN | POLLERR)) {
      nread = read(connfd, buf, MAXLINE); //读取客户端socket流
      if (nread < 0) {
        perror("read error");
        close(connfd);
        p_clients[i].fd = -1;
        continue;
      }
      if (nread == 0) {
        printf("client close the connection");
        close(connfd);
        p_clients[i].fd = -1;
        continue;
      }

      write(connfd, buf, nread); //响应客户端
      if (--nready <= 0)         //没有连接需要处理，退出循环
        break;
    }
  }
}