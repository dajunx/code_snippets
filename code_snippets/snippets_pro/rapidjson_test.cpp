
//��Ѷ json ��Դ����ԣ�ʹ�ð汾 v0.1 https://github.com/Tencent/rapidjson
// Դ��� 3rd

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
//#include "rapidjson/filereadstream.h"
//#include "rapidjson/filewritestream.h"
#include "rapidjson/filestream.h"
#include "rapidjson/reader.h"
#include <iostream>
#include <cstdio>

using namespace rapidjson;

int main() {
    std::string file_name("filter_words.txt");
    //FILE* fp = fopen(file_name.c_str(), "r"); // �� Windows ƽ̨ʹ�� "r"
    char readBuffer[65536];
    //FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    //d.ParseStream(is);


    FILE * pFile = fopen("filter_words.txt" , "r");
    if(pFile){
      //��ȡ�ļ����н�����json
      rapidjson::FileStream inputStream(pFile);
      d.ParseStream<0>(inputStream);
      fclose(pFile);
    }

    const rapidjson::Value& value1 = d;
    for (rapidjson::Value::ConstMemberIterator iter = value1.MemberBegin(); iter!=value1.MemberEnd(); ++iter)
    {
      const rapidjson::Value& name_json = iter->name; // ����������ַ���
      const rapidjson::Value& value_json = iter->value; // �������Ϊ���������
      //printf("%s\n", name_json.GetString());
      std::cout<<"name_json: "<<name_json.GetString()<<std::endl;
      std::cout<<name_json.GetType();

      rapidjson::Document document;
      document.SetObject();
      rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
      //rapidjson::Value data(rapidjson::kObjectType);
      std::string partner_id_data;
      rapidjson::Value data(rapidjson::kObjectType);
      //data.Swap(const_cast<rapidjson::Value&>(value1[name_json.GetString()]));
      data = const_cast<rapidjson::Value&>(value1[name_json.GetString()]);
      document.AddMember("keywords", data, allocator);

      std::string sub_file_name;
      std::string str_partner_id(name_json.GetString());
      sub_file_name.append(file_name, 0, file_name.size() -4); //�޳� ".txt" Ƭ��
      sub_file_name.append(str_partner_id.c_str());
      sub_file_name.append(".txt");
      //std::cout<<"filename: "<<sub_file_name<<std::endl;
/*
      FILE* fp_o = fopen(sub_file_name.c_str(), "w"); // �� Windows ƽ̨ʹ�� "w"
      char writeBuffer[65536];
      FileWriteStream os(fp_o, writeBuffer, sizeof(writeBuffer));
      Writer<FileWriteStream> writer(os);
      document.Accept(writer);
      fclose(fp_o);
*/

      FILE * pFile1 = fopen(sub_file_name.c_str(), "w");
      if(pFile1){
        //��ȡ�ļ����н�����json
        rapidjson::FileStream inputStream(pFile1);
        //StringBuffer buffer;
        Writer<rapidjson::FileStream> writer(inputStream);
        document.Accept(writer);
        fclose(pFile1);
      }

//       StringBuffer buffer;
//       Writer<StringBuffer> writer(buffer);
//       document.Accept(writer);

      sub_file_name.clear();
    }

    return 0;
}
