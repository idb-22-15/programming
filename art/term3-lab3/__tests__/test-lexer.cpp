#include <fstream>
#include <iostream>
#include <sstream>
#include "../src/Lexer.cpp"

void println_token_info(Token tok) {
  if (tok.type_printable.length() > 9)
    std::cout << "type: " << tok.type_printable << "\t literal: " << tok.literal
              << "\t\t start: " << tok.position.start
              << "\tend: " << tok.position.end
              << "\tline: " << tok.position.line
              << "\tcol: " << tok.position.col << std::endl;
  else
    std::cout << "type: " << tok.type_printable
              << "\t\t literal: " << tok.literal
              << "\t\t start: " << tok.position.start
              << "\tend: " << tok.position.end
              << "\tline: " << tok.position.line
              << "\tcol: " << tok.position.col << std::endl;
}

void print_tokens(std::vector<Token> tokens) {
  for (auto tok : tokens) {
    println_token_info(tok);
  }
}

// void print_tokens_by_next(Lexer lexer) {
//   Token tok = lexer.next();
//   while (tok.type != TokenType::eof) {
//     println_token_info(tok);
//     tok = lexer.next();
//   }
// }

int main() {
  Lexer lexer;

  std::ifstream file("test-lexer.txt");
  if (file) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string test_string = buffer.str();
    // std::cout << test_string << std::endl;
    lexer.init(test_string);
    print_tokens(lexer.tokenize());
  } else {
    std::cerr << "Error opening the file" << std::endl;
  }

  lexer.init("int a = 5; const float b = 6.6; char* str = \"fggf\"");
  std::vector<Token> tokens = lexer.tokenize();
  print_tokens(tokens);
}
