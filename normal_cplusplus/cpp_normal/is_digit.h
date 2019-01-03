#include "cplusplus_common_def.hpp"
//url:https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
//数组拷贝

bool is_digit() {
  std::string theInput;
  int inputAsInt;

  std::getline(std::cin, theInput);

  while (std::cin.fail() || std::cin.eof() ||
         theInput.find_first_not_of("0123456789") != std::string::npos) {

    std::cout << "Error" << std::endl;

    if (theInput.find_first_not_of("0123456789") == std::string::npos) {
      std::cin.clear();
      std::cin.ignore(256, '\n');
    }

    std::getline(std::cin, theInput);
  }

  std::string::size_type st;
  inputAsInt = std::stoi(theInput, &st);
  std::cout << inputAsInt << std::endl;
  return true;
}