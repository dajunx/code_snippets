// string_algo ��ʹ��

std::stringstream ret_str_tmp;
std::vector<string> strFilter;
split(strFilter, temp_str, is_any_of("<>"));
boost::iterator_range<string::iterator> ir;

for(BOOST_AUTO(it, strFilter.begin()); it!=strFilter.end(); ++it) {
  ir = boost::find_head(*it, 3); //ȥͷ��,��"img"�ַ���ͷ;
  if(true == boost::equals(std::string(ir.begin(), ir.end()), "img")) {
    ret_str_tmp<<"<"<<*it<<">";
  } else {
    ret_str_tmp<<dc.applyFilter_new(*it, hit_filter);
  }
}
ret_str = ret_str_tmp.str();