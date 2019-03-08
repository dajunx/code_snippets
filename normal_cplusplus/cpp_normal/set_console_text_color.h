
/**c++ console 控制台设置打印文本内容颜色和背景颜色
 * 来源：https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
 */
#include "cplusplus_common_def.hpp"
// header file.
// ##include <windows.h>

bool test_print_color_text_in_console() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  // you can loop k higher to see more color choices
  for (int k = 1; k < 255; k++)
  {
    // pick the colorattribute k you want
    SetConsoleTextAttribute(hConsole, k);
    cout << k << " I want to be nice today!" << endl;
  }

  return true;
}