#include <iostream>
#include "./src/Parser.cpp"

int main() {
  Parser parser;

  try {
    parser.parse("int abs = 4; int b;");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
