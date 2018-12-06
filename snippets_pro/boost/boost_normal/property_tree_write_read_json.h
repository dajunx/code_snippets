// boost property_tree read/write json
#include "boost_common.h"

/* net_json.json 文件内容:
{
  "height" : 320,
  "some" :
  {
  "complex" :
    {
      "path" : "hello"
    }
  },
  "animals" :
  {
    "rabbit" : "white",
    "dog" : "brown",
    "cat" : "grey"
  },
  "fruits" : ["apple", "raspberry", "orange"],
  "matrix" : [[1, 2, 3], [4, 5, 6], [7, 8, 9]],
  "peter" : [{"age": "111"}, {"address": "shanghai"}, {"name": "secret"}]
}
*/

//------------------------------ 遍历 json内容--------------------------
/*
  代码写的有些复杂，输出格式还不够完美，sub_scan_json_content 函数写的有些复杂，后续可能看不懂
*/
void json_content_print(int height, const std::string& name, const std::string& content) {
  while (height--) {
    std::cout<<" ";
  }
  //std::cout<<name<<", "<<content<<std::endl;
  if (name.compare("key") == 0) {
    std::cout<< content<< " : ";
  } else {
    std::cout<< content<< std::endl;
  }

  // 一级结点，换行
  if (height == 0) {
    std::cout<<","<<std::endl;
  }
}
int json_height = 0;
const std::string& strKey("key"), strValue("value");

void sub_scan_json_content(boost::property_tree::ptree& pt) {
  try {
    boost::property_tree::ptree::iterator pos = pt.begin();
    for (;pos != pt.end(); ++pos) {
      std::string strFirst = pos->first;

      // key 为"" 的情况，比如  "matrix" : [[1, 2, 3], [4, 5, 6], [7, 8, 9]] 中 [1,2,3]元素， 其中的1~9元素的key都是""
      if (strFirst.empty()) {
        boost::property_tree::ptree& pt_child = pos->second;
        if (pt_child.empty()) {
          json_content_print(json_height, strKey, pos->second.data());
        } else {
          // second 是一个复合结构，非单纯字符值
          json_height++;
          sub_scan_json_content(pt_child);
          json_height--;
        }
        continue;
      }

      json_content_print(json_height, strKey, pos->first);
      boost::property_tree::ptree& pt_child = pt.get_child(pos->first);
      if (pt_child.empty()) {
        json_content_print(json_height, strValue, pos->second.data());
        continue;
      } else {
        json_height++;
        sub_scan_json_content(pt_child);
        json_height--;
        std::cout<<std::endl;
      }
    }
  } catch (std::exception e) {
    std::cout<<"exception content: "<< e.what()<<std::endl;
  }
}

void scan_json_content() {
  boost::property_tree::ptree ptree;
  try {
    boost::property_tree::read_json("net_json.json", ptree);

    sub_scan_json_content(ptree);
  } catch (std::exception e) {
    std::cout<<"exception content: "<< e.what()<<std::endl;
  }
}

//------------------------------网络读取、写入json 代码--------------------------
// 如下两个函数参考: http://zenol.fr/blog/boost-property-tree/en.html
void read_json_fun() {
  // Short alias for this namespace
  namespace pt = boost::property_tree;
  // Create a root
  pt::ptree root;

  try {
    // Load the json file in this ptree
    pt::read_json("net_json.json", root);

    // Read values
    int height = root.get<int>("height", 0);
    // You can also go through nested nodes
    std::string path = root.get<std::string>("some.complex.path");
    std::string cat = root.get<std::string>("animals.cat");

    // 访问animals数据
    BOOST_FOREACH(boost::property_tree::ptree::value_type &animal, root.get_child("animals"))
    {
      std::cout<<"animal_name: " << animal.first << std::endl;
      std::cout<<"animal_color: " << animal.second.data() << std::endl;
    }

    // fruits 结点;
    std::cout<<std::endl;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &fruits, root.get_child("fruits"))
    {
      std::cout<<"fruit_name: " << fruits.second.data() << std::endl;
    }

    // matrix 结点, 重复使用 value_type;
    std::cout<<std::endl;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &matrix, root.get_child("matrix"))
    {
      BOOST_FOREACH(boost::property_tree::ptree::value_type &matrix_child, matrix.second)
      {
        std::cout<<"matrix_second_subItem_content: " 
                 << matrix_child.second.get_value<int>()
                 << std::endl;
      }
    }

    // peter 复合数据;
    std::cout<<std::endl;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &peter, root.get_child("peter"))
    {
      BOOST_FOREACH(boost::property_tree::ptree::value_type &peter_child, peter.second)
      {
        std::cout<<"peter_item_name: " << peter_child.first << std::endl;
        std::cout<<"peter_item_value: " << peter_child.second.data() << std::endl;
      }
    }

  } catch(std::exception e) {
    std::cout<<"exception content: " << e.what() << std::endl;
  }
}

void write_content_json() {
  // Short alias for this namespace
  namespace pt = boost::property_tree;
  // Create a root
  pt::ptree root;

  try {
    // 向json 添加普通数据 测试
    root.put("height", 25);
    root.put("some.complex.path", "bonjour");

    // 向json 添加复合数据
    pt::ptree pt_animals;
    std::map<std::string, std::string> map_animals;
    std::map<std::string, std::string>::iterator it_animal;
    map_animals["rabbit"] = "white";
    map_animals["dog"] = "brown";
    map_animals["cat"] = "grey";
    it_animal = map_animals.begin();
    for (;it_animal != map_animals.end();it_animal++)
    {
      pt_animals.put(it_animal->first, it_animal->second);
    }
    root.add_child("animals", pt_animals);

    // 3.Add many nodes with the same name
    pt::ptree fish1, fish2;
    fish1.put_value("blue");
    fish2.put_value("yellow");
    root.push_back(std::make_pair("fish", fish1));
    root.push_back(std::make_pair("fish", fish2)); // push_back代替put，是由于put会替换掉相同名称的结点

    // 4.添加没有名称(name)的结点
    pt::ptree matrix_node;
    for (int i=0;i<3;i++)
    {
      pt::ptree pt_child_nodes;
      for (int j=0;j<3;j++)
      {
        pt::ptree pt_child_node;
        pt_child_node.put("", j);

        //pt_child_node.push_back("", pt_child_node);
        pt_child_nodes.push_back(std::make_pair("", pt_child_node));
      }
      matrix_node.push_back(std::make_pair("", pt_child_nodes));
    }
    root.add_child("matrix", matrix_node);
    

    pt::write_json(std::cout, root);
  } catch (std::exception e) {
    std::cout<<"exception content: "<<e.what()<<std::endl;
  }
}

bool property_tree_write_read_json() {
  scan_json_content();
  //read_json_fun();
  //write_content_json();

  return true;
}