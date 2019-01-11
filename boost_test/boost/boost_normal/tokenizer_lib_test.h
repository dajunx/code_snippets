/*
  使用boost 库 分割 string 文本内容;
*/
#include "boost_common.h"
/*
 依赖的两个头文件
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>
*/

// 使用tokenizer 库拆分字符串;
void parse_string(std::string& input, const std::string& str_sep) {
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  boost::char_separator<char> sep(str_sep.c_str());
  tokenizer tokens(input.begin(), input.end(), sep);

  tokenizer::iterator it = tokens.begin();
  for (;it!=tokens.end();++it)
  {
    try {
      std::cout<<"sub string, content: " << boost::lexical_cast<boost::uint64_t>(*it) << std::endl;
    } catch (boost::bad_lexical_cast& a) {
      std::cout<<"err: "<<a.what()<<std::endl;
    }
  }
}

bool use_tokenizer_lib_parse_string() {
  const std::string sep(",:");
  std::string target_string("100003696:0,88400.0");
  parse_string(target_string, sep);

  target_string = "";
  parse_string(target_string, sep);

  target_string = "1,2,3";
  parse_string(target_string, sep);

  return true;
}