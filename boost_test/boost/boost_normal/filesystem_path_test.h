#include "boost_common.h"

void filesystem_path_control(std::string& path_name) {
  boost::filesystem::path input_path(path_name);
  try {
    boost::system::error_code ec;
    bool find_path_ret = boost::filesystem::exists(input_path, ec);
    if (!find_path_ret) {
      return;
    }

    // 获取根目录
    boost::filesystem::path root_path = input_path.root_path();
    boost::filesystem::path root_name = input_path.root_name();

    // 给目录追加文件
    std::string fielname("udp_ini.txt");
    input_path = input_path / fielname;
    std::cout<<"changed path name: "<<input_path.string()<<std::endl;

    // 移除路径后缀，路径结尾的文件名
    boost::filesystem::path parent_path(input_path.parent_path().string());
    std::cout<<"changed path name: "<<parent_path.string()<<std::endl;
    std::cout<<"changed path name: "<<input_path.remove_filename().c_str()<<std::endl;

  } catch (boost::filesystem::filesystem_error &e) {
    std::cerr << e.what() << '\n';
  }
}


bool test_filesystem_path() {
  std::string path_name("c:\\");
  filesystem_path_control(path_name);

  return true;
}