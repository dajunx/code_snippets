// linux获取文件属性
/*
How to get file permissions with c++ boost library?
函数原型：perms      permissions() const                { return m_perms; }
defined in boost/filesystem/v3/operations.hpp
*/
// link:http://stackoverflow.com/questions/9776050/how-to-get-file-permissions-with-c-boost-library
#include "boost_common.h"

namespace fs = boost::filesystem;

bool linux_get_file_property() {
  fs::path p(argv[1]);
  fs::file_status s = status(p);
  printf("%o\n", s.permissions());

  return true;
}