
/**
 * 实用锁来控制多个线程访问共享资源
 */

static volatile int glob_mutex = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/* Loop 'arg' times incrementing 'glob' */
static void * threadFunc_use_lock(void *arg) {
  int loops = *((int *)arg);
  int loc, j, s;

  for (j = 0; j < loops; j++) {
    s = pthread_mutex_lock(&mtx);
    if (s != 0) {
      printf("pthread_mutex_lock,line:%d", __LINE__);
    }

    loc = glob_mutex;
    loc++;
    glob_mutex = loc;

    s = pthread_mutex_unlock(&mtx);
    if (s != 0) {
      printf("pthread_mutex_unlock,line:%d", __LINE__);
    }
  }

  return NULL;
}

int test_thread_increase_with_lock(int input_loops = 0) {
  pthread_t t1, t2;
  int loops, s;

  loops = input_loops? input_loops : 10000000;

  s = pthread_create(&t1, NULL, threadFunc_use_lock, &loops);
  if (s != 0) {
    printf("pthread_create 1 err,line:%d", __LINE__);
  }

  s = pthread_create(&t2, NULL, threadFunc_use_lock, &loops);
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

  printf("glob_mutex = %d\n", glob_mutex);
  
  return 0;
}

