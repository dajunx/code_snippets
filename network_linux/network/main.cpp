// select 模型之 键盘输入
#include <pthread.h>
// header files
#include "select_module_keyboard.h"
#include "normal/net_normal_client.h"
#include "normal/net_normal_server.h"

static void *threadFuncClient(void *arg) {
  test_net_noraml_server();
  return NULL;
}

static void *threadFuncSserver(void *arg) {
  test_net_normal_client();
  return NULL;
}

void main_test(int argc, char **argv) {
  pthread_t thread1, thread2;
  int ret;

  ret = pthread_create(&thread2, NULL, threadFuncSserver, NULL);
  ret = pthread_create(&thread1, NULL, threadFuncClient, NULL);

  ret = pthread_join(thread1, NULL);
  ret = pthread_join(thread2, NULL);
}

int main(int argc, char **argv) {
  main_test(argc, argv);

  return 0;
}
