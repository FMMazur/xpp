#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

#include "lexer.hxx"
#include "token.hxx"
#include "parser.hxx"

int main(int argc, char** argv) {
  std::ifstream file(argv[1]);

  if (!file.is_open()) {
    std::cout << "File not found!" << std::endl;
  }

  std::stringstream ss;
  ss << file.rdbuf();

  std::string program = ss.str();
  xpp::Parser parser{program};

  parser.run();

  return 0;
}
