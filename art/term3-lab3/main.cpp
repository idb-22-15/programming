#include "src/Parser.cpp"
#include "src/utils/colors.cpp"
#include "src/utils/io.cpp"

void print_unexpected_token_error(const std::string& input,
                                  const UnexpectedToken& e) {
  Token tok = e.received;
  size_t lines_between_error = 2;
  size_t start_line = tok.position.line <= lines_between_error
                          ? 1
                          : tok.position.line - lines_between_error;
  size_t end_line = tok.position.line + lines_between_error;

  bool is_line_start = true;
  size_t current_line = 1;
  for (size_t i = 0; i < input.length(); i++) {
    bool is_between = current_line >= start_line && current_line <= end_line;
    bool is_error_line = current_line == tok.position.line;
    if (is_between) {
      if (is_line_start) {
        if (is_error_line)
          std::cout << std::to_string(tok.position.line) << "\t| ";
        else
          std::cout << "\t| ";
      }

      if (i >= tok.position.start && i < tok.position.end)
        std::cout << colorized_string(input.substr(i, 1), Color::red);
      else
        std::cout << colorized_string(input.substr(i, 1), Color::yellow);
    }

    is_line_start = false;
    if (input[i] == '\n') {
      current_line++;
      is_line_start = true;
    }
  }
  std::cout << std::endl;
}

void parse_text(const std::string& input) {
  Parser parser;
  try {
    parser.parse(input);
    std::cout << colorized_string("ok", Color::green) << std::endl;
  } catch (const UnexpectedToken& e) {
    std::cout << colorized_string("error", Color::red) << std::endl;
    std::cerr << e.what() << std::endl;
    print_unexpected_token_error(input, e);
  }
};

void parse_file(const std::string& filename) {
  std::cout << colorized_string("parse ", Color::blue) << filename << ": ";
  try {
    parse_text(read_file(filename));
  } catch (const std::exception& e) {
    std::cout << colorized_string("error", Color::red) << std::endl;
    std::cerr << e.what() << std::endl;
  }
}

void run_tests() {
  parse_file("./__tests__/test-empty.txt");
  parse_file("./__tests__/test-var-declaration.txt");
  parse_file("./__tests__/test-var-declaration-invalid-const.txt");
  parse_file("./__tests__/test-var-declaration-invalid-void.txt");
  parse_file("./__tests__/test-expression.txt");
  parse_file("./__tests__/test-function-declaration.txt");
  parse_file(
      "./__tests__/"
      "test-function-declaration-invalid-args-default-value-order.txt");

  parse_file("./__tests__/test-class-constructor-with-init-list.txt");
  parse_file("./__tests__/test-class-destructor.txt");
  parse_file("./__tests__/test-class-declaration.txt");
  parse_file("./__tests__/test-class-access-modifiers.txt");
  parse_file("./__tests__/test-class-invalid-access-modifier.txt");
  parse_file("./__tests__/test-class-invalid-constructor-name.txt");
  parse_file("./__tests__/test-class-invalid-destructor-name.txt");
  parse_file("./__tests__/test-class-invalid-end.txt");

  parse_file("does-not-exit.txt");
}

void parse_console_input() {
  while (true) {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);
    parse_text(input);
  }
}

int main(int argc, char** argv) {
  if (argc == 1) {
    run_tests();
    parse_console_input();
  }

  else if (argc == 2) {
    parse_file(argv[1]);
  }

  else if (argc > 2) {
    std::cout << "usage: <filename>" << std::endl;
    exit(1);
  }
}