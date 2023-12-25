#include "modules/Parser.cpp"

using std::vector;

void testLexicalAnalisis() {
  Lexer lexer;

  vector<Token> tokenList = lexer.lexicalAnalisis(
      "int // this is int\n arr[5][1] = {{3}, {2}, {13}, 4}; /*long*/");
  for (Token token : tokenList) {
    token.printToken();
  }
}

void testParser() {
  Parser parser;
  parser.parseFile("./__tests__/empty.txt");
  parser.parseFile("./__tests__/comments.txt");
  parser.parseFile("./__tests__/array.txt");
  parser.parseFile("./__tests__/array-invalid.txt");
  parser.parseFile("./__tests__/matrix.txt");
  parser.parseFile("./__tests__/matrix-invalid.txt");
  parser.parseFile("./__tests__/assign.txt");
  parser.parseFile("./__tests__/assign-invalid.txt");
}

int main(int argc, char** argv) {
  if (argc == 1)
    testParser();
  // int arr[2][2][2][2][2] = {{{{1, 2, 3, 4, 5, 6}, 3}, 4}};
  if (argc == 2) {
    Parser parser;
    parser.parseFile(argv[1]);
  }

  if (argc > 2) {
    std::cout << "Передайте путь до файла первым параметром" << std::endl;
    exit(1);
  }
}