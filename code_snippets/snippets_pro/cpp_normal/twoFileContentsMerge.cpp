/*
  �ϲ������ļ����ݣ�����+����
*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime> //���� #include <time.h>

void writedata(std::vector<std::string>& write_data, std::string& out_filename)
{
  std::stringstream outPutFilename;
  time_t timep;  
  struct tm *p;   
  time(&timep);   
  p = localtime(&timep);
  outPutFilename<<"�ϲ���� "
    <<(1900+p->tm_year) << "-"
    <<(1+p->tm_mon) << "-"
    <<p->tm_mday << " "
    <<p->tm_hour << "-"
    <<p->tm_min << "-"
    <<p->tm_sec << ".txt";

  out_filename = outPutFilename.str();
  std::fstream file(out_filename,
    std::fstream::in | std::fstream::out | std::fstream::trunc);

  std::vector<std::string>::iterator it = write_data.begin();
  for (; it != write_data.end();++it)
  {
    file<<*it<<std::endl;
  }
  file.flush();
  file.close();
}

void writelog(std::string szlog)
{
  std::fstream file("log.txt",
    std::fstream::in | std::fstream::out | std::fstream::app);
  file<<szlog<<std::endl;
  file.close();
}

bool ReadDataFromFileLBLIntoString(const std::string& filename, std::vector<std::string>& file_data)
{
  std::ifstream fin(filename);  
  if (fin.is_open() == true) {
    std::string s;  
    while(getline(fin,s))
    {
      file_data.push_back(s);
    }
    fin.close();
    return true;
  } else {
    std::cout<<"------- ����.txt �� ����.txt �ļ� δ�ҵ����봴��--------"<<std::endl;
  }

  fin.close();
  return false;
}

bool checkTwoFileExist()
{
  bool ret = false;
  std::string input_file1("����.txt"), input_file2("����.txt");
  std::ifstream fin1(input_file1);
  std::ifstream fin2(input_file2);

  do 
  {
    if (fin1.is_open() == false) {
      break;
    }
    if (fin1.is_open() == false) {
      break;
    }
    ret = true;
  } while (0);
  fin1.close();
  fin2.close();
  return ret;
}

int main(int argc,char *argv[]) 
{
  std::cout<<"------------------ʹ��˵��---------------------"<<std::endl;
  std::cout<<std::endl;
  std::cout<<"���ڳ���ǰĿ¼���� ����.txt������.txt �����������ļ�"<<std::endl;
  std::cout<<std::endl;
  std::cout<<"------------------������...---------------------"<<std::endl;
  if (checkTwoFileExist() == false) {
    std::cout<<"��⵽��ǰĿ¼û�� ����.txt������.txt �����������ļ�"<<std::endl;
    Sleep(3000);
  }

  std::string input_file1("����.txt"), input_file2("����.txt");
  std::vector<std::string> vec_inputdata1, vec_inputdata2, vec_merge_data;
  bool bReadFileRes = false;
  if (ReadDataFromFileLBLIntoString(input_file1, vec_inputdata1) == false) {
    return 0;
  }
  if (ReadDataFromFileLBLIntoString(input_file2, vec_inputdata2) == false) {
    return 0;
  }

  std::vector<std::string>::iterator it_input_file1 = vec_inputdata1.begin();
  std::vector<std::string>::iterator it_input_file2;

  for (;it_input_file1 != vec_inputdata1.end();it_input_file1++)
  {
    it_input_file2 = vec_inputdata2.begin();
    for (;it_input_file2 != vec_inputdata2.end();it_input_file2++)
    {
      vec_merge_data.push_back(*it_input_file1 + *it_input_file2);
      vec_merge_data.push_back(*it_input_file2 + *it_input_file1);
    }
  }

  std::string outPutFileName;
  writedata(vec_merge_data, outPutFileName);
  int input_file1_count = vec_inputdata1.size();
  int input_file2_count = vec_inputdata2.size();
  int merge_count = vec_merge_data.size();

  std::cout<<"------------------������Ϣ---------------------"<<std::endl;
  std::cout<<"����ļ���:"<<outPutFileName<<std::endl;
  std::cout<<"����������: "<< input_file1_count <<std::endl;
  std::cout<<"����������: "<< input_file2_count <<std::endl;
  std::cout<<"�ϳ���: "<< merge_count <<std::endl;
  Sleep(3000);

  //log
  std::stringstream szlog;
  szlog<<"����ļ���: "<<outPutFileName
    <<", ����������: "<<input_file1_count
    <<", ����������: "<<input_file2_count
    <<", �ϳ���: "<<merge_count<<std::endl;
  writelog(szlog.str());

  return 0;
}