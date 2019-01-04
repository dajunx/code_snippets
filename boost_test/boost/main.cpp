#include "boost_common.h"

// boost header files:
#include "boost_normal/array.h"
#include "boost_normal/asio_steady_timer.h"
#include "boost_normal/assign_items_to_container.h"
#include "boost_normal/atomic.h"
#include "boost_normal/bind_and_function.h"
#include "boost_normal/bind_life_cycle.h"
#include "boost_normal/bind_stl_fun.h"
#include "boost_normal/boost_and_normal_random.h"
#include "boost_normal/boost_function_bind_mixed_usage.h"
#include "boost_normal/boost_multi_index_test.h"
#include "boost_normal/calculate_fun_duration_time.h"
#include "boost_normal/cancle_steady_timer.h"
#include "boost_normal/chrono_time_test.h"
#include "boost_normal/coroutine.h"
#include "boost_normal/filesystem_copy_file.h"
#include "boost_normal/filesystem_dir_file_content_test.h"
#include "boost_normal/filesystem_get_path_all_files.h"
#include "boost_normal/filesystem_path_test.h"
#include "boost_normal/filesystem_savefile_del_oldfile.h"
#include "boost_normal/function_bypass_parameter_usage.h"
#include "boost_normal/function_lib.h"
#include "boost_normal/io_service_simple_test.h"
#include "boost_normal/io_service_wrap_test.h"
#include "boost_normal/judge_task_io_service_reactor_type.h"
#include "boost_normal/linux_get_file_property.h"
#include "boost_normal/multi_index_add_up_view.h"
#include "boost_normal/print_thread_id.h"
#include "boost_normal/property_tree_rw_ini_file.h"
#include "boost_normal/property_tree_write_read_json.h"
#include "boost_normal/ptime_test.h"
#include "boost_normal/regex_test.h"
#include "boost_normal/shared_ptr_cyclic_references.h"
#include "boost_normal/shared_ptr_use_count_change_test.h"
#include "boost_normal/split_string.h"
#include "boost_normal/tokenizer_lib_test.h"
#include "boost_normal/tuple_test.h"
#include "boost_normal/unified_com_client_M_test_stopfun_count.h"
#include "boost_normal/virtual_fun_post_test.h"
#include "boost_normal/wrap_usage.h"
#include "boost_normal/optional_test.h"

int total_test_fun() {
  test_boost_array();

  return true;
}

int main() {
  total_test_fun();

  return 0;
}