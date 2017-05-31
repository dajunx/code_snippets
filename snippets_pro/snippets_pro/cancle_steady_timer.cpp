//steady_timer ��ʱ�� cancleȡ��
//steady_timer ��ʱ�� cancleȡ��ʱ����������ö�Ӧ��ʱ�䣬ͨ��error_code ����ȡ���¼�
#include <iostream>
#include <boost/asio/steady_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/thread.hpp>

typedef boost::asio::steady_timer asio_timer;
typedef boost::shared_ptr<asio_timer>  timer_ptr;
timer_ptr asio_timer_;

void timer_rsp(const boost::system::error_code& error)
{
  if (error) {
    int i = 0;
  } else {
    int i = 0;
  }
}

int main()
{
  boost::shared_ptr<boost::asio::io_service> ptr_io_service =
    boost::make_shared<boost::asio::io_service>();
  boost::shared_ptr<boost::asio::io_service::work> ptr_work =
    boost::make_shared<boost::asio::io_service::work>(boost::ref(*ptr_io_service));
  boost::thread th(boost::bind(&boost::asio::io_service::run,
    boost::ref(*ptr_io_service)));
  th.detach();

  asio_timer_ = boost::make_shared<asio_timer>
    (boost::ref(*ptr_io_service),
    boost::chrono::seconds(10));
  asio_timer_->async_wait(
    boost::bind(&timer_rsp, boost::asio::placeholders::error));

  boost::this_thread::sleep(boost::posix_time::seconds(4));

  boost::system::error_code ec;
  asio_timer_->cancel(ec);
  if (ec) {
    int i = 0;
  }
  asio_timer_.reset();
  boost::this_thread::sleep(boost::posix_time::seconds(4));
  return 0;
}