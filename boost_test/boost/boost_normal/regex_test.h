//替换掉内容中所有非中文字符，正则表达式为
//[^\u4e00-\u9fa5]+，替换掉中文字符类似表达式为 [\u4e00-\u9fa5]+
//keep_only_english_and_number 保留英文和数组，参照如下连接 的 unicode码
//https://unicode-table.com/cn/#005A  基本拉丁字母
#include "boost_common.h"

void remove_regex_words()
{
  std::wstring s1 = L"Boost Libraries的经32415&*)(^)";
  std::wstring s2 = L"林机 拉风的经 适房fasdf";

  boost::wregex reg1(L"[^\x30-\x39\x41-\x5A\x61-\x7A]+",
    boost::regex::icase | boost::regex::perl);
  boost::wregex reg2(L"[^\u4e00-\u9fa5]+",
    boost::regex::icase | boost::regex::perl);

  std::wstring res;
  // 1.去掉中文和空格
  res = boost::regex_replace(s1, reg1, "$1");
  res = boost::regex_replace(s2, reg1, "$1");

  // 2.去掉英文和其他标点符号;
  res = boost::regex_replace(s1, reg2, "$1");
  res = boost::regex_replace(s2, reg2, "$1");
}