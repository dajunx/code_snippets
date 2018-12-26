// linux获取文件属性
/*
How to get file permissions with c++ boost library?
函数原型：perms      permissions() const                { return m_perms; }
defined in boost/filesystem/v3/operations.hpp
*/
// link:http://stackoverflow.com/questions/9776050/how-to-get-file-permissions-with-c-boost-library
#include "boost_common.h"
#ifdef LINUX

namespace fs = boost::filesystem;

bool linux_get_file_property(std::string& directoryPath) {
  fs::path p(directoryPath);
  fs::file_status s = status(p);
  printf("%o\n", s.permissions());

  return true;
}

#endif