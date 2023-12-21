#include "src/ParserIO.cpp"

void run_tests() {
  ParserIO::parse_file("./__tests__/empty.txt");

  ParserIO::parse_file("./__tests__/var-declaration.txt");
  ParserIO::parse_file(
      "./__tests__/var-declaration-invalid-literal-number.txt");
  ParserIO::parse_file("./__tests__/var-declaration-invalid-literal-char.txt");
  ParserIO::parse_file("./__tests__/var-declaration-invalid-literal-bool.txt");
  ParserIO::parse_file(
      "./__tests__/var-declaration-invalid-literal-string.txt");
  ParserIO::parse_file("./__tests__/var-declaration-invalid-const.txt");
  ParserIO::parse_file("./__tests__/var-declaration-invalid-void.txt");
  ParserIO::parse_file("./__tests__/function-declaration.txt");
  ParserIO::parse_file(
      "./__tests__/function-declaration-invalid-default-args-order.txt");
  ParserIO::parse_file("./__tests__/expression.txt");

  ParserIO::parse_file("./__tests__/class-declaration.txt");
  ParserIO::parse_file("./__tests__/class-constructor-with-init-list.txt");
  ParserIO::parse_file("./__tests__/class-destructor.txt");
  ParserIO::parse_file("./__tests__/class-access-modifiers.txt");
  ParserIO::parse_file("./__tests__/class-invalid-access-modifier.txt");
  ParserIO::parse_file("./__tests__/class-invalid-constructor-name.txt");
  ParserIO::parse_file("./__tests__/class-invalid-destructor-name.txt");
  ParserIO::parse_file("./__tests__/class-invalid-end.txt");

  ParserIO::parse_file("does-not-exit.txt");
}

int main(int argc, char** argv) {
  Parser parser;
  if (argc == 1) {
    run_tests();
    ParserIO::parse_console_input();
  }

  else if (argc == 2) {
    ParserIO::parse_file(argv[1]);
  }

  else if (argc > 2) {
    std::cout << "usage: <filename>" << std::endl;
    exit(1);
  }
}