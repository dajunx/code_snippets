/*
  boost 公共头文件
*/
#ifndef BOOST_COMMON_HEADER
#define BOOST_COMMON_HEADER
// 系统头文件
#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <vector>
#include <map>
#include <unordered_map>
#include <deque>
#include <iterator>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <sstream>
#include <fstream>
#include <typeinfo>

// boost自带头文件
#include <boost/config.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/array.hpp>
#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/ref.hpp>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/typeof/typeof.hpp>

#include <boost/foreach.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>

#include <boost/generator_iterator.hpp>
#include <boost/random.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/date_time.hpp>
#include <boost/asio/steady_timer.hpp>

#include <boost/chrono/chrono.hpp>
// 协程
#include <boost/asio/coroutine.hpp>
#include <boost/asio/yield.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/constants.hpp>

#include <boost/cstdint.hpp>
// parse string
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>
#include <boost/token_functions.hpp>

//??
#include <boost/system/error_code.hpp>

#include <boost/locale.hpp>
#include <boost/regex.hpp>
#include <boost/chrono.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <boost/type_traits/detail\wrap.hpp>

// 用户自定义头文件
#include "E:\Work\iSpeak\common\sdk\utilities\inc\bind_weak_ptr.hpp"

// operator+=()
#include <boost/assign/std/vector.hpp>
#include <boost/assert.hpp>; 

#undef BOOST_COMMON_HEADER