
/**
 *  测试如何正常调度生产者和消费者
 */

static pthread_mutex_t mtx_condvar = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_condvar = PTHREAD_COND_INITIALIZER;
static int avail_use_condvar = 0;

static void *threadFunc_condvar(void *arg) {
  int cnt = *(int*)arg;
  int s, j;

  for (j = 0; j < cnt; j++) {
    sleep(1);

    s = pthread_mutex_lock(&mtx_condvar);
    if (s != 0) {
      printf("pthread_mutex_lock falied, line number:%d.\n", __LINE__);
    }

    // 生产者，生产数据
    avail_use_condvar++;

    s = pthread_mutex_unlock(&mtx_condvar);
    if (s != 0) {
      printf("pthread_mutex_unlock falied, line number:%d.\n", __LINE__);
    }

    // 通知睡眠状态下的主消费线程
    s = pthread_cond_signal(&cond_condvar);
    if (s != 0) {
      printf("pthread_cond_signal falied, line number:%d.\n", __LINE__);
    }
  }

  return NULL;
}

int test_prod_condvar() {
  pthread_t tid;
  int s, j;
  int totRequired = 0;  // 生产者总共产生的数据量
  int numConsumed = 0; // 已消费的数据量
  int done = 0;
  time_t t;

  t = time(NULL);

  // 创建5个线程，用来生产数据
  int every_thread_unit = 1;
  for (j = 0; j < 5; j++) {
    totRequired += every_thread_unit;
    s = pthread_create(&tid, NULL, threadFunc_condvar, &every_thread_unit);  // 1表示 每个线程只生产一份数据
    if (s != 0) {
      printf("pthread_create falied, line number:%d.\n", __LINE__);
    }
  }

  // 使用主线程消费数据
  do {
    s = pthread_mutex_lock(&mtx_condvar);
    if (s != 0) {
      printf("pthread_mutex_lock failed, line number:%d\n", __LINE__);
    }

    // 当没有可消费资源时，等待通知
    while (avail_use_condvar == 0) {
      /// TODO 当唤醒过一次后，再次执行到此处钱所有 pthread_cond_signal 都执行完，本进程会不会在此处卡主？
      s = pthread_cond_wait(&cond_condvar, &mtx_condvar);
      if (s != 0) {
        printf("pthread_cond_wait failed, line number:%d\n", __LINE__);
      }
    }

    // 主线程消费所有的产品
    while (avail_use_condvar > 0) {

      /* 对数据做点其他事情 */

      numConsumed++;
      avail_use_condvar--; // 消费掉一份数据
      printf("T=%ld: numConsumed=%d\n", (long)(time(NULL) - t), numConsumed);

      done = numConsumed >= totRequired ? 1 : 0;
    }

    s = pthread_mutex_unlock(&mtx_condvar);
    if (s != 0) {
      printf("pthread_mutex_unlock failed, line number:%d\n", __LINE__);
    }

  } while (!done);

  return 0;
}
