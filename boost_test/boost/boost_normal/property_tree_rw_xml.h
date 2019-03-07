//读写xml文件(property_tree/filesystem)
/*
使用boost 访问 xml内容
来源：https://www.technical-recipes.com/2014/using-boostproperty_tree/
*/
#include "boost_common.h"
/*
  need header file:
  #include <string>
  #include <boost/property_tree/xml_parser.hpp>
  #include <boost/property_tree/ptree.hpp>
  #include <boost/foreach.hpp>

*/

// test1.xml 文件内容
/*
<?xml version="1.0"?>
<purchaseOrder xmlns="http://tempuri.org/po.xsd" orderDate="1999-10-20">
    <shipTo country="US">
        <name>Alice Smith</name>
        <street>123 Maple Street</street>
        <city>Mill Valley</city>
        <state>CA</state>
        <zip>90952</zip>
    </shipTo>
    <billTo country="US">
        <name>Robert Smith</name>
        <street>8 Oak Avenue</street>
        <city>Old Town</city>
        <state>PA</state>
        <zip>95819</zip>
    </billTo>
    <comment>Hurry, my lawn is going wild!</comment>
    <items>
        <item partNum="872-AA">
            <productName>Lawnmower</productName>
            <quantity>1</quantity>
            <USPrice>148.95</USPrice>
            <comment>Confirm this is electric</comment>
        </item>
        <item partNum="926-AA">
            <productName>Baby Monitor</productName>
            <quantity>1</quantity>
            <USPrice>39.98</USPrice>
            <shipDate>1999-05-21</shipDate>
        </item>
    </items>
</purchaseOrder>
*/

// 访问 xml 中指定节点，比如 purchaseOrder 下 items 节点;
void Traverse_property_tree() {
  const std::string XML_PATH1 = "./test1.xml";

  boost::property_tree::ptree pt1;
  boost::property_tree::read_xml(XML_PATH1, pt1);

  // Traverse property tree example
  BOOST_FOREACH(boost::property_tree::ptree::value_type const& node, pt1.get_child("purchaseOrder.items"))
  {
    boost::property_tree::ptree subtree = node.second;

    if (node.first == "item")
    {
      BOOST_FOREACH(boost::property_tree::ptree::value_type const& v, subtree.get_child(""))
      {
        std::string label = v.first;

        if (label != "<xmlattr>")
        {
          std::string value = subtree.get<std::string>(label);
          std::cout << label << ":  " << value << std::endl;
        }
      }
      std::cout << std::endl;
    }
  }
}

// 通过 get 函数获取指定节点的值
void get_target_node_attribute_value_info() {
  const std::string XML_PATH1 = "./test1.xml";
  const std::string DEFAULT_PART_NO = "XYZ";
  const std::string DEFAULT_ZIP = "90125";

  boost::property_tree::ptree pt1;
  boost::property_tree::read_xml(XML_PATH1, pt1);

  std::string partNo = pt1.get<std::string>("purchaseOrder.items.item.<xmlattr>.partNum",
    DEFAULT_PART_NO);

  std::cout << "Part number: " << partNo << std::endl;

  std::string zipCode = pt1.get<std::string>("purchaseOrder.shipTo.zip",
    DEFAULT_ZIP);

  std::cout << "Zip Code: " << zipCode << std::endl;
}

// 写入xml到文件中
void save_xml_2_local_file() {
  const std::string XML =
    "<file>"
      "<people>"
        "<person>"
          "<forename>Andrew</forename>"
          "<surname>Jones</surname>"
        "</person>"
        "<person>"
          "<forename>David</forename>"
          "<surname>Matthews</surname>"
        "</person>"
        "<person>"
          "<forename>Jason</forename>"
          "<surname>Perkins</surname>"
        "</person>"
      "</people>"
    "</file>";

  boost::property_tree::ptree pt;

  // Put the XML string into a stringstream
  std::stringstream is;
  is << XML;

  // Read the stringstream into a Boost property tree, pt
  boost::property_tree::read_xml(is, pt);

  // Then write the Boost property tree to an output XML file
  boost::property_tree::xml_writer_settings<char> w(' ', 2);
  write_xml("output.xml", pt, std::locale(), w);
}