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

void handle_net_select_server(int *clientSockFds, int maxFds, fd_set *pRset,
                              fd_set *pAllset, char *quit);

bool test_net_select_server(/*int argc, char **argv*/) {
  int servPort = 6888;
  int listenq = 1024;

  int listenfd, accept_fd;
  struct sockaddr_in cliaddr, servaddr;
  socklen_t socklen = sizeof(struct sockaddr_in);
  int nready, nread;
  char buf[MAXLINE];
  int accept_fds[FD_SETSIZE];    // 容纳有变化的客户端连接fd ???
  fd_set allset, changed_fd_set; // 1.定义 select模型的结构体;
  int maxfd;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0) {
    perror("socket error");
    return -1;
  }

  // 处理 address already in use. 错误
  int opt = 1;
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("setsockopt error");
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(servPort);

  if (bind(listenfd, (struct sockaddr *)&servaddr, socklen) == -1) {
    perror("bind error");
    exit(-1);
  }

  if (listen(listenfd, listenq) < 0) {
    perror("listen error");
    return -1;
  }

  /// TODO ?
  for (int i = 0; i < FD_SETSIZE; i++) {
    accept_fds[i] = -1;
  }

  // 2.初始化select模型数据, FD_ZERO + FD_SET 绑定要监听的fd
  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);
  maxfd = listenfd;

  printf("echo server use select startup, listen on port %d\n", servPort);
  printf("max connection: %d\n", FD_SETSIZE);

  char *quit = "quit";
  for (;;) {
    changed_fd_set = allset;

    // 3.监听，等待内核通知是否有事件发生
    nready = select(maxfd + 1, &changed_fd_set, NULL, NULL, NULL);
    if (nready < 0) {
      perror("select error");
      continue;
    }
    if (FD_ISSET(listenfd, &changed_fd_set)) { // 4.判断是否有等待的事件发生
      accept_fd = accept(listenfd, (struct sockaddr *)&cliaddr, &socklen);
      if (accept_fd < 0) {
        perror("accept error");
        continue;
      }

      sprintf(buf, "accept form %s:%d\n", inet_ntoa(cliaddr.sin_addr),
              cliaddr.sin_port);
      printf(buf, "");

      int i = 0;
      for (i = 0; i < FD_SETSIZE; i++) {
        if (accept_fds[i] == -1) {
          accept_fds[i] = accept_fd;
          break;
        }
      }
      if (i == FD_SETSIZE) {
        fprintf(stderr, "too many connection, more than %d\n", FD_SETSIZE);
        close(accept_fd);
        continue;
      }
      if (accept_fd > maxfd)
        maxfd = accept_fd;

      FD_SET(accept_fd, &allset);
      /* if (--nready <= 0) */
      /*     continue; */
    }

    handle_net_select_server(accept_fds, maxfd, &changed_fd_set, &allset, quit);
  }

  return true;
}

void handle_net_select_server(int *p_accept_fds, int maxFds,
                              fd_set *p_changed_fd_set, fd_set *p_allset,
                              char *quit) {
  int nread;
  int i;
  char buf[MAXLINE];
  for (i = 0; i < maxFds; i++) {
    if (p_accept_fds[i] == -1) {
      continue;
    }

    if (!FD_ISSET(p_accept_fds[i], p_changed_fd_set)) {
      continue;
    }

    nread = read(p_accept_fds[i], buf, MAXLINE); //读取客户端socket流
    if (nread < 0) {
      perror("read error");
      close(p_accept_fds[i]);
      FD_CLR(p_accept_fds[i], p_allset);
      p_accept_fds[i] = -1;
      continue;
    }
    if (nread == 0) { // kill 可以引发这个case
      printf("client close the connection\n");
      close(p_accept_fds[i]);
      FD_CLR(p_accept_fds[i], p_allset);
      p_accept_fds[i] = -1;
      continue;
    }

    // socket传递过来的数据，除了输入的本身，还额外包含回车和换行2个字符
    if (strncmp(buf, quit, 4) ==0) {
      printf("client close the connection 1\n");
      close(p_accept_fds[i]);
      FD_CLR(p_accept_fds[i], p_allset);
      p_accept_fds[i] = -1;
      continue;
    }
    write(p_accept_fds[i], buf, nread); //响应客户端  有可能失败，暂不处理
  }
}