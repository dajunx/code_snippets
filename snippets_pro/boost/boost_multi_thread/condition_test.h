// thread condition条件变量
/*
采用condition控制生产者和消费者，若去掉只保留锁机制，会产生死锁：消费者取不到数据、并且不释放锁->导致生成者无法生成=>形成死锁。
修改点是让 消费者没内容时 while循环并释放锁直到有数据，方法很蹩脚
*/

// header file.
//#include <boost/thread/condition.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/thread.hpp>

const int BUF_SIZE = 10;
const int ITERS = 100;
boost::mutex io_mutex;

class buffer {
public:
  typedef boost::mutex::scoped_lock scoped_lock;
  buffer() : pos(0), c(0), full(0) {}
  void put(int m) {
    scoped_lock lock(mutex);

    if (full == BUF_SIZE) {
      {
        boost::mutex::scoped_lock lock(io_mutex);
        std::cout << "Buffer is full. Waiting..." << std::endl;
      }

      while (full == BUF_SIZE) {
        cond.wait(lock);
      }
    }

    buf[pos] = m;
    pos = (pos + 1) % BUF_SIZE;
    ++full;
    cond.notify_one();
  }

  int get() {
    scoped_lock lk(mutex);

    if (full == 0) {
      {
        boost::mutex::scoped_lock lock(io_mutex);
        std::cout << "Buffer is empty. Waiting..." << std::endl;
      }

      while (full == 0) {
        cond.wait(lk);
      }
    }

    int i = buf[c];
    c = (c + 1) % BUF_SIZE;
    --full;
    cond.notify_one();
    return i;
  }

private:
  boost::mutex mutex;
  boost::condition cond;
  unsigned int pos, c, full;
  int buf[BUF_SIZE];
};

buffer buf;

void writer() {
  for (int n = 0; n < ITERS; ++n) {
    {
      boost::mutex::scoped_lock lock(io_mutex);
      std::cout << "sending: " << n << std::endl;
    }
    buf.put(n);
  }
}

void reader() {
  for (int x = 0; x < ITERS; ++x) {
    int n = buf.get();
    {
      boost::mutex::scoped_lock lock(io_mutex);
      std::cout << "received: " << n << std::endl;
    }
  }
}

bool test_boost_thread_condition() {
  boost::thread thrd1(&reader);
  boost::thread thrd2(&writer);
  thrd1.join(); // join 阻塞主线程;
  thrd2.join();

  return true;
}