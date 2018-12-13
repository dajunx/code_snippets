
// filesystem 创建移除目录、文件，内容管理测试
#include "boost_common.h"

using namespace boost;

//----------------- 目录增删改 -----------------------------------------------
enum e_control_type { CREATE_DIR, RENAME_DIR, DELETE_DIR};

bool manage_dir(std::string& directory_name, std::string& new_directory_name, 
  int control_type) {
    // check
    bool ret = false;
    bool is_directory = filesystem::is_directory(directory_name);
    filesystem::path path_dir(directory_name);
    try {
      switch (control_type) {
      case CREATE_DIR:
        {
          if (is_directory) { break; }
          ret = create_directory(path_dir);
        }      
        break;
      case RENAME_DIR:
        {
          if (!is_directory) { break; }
          filesystem::rename(path_dir, new_directory_name);
          ret = true;
        }
        break;
      case DELETE_DIR:
        {
          if (!is_directory) { break; }
          ret = filesystem::remove(directory_name);
        }
        break;
      default:
        break;
      }

      std::cout<<"control type: " << control_type 
        <<", directory name: " << directory_name
        <<", result: " << (ret == true?"true": "false")
        <<std::endl;
    } catch(filesystem::filesystem_error &e) {
      std::cerr << e.what() << '\n';
    }

    return ret;
}

enum e_file_type { CREATE_FILE, COPY_FILE, REMOVE_FILE};

void file_is_exist(std::string& filename, int control_type) {
  std::cout<< "action: " << control_type
    << "file " << filename
    << " is exist: " 
    << (filesystem::is_regular_file(filename)?"true":"false")
    << std::endl;
}

// 文件增删改
void manage_file(std::string& src_file_name, std::string& des_file_name,
  int file_control_type) {
    bool ret = false;
    try {
      switch (file_control_type)
      {
      case CREATE_FILE:
        {
          file_is_exist(src_file_name, file_control_type);
          if (filesystem::is_regular_file(src_file_name)) {
            break;
          }

          filesystem::ofstream of(src_file_name);
          file_is_exist(src_file_name, file_control_type);
        }
        break;
      case COPY_FILE:
        {
          file_is_exist(src_file_name, file_control_type);
          file_is_exist(des_file_name, file_control_type);
          filesystem::copy_file(filesystem::path(src_file_name), filesystem::path(des_file_name));
          file_is_exist(src_file_name, file_control_type);
          file_is_exist(des_file_name, file_control_type);
        }
        break;
      case REMOVE_FILE:
        {
          file_is_exist(des_file_name, file_control_type);
          filesystem::remove(filesystem::path(des_file_name));
          file_is_exist(des_file_name, file_control_type);
        }
        break;
      default:
        break;
      }
    } catch(filesystem::filesystem_error &e) {
      std::cerr << e.what() << '\n';
    }
}

void read_data_from_local_file(std::string& filename) {
  try
  {
    filesystem::path filePath(filename);
    if (!filesystem::exists(filePath) ||
      !filesystem::is_regular_file(filePath)) {
        return;
    }

    filesystem::fstream fs;
    char content[50];
    fs.open(filename, std::fstream::in);
    while (fs.getline(content, 50)) {
      std::cout<<content<<std::endl;
    }

    fs.close();
  } catch (filesystem::filesystem_error &e) {
    std::cerr << e.what() << '\n';  	
  }
}

void synce_data_to_local_file(std::string& filename) {
  try
  {
    filesystem::fstream fs;
    fs.open(filename,
      std::fstream::in | std::fstream::out | std::fstream::app);
    /*
    这种初始化 也可以  path 的 native函数
    path input_path(filename);
    fstream fs(input_path.native(),
               std::fstream::in | std::fstream::out | std::fstream::app);
    */
    fs << "hello" << std::endl;
    fs << "world" << std::endl;
    fs.close();
  } catch (filesystem::filesystem_error &e) {
    std::cerr << e.what() << '\n';  	
  }
}

//--------------------- 测试代码 -----------------------------------
void test_manage_dir() {
  std::string dir_name("C:\\TestFilesystemDir"), dir_new_name;
  int control_type = CREATE_DIR;
  manage_dir(dir_name, dir_new_name, control_type);

  dir_new_name.append(dir_name);
  dir_new_name.append("_temp");
  control_type = RENAME_DIR;
  manage_dir(dir_name, dir_new_name, control_type);

  dir_name = dir_new_name;
  dir_new_name.clear();

  control_type = DELETE_DIR;
  manage_dir(dir_name, dir_new_name, control_type);
}

void test_manage_file() {
  std::string file_name_with_path("c:\\test.xml");
  std::string file_name_with_path_temp("c:\\test_temp.xml");

  manage_file(file_name_with_path, file_name_with_path_temp, CREATE_FILE);
  manage_file(file_name_with_path, file_name_with_path_temp, COPY_FILE);
  manage_file(file_name_with_path, file_name_with_path_temp, REMOVE_FILE);
}

void test_write_read_file() {
  std::string filename_with_path("c:\\test.log");
  synce_data_to_local_file(filename_with_path);
  read_data_from_local_file(filename_with_path);
}

bool test_filesystem_dir_file_content() {
  test_manage_dir();
  test_manage_file();
  test_write_read_file();

  return true;
}