// string_algo 简单使用
#include "boost_common.h"
/*
  需要包含的头文件:
  #include <boost/algorithm/string.hpp>
  #include <boost/algorithm/string/regex.hpp>
  #include <boost/algorithm/string/constants.hpp>
*/

void split_string_fun1() {
  std::string src("filter_src&linjianjun&content&");
  std::vector<std::string> vec_str;
  boost::split_regex(vec_str, src, boost::regex("&"));

  std::string str1("filter_src=linjianjun&content=!linjianjun");
  std::vector<std::string> SplitVec;
  // is_any_of 表示其中任何一个 字符 都可以作为分隔符， - 或者 *
  // token_compress_on 表示去掉字符串两端分割出来的空的token，默认是token_compress_off
  //   token_compress_on 仅仅对于字符串中间分隔有效，出现在字符串首位的分隔符前或后两次会分割出空格元素
  //   即 token_compress_on只对两个分隔元素都出现时，中间不产生空格元素
  boost::split(SplitVec, str1, boost::is_any_of("=&!"), boost::token_compress_on);
}