// select 模型之 键盘输入

// header files
#include "select_module_keyboard.h"
#include "normal/net_normal_client.h"
#include "normal/net_normal_server.h"

void main_test(int argc, char **argv) {
	test_select_module_keyborad();

  test_net_normal_client(argc, argv);
  test_net_noraml_server(argc, argv);
}

int main(int argc, char **argv) {
  main_test(argc, argv);

  return 0;
}
