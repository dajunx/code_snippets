#include <iostream>
#include <string>

// io
#include <fstream>
#include <iostream>

// GoogleProtoBuf
#include <google\protobuf\message.h>

// Э��ͷ�ļ�;
#include "../protobuf_test/lm.helloworld.pb.h"

// base64 header file
// Ŀ¼:cplusplus\code_snippets\snippets_pro\3rd\base64�����ð���cppʵ���ļ�
#include "base64.h"

//------------------io������-------------------------
void write(std::string& output) {
  std::fstream file("output.txt",
    std::fstream::in | std::fstream::out | std::fstream::app);
  file << output;
  file.close();
}

void read(std::string& getcontent) {
  std::fstream file("input.txt", std::fstream::in);
  file >> getcontent;
  file.close();
}
//------------------end-------------------------

std::string testParse_helloworld()
{
  lm::helloworld hell;
  hell.set_id(1);
  hell.set_str("1");

  lm::userinfo* p_helloworld = hell.add_uinfo();
  p_helloworld->set_uid(1);
  p_helloworld->set_pwd(1);
  p_helloworld->set_name("1");

  std::string temp;
  hell.SerializeTo String(&temp);
  //base64_encode(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
  return temp;
}

//�˴���������Э�飬����stringת���� GoogleProtobuf����;
template <typename MSG>
void ParseString2Protobuff(std::string& inputStr, bool base64decode = false) 
{
  try
  {
    std::string strSrc = inputStr;
    if (base64decode) {
      inputStr = base64_decode(inputStr);
    }

    MSG msg;
    msg.ParseFromString(inputStr);
    std::cout<<"succ, input source content:" << strSrc <<std::endl;
    std::cout<<"parse result:" << std::endl <<msg.DebugString()<<std::endl;
    //write(daluandou_rank.DebugString());
  }
  catch (...)
  {
    std::cout<<"err, parse input content failed."<<std::endl;
  }
}

int main() {
  /* 
  �����������ݣ��Ѿ�������base64_decode�� 
  CKazqxsQHhgGIAIo0tDT3wUyKgogNzkyZTE5MzUwNWUwYmM5YjE0N2RlZmVmNjc1ZTI3NjcQ0tDT3wUgYw==
  */

  std::string sourceStr("");
  ParseString2Protobuff<lm::helloworld>(sourceStr, true);
  return 0;
}