#include <unistd.h>
#include <arpa/inet.h>    /* inet(3) functions */
#include <fcntl.h>        /* nonblocking */
#include <netinet/in.h>   /* sockaddr_in{} and other Internet defns */
#include <sys/epoll.h>    /* epoll function */
#include <sys/resource.h> /*setrlimit */
#include <sys/socket.h>   /* basic socket definitions */
#include <sys/types.h>    /* basic system data types */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXEPOLLSIZE 10000
#define MAXLINE 10240

int handle_net_epoll_server(int connfd);

bool test_net_epoll_server() {
  int servPort = 88960;
  int listenq = 1024;
  int listenfd, connfd, epoll_fd, current_fd_num = 1, acceptCount = 0;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t socklen = sizeof(struct sockaddr_in);
  struct epoll_event ev;
  struct epoll_event happen_events[MAXEPOLLSIZE];

  // 设置每个进程允许打开的最大文件数
  struct rlimit rt;
  rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
  if (setrlimit(RLIMIT_NOFILE, &rt) == -1) {
    perror("setrlimit error");
    return -1;
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(servPort);
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  if (listenfd == -1) {
    perror("can't create socket file");
    return -1;
  }

  // 处理 address already in use. 错误
  int opt = 1;
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("setsockopt error");
  }

  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) ==
      -1) {
    perror("bind error");
    return -1;
  }

  if (listen(listenfd, listenq) == -1) {
    perror("listen error");
    return -1;
  }

  // 1.创建 epoll 句柄，把监听 socket 加入到 epoll 集合里
  epoll_fd = epoll_create(MAXEPOLLSIZE);
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = listenfd;

  if (fcntl(listenfd, F_SETFL, fcntl(listenfd, F_GETFD, 0) | O_NONBLOCK) == -1) {
    perror("fcntl error");
  }
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listenfd, &ev) < 0) { // 2.事件注册
    fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
    return -1;
  }

  printf("epollserver startup,port %d, max connection is %d, backlog is %d\n",
         servPort, MAXEPOLLSIZE, listenq);

  /** 
   * 等待有事件发生：1.新连入的客户端； 2.已连入客户端请求的数据；
   */
  for (;;) {
    int happen_fd_num = -1; // 存放I/O上已准备好的文件描述符数目;
    happen_fd_num = epoll_wait(epoll_fd, happen_events, current_fd_num, -1); // 3.收集在epoll监控的事件中已经发生的事件

    if (happen_fd_num == -1) {
      perror("epoll_wait");
      continue;
    }

    /* 处理所有发生的事件 */
    for (int n = 0; n < happen_fd_num; ++n) {
      // 新客户端连入
      if (happen_events[n].data.fd == listenfd) {
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &socklen);

        if (connfd < 0) {
          perror("accept error");
          continue;
        }

        char buf[MAXLINE];
        sprintf(buf, "accept form %s:%d\n", inet_ntoa(cliaddr.sin_addr),
                cliaddr.sin_port);
        printf("acceptCount-> %d:%s", ++acceptCount, buf);

        if (current_fd_num >= MAXEPOLLSIZE) {
          fprintf(stderr, "too many connection, more than %d\n", MAXEPOLLSIZE);
          close(connfd);
          continue;
        }

        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = connfd;

        if (fcntl(connfd, F_SETFL, fcntl(connfd, F_GETFD, 0) | O_NONBLOCK) == -1) {
          perror("fcntl error");
        }
        // 2.把连入的客户端fd加入 epoll监听事件列表中，用来监听是否有数据到来;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connfd, &ev) < 0) {
          fprintf(stderr, "add socket '%d' to epoll failed: %s\n", connfd,
                  strerror(errno));
          return -1;
        }

        current_fd_num++;
        continue;
      } else { // 不是新客户端连入，就是已连入客户端数据传输
        // 处理客户端请求
        if (handle_net_epoll_server(happen_events[n].data.fd) < 0) {
          epoll_ctl(epoll_fd, EPOLL_CTL_DEL, happen_events[n].data.fd, &ev);
          current_fd_num--;
        }
      }

    }
  }

  close(listenfd);
  return true;
}

int handle_net_epoll_server(int connfd) {
  int nread;
  char buf[MAXLINE];
  nread = read(connfd, buf, MAXLINE); //读取客户端socket流

  if (nread == 0) {
    printf("client close the connection\n");
    close(connfd);
    return -1;
  }

  if (nread < 0) {
    perror("read error");
    close(connfd);
    return -1;
  }

  write(connfd, buf, nread); //响应客户端
  return 0;
}