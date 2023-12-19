#include <fstream>
#include <iostream>

#include "./src/Parser.cpp"
#include "./src/colors.cpp"



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

std::string read_file_or_die(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "error opening the file" << std::endl;
    exit(1);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string file_content = buffer.str();
  return file_content;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    parse_or_print_error("int x = 5;");
    parse_or_print_error("int abs(float c, bool y){};");
    parse_or_print_error(
        "class Cat{ bool is_meow = true;  Cat(bool can_meow = true): "
        "is_meow(can_meow) {} };");
    parse_or_print_error(read_file_or_die("test-empty.txt"));
    parse_or_print_error(read_file_or_die("test-var-declaration.txt"));

    parse_or_print_error(read_file_or_die("test-class-declaration.txt"));
    parse_or_print_error(read_file_or_die("test-class-access-modifiers.txt"));
    parse_or_print_error(read_file_or_die("test-class-invalid-access-modifier.txt"));
    parse_or_print_error(read_file_or_die("test-class-invalid-constructor-name.txt"));
    parse_or_print_error(read_file_or_die("test-class-invalid-end.txt"));

    while (true) {
      std::cout << "> ";
      std::string input;
      std::getline(std::cin, input);
      parse_or_print_error(input);
    }
  }

  else if (argc == 2) {
    std::string file_content = read_file_or_die(argv[1]);
    parse_or_print_error(file_content);
  }

  else if (argc > 2) {
    std::cout << "usage: <filename>";
    exit(1);
  }
}