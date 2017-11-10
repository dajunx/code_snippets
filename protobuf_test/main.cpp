#include <iostream>
#include <string>
#include <fstream>
#include "lm.helloworld.pb.h"
using namespace std;

/*
void ListMsg(const lm::helloworld & msg)
{
	cout << msg.id() << endl; 
	cout << msg.str() << endl; 
}

void put_disk(lm::helloworld & msg)
{
	msg.set_id(101);
	msg.set_str("hello");

	// Write the new address book back to disk. 
	fstream output("./log", ios::out | ios::trunc | ios::binary);

	if (!msg.SerializeToOstream(&output))
	{
		cerr << "Failed to write msg." << endl;
		output.close();
		return;
	}
	output.close();
}

void read_from_disk()
{
	// write
	lm::helloworld msg2;
	{
		fstream input("./log", ios::in | ios::binary);
		if (!msg2.ParseFromIstream(&input))
		{
			cerr << "Failed to parse address book." << endl;
			input.close();
			return;
		}
		input.close();
	}
	ListMsg(msg2);
}

void save2disk_and_read()
{
  lm::helloworld msg;
	put_disk(msg);

	
  //string buf;
  //msg.SerializeToString(&buf);
  //lm::helloworld* tmp = new lm::helloworld();
  //tmp->ParseFromString(buf);
  //cout<<tmp->id()<<tmp->str()<<endl;
	

	// void *
	void* data = new char(msg.ByteSize());
	msg.SerializeToArray(data, msg.ByteSize());
	lm::helloworld* tmp = new lm::helloworld();
	tmp->ParsePartialFromArray(data, msg.ByteSize());
	cout<<tmp->id()<<tmp->str()<<endl;
	//read_from_disk();
}
*/

int main()
{
  lm::helloworld msg;
  msg.set_id(5);
  lm::userinfo* ui = msg.mutable_ui();
  ui->set_uid(555);
  ui->set_pwd(999);
  ui->set_name("lin");
  ui->set_some("hello!");
  std::cout << "message: "<<msg.Utf8DebugString() << std::endl;

  lm::userinfo* p_userinfo = msg.mutable_uinfo();
  if (p_userinfo) {
    p_userinfo->set_uid(555);
    p_userinfo->set_pwd(666);
    p_userinfo->set_name("linjianjun");
    p_userinfo->set_some("hello world!");
  }

  const std::string& str_tmp = msg.uinfo().name();
  std::string* p_str_tmp = msg.mutable_uinfo()->mutable_name();

  std::string ss;
  ui->SerializeToString(&ss);
  std::cout << "serialized msg: "<< ss << std::endl;

  int i = 0;
	return 0;
}