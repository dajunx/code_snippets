
//c���i/O
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <boost/locale.hpp>

void conver_vec_2_string(std::vector<char>& src, std::string& des)
{
  std::stringstream contents;
  std::vector<char>::iterator it = src.begin();
  for (; it!=src.end(); it++)
  {
    contents<<*it;
  }
  des = contents.str();
}

void print_contents(std::vector<char>& buf)
{
  std::stringstream ss;

  std::cout<<"content :"<<std::endl;
  std::vector<char>::iterator it = buf.begin();
  for (; it != buf.end(); it++)
  {
    //std::cout<<*it;
    ss<<*it;
  }
  std::wstring wss = boost::locale::conv::utf_to_utf<wchar_t>(ss.str());
  std::wcout<<wss;
  std::wcout<<std::endl;
}

//--------------------��ȡ�ļ�----------------------------------------
void ReadContentFromFILEVersion1(FILE* fp, std::vector<char>& buf)
{
  int c;
  while ((c = std::fgetc(fp)) != EOF) {
    buf.push_back(c);
    //std::putchar(c);
  }
  print_contents(buf);
}

void ReadContentFromFILEVersion2(FILE* fp, std::vector<char>& buf, int content_size)
{
  buf.resize(content_size);
  std::fseek(fp, 0, SEEK_SET);
  fread(&buf[0], sizeof(buf[0]), buf.size(), fp);
  print_contents(buf);
}

std::string readInputTestFile(std::string file_path)
{
  FILE *file = fopen(file_path.c_str(), "rb");
  if (!file) {
    return std::string("");
  }

  fseek( file, 0, SEEK_END );// Ѱλ����β
  long size = ftell( file );
  fseek( file, 0, SEEK_SET );// Ѱλ����ʼ
  std::string text;
  char *buffer = new char[size+1];
  buffer[size] = 0;
  if ( fread( buffer, 1, size, file ) == (unsigned long)size )
    text = buffer;

  fclose( file );
  delete[] buffer;

  const std::wstring wstr = boost::locale::conv::utf_to_utf<wchar_t>(text);

  return text;
}
//--------------------end---------------------------------------------


//--------------------д���ļ�----------------------------------------
void WriteContentsToLocalFile(std::string file_name, FILE* fp, std::string contents)
{
  if(!fp) return;

  fwrite(contents.c_str(), 1, contents.size(), fp);
  fclose(fp);
}
//--------------------end---------------------------------------------


void test_fun1()
{
  std::wstring wss(L"�����ǵ�");
  std::wcout<<wss<<std::endl;
}

int main()
{
  setlocale(LC_ALL, "chs"); //Ҫʹ�� wcout��ӡ���ģ��������ã�Ĭ�ϲ��������
  //test_fun1();
  std::string file_name("filter_new.txt");
  //readInputTestFile(file_name);

  FILE* fp = fopen(file_name.c_str(), "r");
  std::vector<char> buf;
  if(fp) {    
    ReadContentFromFILEVersion1(fp, buf);
    buf.clear();
    ReadContentFromFILEVersion2(fp, buf, 79);
  }
  fclose(fp);


  std::string write_file("writer.txt");
  FILE* fpw = fopen(write_file.c_str(), "w");
  if(fpw) {
    std::string writes;
    conver_vec_2_string(buf, writes);
    WriteContentsToLocalFile(write_file, fpw, writes);
  }

  return 0;
}