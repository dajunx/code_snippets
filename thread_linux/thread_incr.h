
/**
 * 测试 多线程竞争情况下，数据一致性不能保证
 */

static volatile int glob = 0; /* "volatile" prevents compiler optimizations
                                 of arithmetic operations on 'glob' */
static void *                 /* Loop 'arg' times incrementing 'glob' */
threadFunc_incr(void *arg) {
  int loops = *((int *)arg);
  int loc, j;

  for (j = 0; j < loops; j++) {
    loc = glob;
    loc++;
    glob = loc;
  }

  return NULL;
}

int test_thread_increase(int input_loops = 0) {
  pthread_t t1, t2;
  int loops, s;

  loops = input_loops ? input_loops : 10000000;

  s = pthread_create(&t1, NULL, threadFunc_incr, &loops);
  if (s != 0) {
    printf("pthread_create 1 err,line:%d", __LINE__);
  }

  s = pthread_create(&t2, NULL, threadFunc_incr, &loops);
  if (s != 0) {
    printf("pthread_create 2 err,line:%d", __LINE__);
  }

  s = pthread_join(t1, NULL);
  if (s != 0) {
    printf("pthread_join 1 err,line:%d", __LINE__);
  }

  s = pthread_join(t2, NULL);
  if (s != 0) {
    printf("pthread_join 2 err,line:%d", __LINE__);
  }

  printf("glob = %d\n", glob);
  
  return 0;
}
