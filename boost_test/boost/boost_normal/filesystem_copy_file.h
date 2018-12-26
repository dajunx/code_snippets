//使用filesystem拷贝磁盘文件
#include "boost_common.h"

using namespace boost::filesystem;
std::deque<std::string> g_file_content_deque;
std::deque<std::string> g_all_file_wholePath_deque;
std::string g_read_only_path("E:\\System Volume Information");

void write_content_to_disk() {
  path input_path("e:\\tmp.ipp");
  fstream fs(input_path.native(),
    std::fstream::in | std::fstream::out | std::fstream::app);
  BOOST_AUTO(it, g_file_content_deque.begin());
  for (; it != g_file_content_deque.end(); ++it) {
    fs << *it << "\n";
  }
  fs.close();
}

void save_all_filenames_to_disk() {
  path input_path("e:\\tmp.txt");
  fstream fs(input_path.native(),
    std::fstream::in | std::fstream::out | std::fstream::app);
  BOOST_AUTO(it, g_all_file_wholePath_deque.begin());
  int x = 0;
  for (; it != g_all_file_wholePath_deque.end(); ++it) {
    fs << *it << "\n";
    //     path file_path(*it);
    //     x = status(file_path).permissions();
    //     if (x != 438)
    //       fs << *it <<"\n";
    //     x = 0;
  }
  fs.close();
}

void read_content_from_file1(std::string const &path_input) {
  std::string cache_dir_temp;
  if (path_input.empty()) {
    cache_dir_temp.assign("C:\\Users\\Administrator\\Pictures\\1.txt");
  } else {
    cache_dir_temp = path_input;
  }
  path input_path(cache_dir_temp);
  if (!exists(input_path) || !is_regular_file(input_path)) {
    return;
  }

  char c_content[256];
  fstream fs(input_path.native());
  while (fs.getline(c_content, 256)) { // read a line
    g_file_content_deque.push_back(std::string(c_content));
  }
  fs.close();
}

// 第二种方式，用一个char堆来存放单个文本内容，不过有点问题
void read_content_from_file2(std::string const &path_input) {
  std::string cache_dir_temp;
  if (path_input.empty()) {
    cache_dir_temp.assign("C:\\Users\\Administrator\\Pictures\\1.txt");
  } else {
    cache_dir_temp = path_input;
  }
  path input_path(cache_dir_temp);
  if (!exists(input_path) || !is_regular_file(input_path)) {
    return;
  }

  if (cache_dir_temp.find(".cpp") == std::string::npos &&
    cache_dir_temp.find(".cc") == std::string::npos &&
    cache_dir_temp.find(".hpp") == std::string::npos &&
    cache_dir_temp.find(".h") == std::string::npos) {
      return;
  }

  ifstream file(input_path.native());
  file.seekg(0, ifstream::end);
  int size = file.tellg();
  char *contents = new char[size];
  file.seekg(0, ifstream::beg);
  file.read(contents, size);
  contents[size] = '\0';
  g_file_content_deque.push_back(contents);
  file.close();
}

void read_content_from_filelist3() {
  path input_path_outer("e:\\tmp.ipp");
  fstream fs(input_path_outer.native(),
    std::fstream::in | std::fstream::out | std::fstream::app);

  BOOST_AUTO(it, g_all_file_wholePath_deque.begin());
  //优化点 循环前new一块内存供给向磁盘写入内容使用，内存消耗会小很多。linux
  //端也不报错 不过这个new的值是后期算出来的，不智能
  int max_size = 2234683;
  char *contents = new char[max_size];
  for (; it != g_all_file_wholePath_deque.end(); ++it) {
    std::string cache_dir_temp = *it;

    if (!cache_dir_temp.empty()) {
      path input_path(cache_dir_temp);
      if (!exists(input_path) || !is_regular_file(input_path)) {
        continue;
      }

      if (cache_dir_temp.find(".cpp") == std::string::npos &&
        cache_dir_temp.find(".cc") == std::string::npos &&
        cache_dir_temp.find(".hpp") == std::string::npos &&
        cache_dir_temp.find(".h") == std::string::npos) {
          continue;
      }

      ifstream file(input_path.native());
      file.seekg(0, ifstream::end);
      int size = file.tellg();
      // if (size > max_size) max_size = size;
      // char* contents = new char [size];
      file.seekg(0, ifstream::beg);
      file.read(contents, size);
      contents[size] = '\0';
      fs << contents << "\n";
      file.close();
      contents[0] = '\0';
    }
  }

  fs.close();
}

void save_one_path_contain_files_wholePath(std::string const &path_tmp,
  std::deque<std::string> &directory_path) {
    path input_path(path_tmp);
    if (!exists(input_path) || !is_directory(input_path)) {
      return;
    }

    int x = status(input_path).permissions();

    directory_iterator itr = directory_iterator(input_path);
    for (;itr != directory_iterator(); ++itr) {
      if (g_read_only_path.compare(itr->path().string()) == 0) {
        continue;
      } else if (is_regular_file(*itr)) {// 文件
        g_all_file_wholePath_deque.push_back(itr->path().string());
      } else if (is_directory(*itr)) {// 目录
        directory_path.push_back(itr->path().string());
      }
    }
}

bool read_filepath_list(std::string const &path_tmp) {
  bool ret = false;
  do 
  {
    if (path_tmp.empty()) {
      break;
    }
    path input_path(path_tmp);

    char c_content[256];
    fstream fs(input_path.native());
    while (fs.getline(c_content, 256)) { // read a line
      g_all_file_wholePath_deque.push_back(std::string(c_content));
      if(!ret) ret = true;
    }
    fs.close();
  } while (false);
  return ret;
}

void save_file_wholePath(std::string const &root_path) {
  // 若已缓存指定根目录下所有文件 路径+文件名，则不再解析路径
  std::string cached_file_WholePath("e:\\cached_rootpath_files_whole_path.txt");
  if (exists(cached_file_WholePath) && is_regular_file(cached_file_WholePath)) {
    if (read_filepath_list(cached_file_WholePath)) {
      return;
    }
  }

  //缓存指定目录下所有文件路径，每次进入函数，只记录文件路径，对目录路径缓存下次在解析
  std::deque<std::string> cached_child_paths;
  save_one_path_contain_files_wholePath(root_path, cached_child_paths);
  while (cached_child_paths.size() > 0) {
    save_one_path_contain_files_wholePath(cached_child_paths.front(), cached_child_paths);
    cached_child_paths.pop_front();
  }

  save_all_filenames_to_disk();
}

// 目录创建
void create_director(path const &path_tmp, path const &root_path) {
  path path_source = path_tmp;
  std::deque<path> deque_path;
  while (path_source != root_path) {
    deque_path.push_back(path_source);
    path_source = path_source.parent_path();
  }

  BOOST_AUTO(it, deque_path.rbegin());
  for (; it != deque_path.rend(); ++it) {
    boost::filesystem::create_directory(*it);
  }
}

void copy_files(std::string const &save_path) {
  std::string path_one_file = save_path;
  std::string path_one_file_tmp = save_path;
  path_one_file_tmp.erase(--path_one_file_tmp.end());
  BOOST_AUTO(it, g_all_file_wholePath_deque.begin());
  for (; it != g_all_file_wholePath_deque.end(); ++it) {
    if ((*it).find(".cpp") == std::string::npos &&
      (*it).find(".cc") == std::string::npos &&
      (*it).find(".hpp") == std::string::npos &&
      (*it).find(".h") == std::string::npos) {
        continue;
    }

    path source_path(*it);
    path_one_file.append(source_path.relative_path().string()); //替换目录根部
    path dest_path(path_one_file);
    path save_path_tmp(path_one_file_tmp);

    // 目录创建
    if (!exists(dest_path.parent_path())) {
      create_director(dest_path.parent_path(), save_path_tmp);
    }

    fstream fs(dest_path.native(),
      std::fstream::in | std::fstream::out | std::fstream::app);

    ifstream file(source_path.native());
    file.seekg(0, ifstream::end);
    int size = file.tellg();
    char *contents = new char[size];
    file.seekg(0, ifstream::beg);
    file.read(contents, size);
    contents[size] = '\0';
    file.close();

    fs << contents << "\n";
    fs.close();
    path_one_file.assign(save_path);
  }
}

void copy_file_to_another_path(std::string const &source_path,
  std::string const &dest_path) {
    // 缓存待拷贝文件目录列表
    save_file_wholePath(source_path);
    copy_files(dest_path);
}

bool test_filesystem_copy_file_test() {
  copy_file_to_another_path("E:\\Work\\3rd\\boost_1_53_0\\boost\\", "d:\\tmp\\");
  return true;
}