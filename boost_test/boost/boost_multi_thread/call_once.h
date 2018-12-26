//一次实现once routine

// include header file
//#include <boost/thread/once.hpp>
//#include <boost/thread/thread.hpp>

int i = 0;
boost::once_flag flag = BOOST_ONCE_INIT;

// 函数只执行一次
void init() {
  ++i;
  std::cout<<"i value:"<<i<<std::endl;
}

void thread() { 
  std::cout<<" step into thread fun."<<std::endl;
  boost::call_once(&init, flag); 
  std::cout<<" leave thread fun."<<std::endl;
}

bool test_call_once() {
  boost::thread thrd1(&thread);
  boost::thread thrd2(&thread);
  thrd1.join();
  thrd2.join();

  boost::this_thread::sleep(boost::posix_time::seconds(10));
  return true;
}