//__FILE__ 全路径、相对路径问题
/*
__FILE__
宏在debug模式下，h和cpp文件都是全路径；在release模式下，h是全路径、cpp是相对路径
*/

#include "cplusplus_common_def.hpp"

bool test_macro_FILE() {
  std::cout << "__FILE__ => " << __FILE__ << std::endl
            << "__LINE__ => " << __LINE__
            << std::endl;

  return true;
}