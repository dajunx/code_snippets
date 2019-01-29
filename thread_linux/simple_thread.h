
/**
 * 最简单的Linux 多线程程序例子
 */
static void *threadFunc_simple(void *arg) {
  char *s = (char *)arg;

  printf("child thread, input value:%s\n", s);
  //sleep(3);

  return (void *)strlen(s);
}

int test_simple_thread() {
  pthread_t t1;
  void *res;
  int s;

  char hello_string[20];
  strcpy(hello_string, "Hello world\n");

  s = pthread_create(&t1, NULL, threadFunc_simple, hello_string);
  if (s != 0) {
    printf("pthread_create err, line:%d", __LINE__);
  }

  printf("Message from main()\n");
  s = pthread_join(t1, &res);
  if (s != 0) {
    printf("pthread_join err, line:%d", __LINE__);
  }

  printf("Thread returned %ld\n", (long)res);

  return 0;
}

