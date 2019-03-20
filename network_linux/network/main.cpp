// select 模型之 键盘输入
#include <pthread.h>
// header files
#include "select_module_keyboard.h"
#include "normal/net_normal_client.h"
#include "normal/net_normal_server.h"

// select
#include "select/net_select_client.h"
#include "select/net_select_server.h"

// poll
#include "poll/net_poll_client.h"
#include "poll/net_poll_server.h"

enum {
  e_network_normal=1, 
  e_network_select,
  e_network_poll,
  e_network_epoll
};

static void *threadFuncClient(void *arg) {
  int* p_network_type = static_cast<int*>(arg);

  switch (*p_network_type) {
  case e_network_normal:
  {
    test_net_noraml_server();
    break;
  }
  case e_network_select:
  {
    test_net_select_server();
    break;
  }
  case e_network_poll:
  {
    test_net_poll_server();
    break;
  }
  default:
    break;
  }
  
  return NULL;
}

static void *threadFuncSserver(void *arg) {
  int* p_network_type = static_cast<int*>(arg);

  switch (*p_network_type) {
  case e_network_normal:
  {
    test_net_normal_client();
    break;
  }
  case e_network_select:
  {
    test_select_client();
    break;
  }
  case e_network_poll:
  {
    test_net_poll_client();
    break;
  }
  default:
    break;
  }
  return NULL;
}

void main_test(int network_type) {
  pthread_t thread1, thread2;
  int ret;

  ret = pthread_create(&thread2, NULL, threadFuncSserver, &network_type);
  ret = pthread_create(&thread1, NULL, threadFuncClient, &network_type);

  ret = pthread_join(thread1, NULL);
  ret = pthread_join(thread2, NULL);
}

int main(int argc, char **argv) {
  main_test(e_network_poll);

  return 0;
}
