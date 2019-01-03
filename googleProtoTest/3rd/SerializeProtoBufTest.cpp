#include <iostream>
#include <string>

// io
#include <fstream>
#include <iostream>

// GoogleProtoBuf
#include <google\protobuf\message.h>

// 协议头文件;
#include "proto_config/lm.helloworld.pb.h"

// base64 header file
// 目录:cplusplus\code_snippets\snippets_pro\3rd\base64，还得包含cpp实现文件
#include "base64/base64.h"

//------------------io处理函数-------------------------
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

//此处解析所有协议，把由string转换成 GoogleProtobuf类型;
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

template <typename MSG>
bool conver_proto_obj_to_string(MSG obj, std::string& ret) {
  try
  {
    obj.SerializeToString(&ret);
    ret = base64_encode(reinterpret_cast<const unsigned char*>(ret.c_str()), ret.length());
  }
  catch (...)
  {
    std::cout<<"err, parse input content failed."<<std::endl;
    return false;
  }

  return true;
}

int main() {
  /* 
  待解析的内容，已经经过了base64_decode： 
  CKazqxsQHhgGIAIo0tDT3wUyKgogNzkyZTE5MzUwNWUwYmM5YjE0N2RlZmVmNjc1ZTI3NjcQ0tDT3wUgYw==
  */
  std::string str_proto_content;
  lm::am_dispatch_raw_datas raw_datas;
  raw_datas.set_msg_id(1);
  raw_datas.set_datas("1111111");
  conver_proto_obj_to_string<lm::am_dispatch_raw_datas>(raw_datas, str_proto_content);

  std::string sourceStr("");
  //ParseString2Protobuff<lm::helloworld>(sourceStr, true);
  return 0;
}