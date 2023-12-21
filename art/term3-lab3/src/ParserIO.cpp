#pragma once
#include "Parser.cpp"

class ParserIO {
 public:
  static void parse_text(const std::string& input) {
    Parser parser;
    std::vector<UnexpectedToken> errors;
    parser.parse(input, errors);

    if (!errors.empty()) {
      std::cout << colorized_string("error", Color::bright_red) << std::endl;
      for (auto e : errors) {
        std::cerr << e.what() << std::endl;
        e.print_error_in_context(input);
      }
    } else
      std::cout << colorized_string("ok", Color::green) << std::endl;
  };

  static void parse_file(const std::string& filename) {
    std::cout << colorized_string("parse ", Color::blue) << filename << ": ";
    try {
      ParserIO::parse_text(read_file(filename));
    } catch (const std::exception& e) {
      std::cout << colorized_string("error", Color::bright_red) << std::endl;
      std::cerr << e.what() << std::endl;
    }
  }

  static void parse_console_input() {
    while (true) {
      std::cout << "> ";
      std::string input;
      std::getline(std::cin, input);
      std::cout << colorized_string("parse ", Color::blue) << "console input: ";
      ParserIO::parse_text(input);
    }
  }
};