
/**
 *  ��������������������ߺ�������
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

    // �����ߣ���������
    avail_use_condvar++;

    s = pthread_mutex_unlock(&mtx_condvar);
    if (s != 0) {
      printf("pthread_mutex_unlock falied, line number:%d.\n", __LINE__);
    }

    // ֪ͨ˯��״̬�µ��������߳�
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
  int totRequired = 0;  // �������ܹ�������������
  int numConsumed = 0; // �����ѵ�������
  int done = 0;
  time_t t;

  t = time(NULL);

  // ����5���̣߳�������������
  int every_thread_unit = 1;
  for (j = 0; j < 5; j++) {
    totRequired += every_thread_unit;
    s = pthread_create(&tid, NULL, threadFunc_condvar, &every_thread_unit);  // 1��ʾ ÿ���߳�ֻ����һ������
    if (s != 0) {
      printf("pthread_create falied, line number:%d.\n", __LINE__);
    }
  }

  // ʹ�����߳���������
  do {
    s = pthread_mutex_lock(&mtx_condvar);
    if (s != 0) {
      printf("pthread_mutex_lock failed, line number:%d\n", __LINE__);
    }

    // ��û�п�������Դʱ���ȴ�֪ͨ
    while (avail_use_condvar == 0) {
      /// TODO �����ѹ�һ�κ��ٴ�ִ�е��˴�Ǯ���� pthread_cond_signal ��ִ���꣬�����̻᲻���ڴ˴�������
      s = pthread_cond_wait(&cond_condvar, &mtx_condvar);
      if (s != 0) {
        printf("pthread_cond_wait failed, line number:%d\n", __LINE__);
      }
    }

    // ���߳��������еĲ�Ʒ
    while (avail_use_condvar > 0) {

      /* ������������������ */

      numConsumed++;
      avail_use_condvar--; // ���ѵ�һ������
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
