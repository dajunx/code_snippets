//��дini�ļ�(property_tree/filesystem)
/*
ʹ��boost property_tree��filesystemʵ��ini�ļ��Ķ�д��ע��㣺map�ṹkey����Ϊstring���ͣ�
  ��Ϊ�ڱ���ini�ļ���ʱ�����ɽڵ���key��.age����ƴ�ӣ�
  �����ʹ��std::stringstream �����ε�key���ַ��� .age ������ڵ�ǰƴ�ӡ�
*/
#include <iostream>
#include <map>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

struct data {
  data(int age_tmp, std::string const& name_tmp)
    : age(age_tmp), name(name_tmp) {}
  int age;
  std::string name;
};
std::map<std::string, boost::shared_ptr<data> > map_data;

void load_from_ini()
{
  std::string file_location;
  file_location.append("file.txt");
  boost::filesystem::path file_path(file_location.c_str());

  if (boost::filesystem::exists(file_path)
    && boost::filesystem::is_regular_file(file_path)) {
      try {
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini(file_location, pt);
        boost::property_tree::ptree::iterator tag_pt;

        for (tag_pt = pt.begin(); tag_pt != pt.end(); tag_pt++) {
          map_data[tag_pt->first] = boost::make_shared<data>
            (tag_pt->second.get<int>("age"),
            tag_pt->second.get<std::string>("name"));
        }
      } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
      }
  }
}

void save_to_disk()
{
  boost::property_tree::ptree pt;
  BOOST_AUTO(it, map_data.begin());

  try {
    for (; it != map_data.end(); ++it) {
      pt.add(it->first + ".age", it->second->age);
      pt.add(it->first + ".name", it->second->name);
    }

    std::string file_location;
    file_location.append("file.txt");
    boost::property_tree::write_ini(file_location, pt);
  } catch (std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

int main()
{
  std::stringstream name, key;
  // ��map�����¼
  for (int i = 0; i < 10; ++i) {
    name.str("");
    key.str("");
    name << "lin'";
    name << i;
    key << i;
    map_data.insert(std::make_pair(key.str(),
      boost::make_shared<data>(i, name.str())));
  }

  save_to_disk();
  map_data.clear();
  load_from_ini();

  BOOST_AUTO(it, map_data.begin());
  for (; it != map_data.end(); ++it) {
    std::cout << "key:" << it->first
      << ", value-name:" << it->second->name
      << ", value-age:" << it->second->age
      << std::endl;
  }
  return 0;
}