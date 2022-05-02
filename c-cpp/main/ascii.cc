#include <cstring>
#include <fstream>
#include <iostream>

void show_help(const char *cmd) {
  std::cout << "Description: print hex representation of ascii characters"
            << std::endl;
  std::cout << "Usage: " << cmd << " [file]" << std::endl;
}

int main(const int argc, const char *argv[]) {
  std::istream *in = &std::cin;
  if (argc == 2) {
    in = new std::ifstream(argv[1], std::ifstream::in);
    if (!strcmp("-h", argv[1]) || in->bad()) {
      show_help(argv[0]);
      return 1;
    }
  } else if (argc != 1) {
    show_help(argv[0]);
    return 1;
  }

  std::string s;

  while (*in >> s) {
    for (const auto ch : s) {
      std::cout << std::hex << (int)ch << ' ';
    }
    std::cout << std::endl;
  }
}