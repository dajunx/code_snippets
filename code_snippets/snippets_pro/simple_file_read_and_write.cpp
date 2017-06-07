//�򵥵��ļ���д

#include <iostream>
#include <string>
#include <fstream>

void write()
{
  std::fstream file("file.txt",
    std::fstream::in | std::fstream::out | std::fstream::app);
  file<<"lin";
  file.close();
}

void read()
{
  std::string str;
  std::fstream file("file.txt", std::fstream::in);
  file>>str;
  std::cout<<str;
  file.close();
}

//////////////////////////////////////////////////////////////////////////
// �����С����ʷ�ʽ��ȡ�ļ����ڴ���
// url:http://www.cnblogs.com/JCSU/articles/1190685.html
//////////////////////////////////////////////////////////////////////////

//��ȡ��ʽ: ��ʶ�ȡ, ��֮���ÿո�����
//read data from the file, Word By Word
//when used in this manner, we'll get space-delimited bits of text from the file
//but all of the whitespace that separated words (including newlines) was lost.
void ReadFileDataFromFileWBW()
{
  std::ifstream file("file.txt");
  std::string s;
  while(file>>s){
    std::cout<<"ch : "<<s<<std::endl;
  }
}

//��ȡ��ʽ: ���ж�ȡ, ���ж����ַ�����, ��֮���ûس���������
//If we were interested in preserving whitespace, 
//we could read the file in Line-By-Line using the I/O getline() function.
void ReadDataFromFileLBLIntoCharArray()
{
  std::ifstream fin("file.txt"); 
  const int LINE_LENGTH = 100; 
  char str[LINE_LENGTH];  
  while( fin.getline(str, LINE_LENGTH) )
  {    
    std::cout << "Read from file into char array: " << str << std::endl;
  }
}

//��ȡ��ʽ: ���ж�ȡ, ���ж����ַ���, ��֮���ûس���������
//If you want to avoid reading into character arrays, 
//you can use the C++ string getline() function to read lines into strings
void ReadDataFromFileLBLIntoString()
{
  std::ifstream fin("file.txt");  
  std::string s;  
  while(getline(fin,s))
  {    
    std::cout<<"Read from file into string: "<<s<<std::endl; 
  }
}

//��������Ķ�ȡ��ʽ
//Simply evaluating an I/O object in a boolean context will return false 
//if any errors have occurred
void ReadDataWithErrChecking()
{
  std::string filename = "dataFUNNY.txt";  
  std::ifstream fin( filename.c_str());  
  if( !fin ) 
  {   
    std::cout << "Error opening " << filename << " for input" << std::endl;
  }
}

int main()
{
  ReadFileDataFromFileWBW();
  ReadDataFromFileLBLIntoCharArray();
  ReadDataFromFileLBLIntoString();
  ReadDataWithErrChecking();

  write();
  read();

  return 0;
}