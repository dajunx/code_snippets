
/**
 * Linux环境 拷贝文件代码 read + write，参考 tlpi/tlpi/fileio/copy.c 文件
 */
#include <iostream>
#include <string>

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXSIZE 256

void copy_file(std::string const& src_filename, std::string const& dsc_filename) {
  int open_fd_src = -1, open_fd_dsc = -1;
  int call_api_ret = -1;
  int read_bytes = -1;

  // 打开指定文件
  open_fd_src = open(src_filename.c_str(), O_RDONLY);
  if (open_fd_src == -1) {
    std::cout << "open " << src_filename << " file failed." << std::endl;
    return;
  }

  int openFlags, filePerms;
  openFlags = O_CREAT | O_WRONLY /*| O_TRUNC*/;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
    S_IROTH | S_IWOTH;      /* rw-rw-rw- */
  open_fd_dsc = open(dsc_filename.c_str(), openFlags, filePerms);
  if (open_fd_dsc == -1) {
    std::cout << "open " << open_fd_dsc << " file failed." << std::endl;
    return;
  }

  //// 读取文件
  //char buf[MAXSIZE];
  //read_bytes = read(open_fd_src, buf, MAXSIZE);
  //if (read_bytes == -1) {
  //  std::cout << "read " << src_filename << " file failed." << std::endl;
  //  return;
  //}
  //
  //// 写入文件
  //call_api_ret = write(open_fd_dsc, buf, read_bytes);
  //if (call_api_ret == -1) {
  //  std::cout << "read " << src_filename << " file failed." << std::endl;
  //  return;
  //}

  // 转存文件
  char buf[MAXSIZE];
  int copy_count = 0;
  while ((read_bytes = read(open_fd_src, buf, MAXSIZE)) > 0) {
    copy_count++;
    if (write(open_fd_dsc, buf, read_bytes) != read_bytes) {
      std::cout << "err " << std::endl;
    }
  }

  std::cout << "file copy count:" << copy_count << std::endl;
}

int main() {
  std::string source_file_name("/root/projects/simple_linux_pro/file");
  std::string desc_file_name("/root/projects/simple_linux_pro/file1");
  copy_file(source_file_name, desc_file_name);

  return 0;
}