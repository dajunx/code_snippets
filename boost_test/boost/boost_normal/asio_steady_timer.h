// steady_timer 定时器使用

// boost::posix_time::to_simple_string函数需要这两个头文件
//#include <boost/date_time.hpp>
//#include <boost/date_time/posix_time/ptime.hpp>

//使用boost.chrono代替std.chrono,
#define BOOST_ASIO_DISABLE_STD_CHRONO

class boost_steady_time_class {
public:
  boost_steady_time_class() : work_(io_service_), timer_(io_service_) {}

public:
  boost::thread_group thread_group_;
  boost::asio::io_service io_service_;
  boost::asio::io_service::work work_;
  boost::asio::steady_timer timer_;

public:
  void Init() {
    boost::system::error_code errCode;
    thread_group_.create_thread(
      boost::bind(&boost::asio::io_service::run, boost::ref(io_service_), errCode));
    std::cout << "Init create thread, time: " << LocalTime() << std::endl;

    //设置过期时间长度
    timer_.expires_from_now(boost::chrono::milliseconds(4000));
    //std::cout << "Init set expire, time: " << LocalTime() << std::endl;
    //异步等待
    timer_.async_wait(boost::bind(
      &boost_steady_time_class::Test, this, /*boost::asio::placeholders::error*/_1));
    std::cout << "Init async wait, time: " << LocalTime() << std::endl;
    //由Console可知, 函数立即返回了, 定时器的expires_from_now是由完成端口处理的
  }

  void Test(const boost::system::error_code &ec) {
    //printf("Test entered, time: %s, ec.value=%d, ec.message=%s\n", 
    //       LocalTime().c_str(), ec.value(), ec.message().c_str());
    if (ec) {
      std::cout<<"Test fun meet err, ec.value=" << ec.value()
        << ", ec.message=" << ec.message().c_str()
        << std::endl;
      return;
    }
    timer_.expires_from_now(boost::chrono::milliseconds(4000));
    //std::cout << "Test set expire, time: " << LocalTime() << std::endl;
    timer_.async_wait(boost::bind(&boost_steady_time_class::Test, boost::ref(*this), _1));
    std::cout << "Test async awit, time: " << LocalTime() << std::endl;
  }

  void Stop() {
    std::cout << "begin stop, time: " << LocalTime() << std::endl;
    timer_.cancel(); // 取消所有handler
    work_.~work();
    thread_group_.join_all();
    std::cout << "finished stop, time: " << LocalTime() << std::endl;
  }

  static std::string LocalTime() {
    return boost::posix_time::to_simple_string(
      boost::posix_time::microsec_clock::local_time());
  }
};

bool steady_timer_test() {
  std::cout << "steady_timer_test begin." << std::endl;
  boost_steady_time_class steady_time;
  steady_time.Init();
  for (int i = 0; i < 30; ++i) {
    // 挂起当前进程指定时间
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
  }
  steady_time.Stop();

  std::cout << "steady_timer_test exit." << std::endl;
  return true;
}