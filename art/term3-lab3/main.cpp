#include <fstream>
#include <iostream>

#include "./src/Parser.cpp"

enum class Color {
  red = 31,
  green = 32,
  yellow = 33,
  blue = 34,
  magenta = 35,
  cyan = 36
};

std::string colorized_string(const std::string& str, Color color_code) {
  std::string new_str =
      "\033[" + std::to_string(int(color_code)) + "m" + str + "\033[0m";
  return new_str;
}

void print_unexpected_token_error(const std::string& input,
                                  const UnexpectedToken& e) {
  Token tok = e.received;
  for (size_t i = 0; i < input.length(); i++) {
    if (i >= tok.position.start && i < tok.position.end)
      std::cout << colorized_string(input.substr(i, 1), Color::red);
    else
      std::cout << colorized_string(input.substr(i, 1), Color::yellow);
  }
  std::cout << std::endl;
}

void parse_or_print_error(const std::string& input) {
  Parser parser;
  try {
    parser.parse(input);
    std::cout << "ok" << std::endl;
  } catch (const UnexpectedToken& e) {
    std::cerr << e.what() << std::endl;
    print_unexpected_token_error(input, e);
  }
};

int main(int argc, char** argv) {
  if (argc == 1) {
    parse_or_print_error("int x = 5;");
    parse_or_print_error("int abs(float c, bool y){};");
    parse_or_print_error(
        "class Cat{ bool is_meow = true;  Cat(bool can_meow = true): "
        "is_meow(can_meow) {} };");

    while (true) {
      std::cout << "> ";
      std::string input;
      std::getline(std::cin, input);
      parse_or_print_error(input);
    }
  }

  else if (argc == 2) {
    std::ifstream file(argv[1]);
    if (file) {
      std::stringstream buffer;
      buffer << file.rdbuf();
      std::string test_string = buffer.str();
      parse_or_print_error(test_string);
      exit(0);
    } else {
      std::cerr << "error opening the file" << std::endl;
    }
  }

  else if (argc > 2) {
    std::cout << "usage: <filename>";
    exit(1);
  }
}