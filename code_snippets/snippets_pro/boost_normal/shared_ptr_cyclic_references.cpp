//shared_ptr ѭ����������
//std::shared_ptr �� std::weak_ptr���÷��Լ����ü�����ѭ����������
#include <iostream>  
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>

class Woman;  
class Man{  
private:  
  boost::weak_ptr<Woman> _wife;  
  //boost::shared_ptr<Woman> _wife;  
public:  
  void setWife(boost::shared_ptr<Woman> woman){  
    _wife = woman;  
  }  
  ~Man(){  
    std::cout << "kill man\n";  
  }  
};  

class Woman{  
private:  
  //boost::weak_ptr<Man> _husband;  
  boost::shared_ptr<Man> _husband;  
public:  
  void setHusband(boost::shared_ptr<Man> man){  
    _husband = man;  
  }  
  ~Woman(){  
    std::cout <<"kill woman\n";  
  }  
};  


int main(int argc, char** argv){  
  boost::shared_ptr<Man> m(boost::make_shared<Man>());  
  boost::shared_ptr<Woman> w(boost::make_shared<Woman>());  
  if(m && w) {  
    m->setWife(w);  
    w->setHusband(m);  
  }  
  return 0;  
}