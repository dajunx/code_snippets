
/**
 *  测试如何正常调度生产者和消费者
 */

static pthread_mutex_t mtx_no_condvar = PTHREAD_MUTEX_INITIALIZER;
static int avail = 0;

static void *threadFunc_no_condvar(void *arg) {
  int cnt = *(int*)arg;
  int s, j;

  for (j = 0; j < cnt; j++) {
    sleep(1);

    s = pthread_mutex_lock(&mtx_no_condvar);
    if (s != 0) {
      printf("pthread_mutex_lock falied, line number:%d.\n", __LINE__);
    }

    // 生产者，生产数据
    avail++;

    s = pthread_mutex_unlock(&mtx_no_condvar);
    if (s != 0) {
      printf("pthread_mutex_unlock falied, line number:%d.\n", __LINE__);
    }
  }

  return NULL;
}

int test_prod_no_condvar() {
  pthread_t tid;
  int s, j;
  int totRequired = 0;  // 生产者总共产生的数据量
  int numConsumed = 0; // 已消费的数据量
  int done = 0;
  time_t t;

  t = time(NULL);

  // 创建5个线程，用来生产数据
  int every_thread_unit = 1;
  for (j = 0; j < 5;j++) {
    totRequired += every_thread_unit;
    s = pthread_create(&tid, NULL, threadFunc_no_condvar, &every_thread_unit);  // 1表示 每个线程只生产一份数据
    if (s != 0) {
      printf("pthread_create falied, line number:%d.\n", __LINE__);
    }
  }

  // 使用主线程消费数据
  do {
    s = pthread_mutex_lock(&mtx_no_condvar);
    if (s != 0) {
      printf("pthread_mutex_lock failed, line number:%d\n", __LINE__);
    }

    // 主线程消费所有的产品
    while (avail > 0) {

      /* 对数据做点其他事情 */

      numConsumed++;
      avail--; // 消费掉一份数据
      printf("T=%ld: numConsumed=%d\n", (long)(time(NULL) - t), numConsumed);

      done = numConsumed >= totRequired ? 1:0;
    }

    s = pthread_mutex_unlock(&mtx_no_condvar);
    if (s != 0) {
      printf("pthread_mutex_unlock failed, line number:%d\n", __LINE__);
    }

  } while (!done);

  return 0;
}
