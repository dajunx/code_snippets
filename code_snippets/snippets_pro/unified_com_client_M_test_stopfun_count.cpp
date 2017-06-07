//unified_com_clientģ�� ����stop������ü������
/*
1������ stop ��̬����������������io_service��stop��������֮�󣬻�ִ����� post��io_service�ϵ�handler��stop����֮��post��handler����ִ�С�
���ܵ�ԭ���� ��ɶ˿ڵĵ�����FIFO��stop�������û� PostQueuedCompletionStatus Ͷ��һ���ر�run��ѭ����Ͷ�ݣ���run��ȡ���ú�����ʱ�򣬻����˳����̡�
2����io_service ��stop֮��Ӧ��post����Ӧ�ü����Լ�io_service ������������.
3��post��ȥ��Ͷ�ݣ���ʹ��weak_ptr �����Ӷ����weak_count����Ӧhandler���õ�ʱ��鿴use_count�Ƿ�Ϊ0��
  ���¶����Ƿ��Ѿ���������shared_from_this �����Ӷ�Ӧ��use_count��handler���õ�ʱ�����϶�δ�ͷš�
4������ IOCP ��ʹ�ú� BOOST_ASIO_DISABLE_IOCP
*/
#include <iostream>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/ref.hpp>
#include "E:\Work\iSpeak\common\sdk\utilities\inc\bind_weak_ptr.hpp"

using namespace boost;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
typedef boost::shared_ptr<boost::asio::io_service::work> io_work_ptr;
volatile boost::uint32_t finished_count = 0;
volatile bool after_stop_post = false;

struct test1 : public boost::enable_shared_from_this<test1> {
  io_service_ptr ptr_io_service;

  static io_service_ptr get_instance(bool stop = false,
    boost::shared_ptr<test1> ptr_test1 = nullptr)
  {
    static io_service_ptr ptr_io_service;
    static io_work_ptr ptr_io_work;
    static boost::shared_ptr<boost::thread> ptr_thread;
    static bool io_service_running = false;
    static boost::shared_ptr<test1> ptr_instance;

    if (stop) {
      io_service_running = false;
      ptr_io_work.reset();
      while (ptr_thread) {
        if (ptr_thread->try_join_for(boost::chrono::milliseconds(100))) {
          ptr_thread.reset();
        } else {
          ptr_io_service->stop(); // ��stop ����post����post��shared_from_this��ʽ��io_service����� ���������ͷ�
          if (false == after_stop_post) {
            after_stop_post = true;
            //ptr_test1->post1(9999);
            //ptr_test1.reset();
          }
          //ptr_io_service->stop();
        }
      }
      ptr_io_service.reset();
    }  else {
      if (!ptr_io_service) {
        ptr_io_service = boost::make_shared<boost::asio::io_service>();
        ptr_io_work = boost::make_shared<boost::asio::io_service::work>
          (boost::ref(*ptr_io_service));

        ptr_thread = boost::make_shared<boost::thread>(
          boost::bind(&test1::thread, ptr_io_service, boost::ref(io_service_running)));
        while (!io_service_running) {
          boost::this_thread::sleep(boost::posix_time::milliseconds(1));
        }
        //ptr_instance = boost::make_shared<test1>();
      }
    }

    return ptr_io_service;
  }

  static void thread(io_service_ptr ptr_io_service, bool& io_service_running)
  {
    //ptr_io_service->run();
    boost::unwrap_ref(io_service_running) = true;
    do {
      try {
        ptr_io_service->run();
      } catch (std::exception& e) {
      }

      if (io_service_running) {
        ptr_io_service->reset();
      } else {
        break;
      }
    } while (1);
  }

  test1()
  {
    ptr_io_service = get_instance();
  }

  void fun1(int i)
  {
    std::cout << "index :" << i << std::endl;
    ++finished_count;
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
  }

  void post(int i)
  {
    //ptr_io_service->post(boost::bind(&test1::fun1, shared_from_this(), i));
    //ptr_io_service->post(boost::bind(&test1::fun1, boost::weak_ptr<test1>(shared_from_this()), i));
    ptr_io_service->post(boost::bind(&test1::fun1, this, i));
  }

  void post1(int i)
  {
    ptr_io_service->post(boost::bind(&test1::fun1, shared_from_this(), i));
    //ptr_io_service->post(boost::bind(&test1::fun1, boost::weak_ptr<test1>(shared_from_this()), i));
  }

  static io_service_ptr stop(boost::shared_ptr<test1> ptr_test1)
  {
    return get_instance(true, ptr_test1);
  }

  ~test1()
  {
    int i = 0;
  }
};

int main()
{
  boost::shared_ptr<test1> ptr_test1 = boost::make_shared<test1>();
  ptr_test1->post(0);
  boost::shared_ptr<test1> ptr_test2 = boost::make_shared<test1>();
  for (int i = 0; i < 20; ++i) {
    ptr_test2->post(i);
  }

  //   ptr_test1.reset();
  //   ptr_test2.reset();

  //io_service_ptr ptr_io_service = test1::stop(ptr_test2);
  boost::this_thread::sleep(boost::posix_time::seconds(5));
  ptr_test1.reset();
  ptr_test2.reset();
  return 0;
}
