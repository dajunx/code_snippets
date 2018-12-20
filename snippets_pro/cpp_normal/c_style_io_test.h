// c风格i/O
#include "cplusplus_common_def.hpp"

void conver_vec_char_2_string(std::vector<char>& src, std::string& des) {
  std::stringstream contents;
  std::vector<char>::iterator it = src.begin();
  
  for (; it != src.end(); it++) {
    contents << *it;
  }
  
  des = contents.str();
}

void print_contents(std::vector<char>& buf) {
  std::stringstream ss;
  std::cout << "content :" << std::endl;
  std::vector<char>::iterator it = buf.begin();
  
  for (; it != buf.end(); it++) {
    ss << *it;
  }
  
  // string模式打印文本内容 有乱码
  bool use_string_mode_print = false;
  
  if (use_string_mode_print) {
    std::cout << ss.str();
    std::cout << std::endl;
  } else {
    // 使用 wstring 打印内容;
    std::wstring wss = boost::locale::conv::utf_to_utf<wchar_t>(ss.str());
    std::wcout << wss;
    std::wcout << std::endl;
  }
}

void read_content_from_file1(FILE* fp, std::vector<char>& buf) {
  int c;
  
  while ((c = std::fgetc(fp)) != EOF) {
    buf.push_back(c);
    // std::putchar(c);
  }
  
  print_contents(buf);
}

void read_content_from_file2(FILE* fp, std::vector<char>& buf,
                             int content_size) {
  buf.resize(content_size);
  std::fseek(fp, 0, SEEK_SET);
  fread(&buf[0], sizeof(buf[0]), buf.size(), fp);
  print_contents(buf);
}

std::string read_whole_conent_from_file(std::string file_path) {
  FILE* file = fopen(file_path.c_str(), "rb");
  
  if (!file) {
    return std::string("");
  }
  
  fseek(file, 0, SEEK_END); // 寻位到结尾
  long size = ftell(file);
  fseek(file, 0, SEEK_SET); // 寻位到起始
  std::string text;
  char* buffer = new char[size + 1];
  buffer[size] = 0;
  
  if (fread(buffer, 1, size, file) == (unsigned long)size) {
    text = buffer;
  }
  
  fclose(file);
  delete[] buffer;
  const std::wstring wstr = boost::locale::conv::utf_to_utf<wchar_t>(text);
  return text;
}

void write_contents_2_file(std::string file_name, FILE* fp,
                           std::string contents) {
  if (!fp) {
    return;
  }
  
  fwrite(contents.c_str(), 1, contents.size(), fp);
  fclose(fp);
}

void test_wstring_string() {
  std::wstring wss(L"房间是的");
  std::wcout << wss << std::endl;
  std::string ss("房间是");
  std::cout << ss << std::endl;
}

bool test_c_style_io() {
  //test_wstring_string();
  //要使用 wcout打印中文，必须设置，默认不输出中文
  setlocale(LC_ALL, "chs");
  std::vector<char> buf;
  /*
  ** 读取文件内容
  */
  std::string file_name("reader.txt");
  // 1.方法1
  {
    FILE* fpr = fopen(file_name.c_str(), "r");
    
    if (fpr) {
      read_content_from_file1(fpr, buf);
      buf.clear();
      read_content_from_file2(fpr, buf, 79);
    }
    
    fclose(fpr);
  }
  // 2.方法2 计算文本长度，整块读取
  read_whole_conent_from_file(file_name);
  /*
  ** 向文件写数据
  */
  {
    std::string write_file("writer.txt");
    FILE* fpw = fopen(write_file.c_str(), "w");
    
    if (fpw) {
      std::string writes;
      conver_vec_char_2_string(buf, writes);
      write_contents_2_file(write_file, fpw, writes);
    }
    
    fclose(fpw);
  }
  return true;
}