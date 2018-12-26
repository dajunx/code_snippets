
/*
使用 filesystem遍历目录文件
*/
#include "boost_common.h"

using namespace boost::filesystem;
std::deque<std::string> filelist_deque_;
std::string read_only_path("E:\\System Volume Information");

// 获取指定目录下所有文件列表，[遍历所有子目录]
void get_path_all_files(std::string const& str_path_name) {
  path path(str_path_name);

  if (!exists(path) || !is_directory(path)) {
    return;
  }

  for (directory_iterator itr = directory_iterator(path);
    itr != directory_iterator(); ++itr) {
      if (read_only_path.compare(itr->path().string()) == 0) {
        continue;
      }

      if (is_regular_file(*itr)) {
        filelist_deque_.push_back(itr->path().string());
      } else if (is_directory(*itr)) {
        get_path_all_files(itr->path().string());
      } else {
        std::cout << "path: " << itr->path().string() 
          << " is not file or dir." << std::endl;
      }
  }
}

void print_paths() {
  std::deque<std::string>::iterator it = filelist_deque_.begin();
  while (it != filelist_deque_.end()) {
    std::cout<<"path: " << *it<< std::endl;
    it++;
  }
}

bool test_get_path_all_files() {
  std::string path("E:\\mayun_code");
  get_path_all_files(path);
  print_paths();

  return true;
}