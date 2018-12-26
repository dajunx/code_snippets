// asio io_service 例子
#include "boost_common.h"

using namespace boost;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
typedef boost::shared_ptr<boost::asio::io_service::work> io_work_ptr;
static int task_execute_count = 0;

void test_asio_post(io_service_ptr io) {
  std::cout<<"asio execute task, count:" << task_execute_count++ <<std::endl;
  boost::this_thread::sleep(boost::posix_time::seconds(1));
  //io->post(boost::bind(&fun1, io));
}

bool io_service_common_test() {
  // 1.生成io_service 对象及其work对象
  io_service_ptr ptr_io_service = boost::make_shared<boost::asio::io_service>();
  io_work_ptr ptr_io_work = boost::make_shared<boost::asio::io_service::work>(
    boost::ref(*ptr_io_service));

  // 2.把上面初始化好的io_service 放入线程中运行，即 开启了一个任务处理器，可以往其中分配任务;
  boost::thread th(boost::bind(&boost::asio::io_service::run, ptr_io_service));
  th.detach();

  // 3.向准备就绪的 asio [io_service] 投递任务
  ptr_io_service->post(boost::bind(&test_asio_post, ptr_io_service));

  // 4.此处目的是sleep  挂起主线程，好让 io_service 继续执行任务，不会由于父进程销毁而销毁掉
  boost::this_thread::sleep(boost::posix_time::seconds(100));

  return true;
}