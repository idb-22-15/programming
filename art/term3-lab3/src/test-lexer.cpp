#include "Lexer.cpp"
#include "utils/io.cpp"

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
  std::string input = read_file("../__tests__/test-lexer.txt");
  lexer.init(input);
  print_tokens(lexer.tokenize());
}
