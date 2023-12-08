#include <iostream>
#include <exception>
#include "./src/Lexer.cpp"

enum class NodeType {
  program,
  numeric_literal,
  identifier,
  binary_expr,
};

class UnexpectedToken: public std::exception {
  TokenType expected;
  Token received;

  public:

  UnexpectedToken(TokenType expected, Token received): received(received) {
    this->expected = expected;
  }

  virtual const char* what() const throw() {
    std::string message = "Expected: " + Token::printable_literals.at(expected) + " , received: " + this->received.literal;
    return message.c_str();
  }
};

// class Parser {
//   std::string input;
//   Lexer lexer;
//   Token lookahead;

// public:
//   void parse(std::string input) {
//     this->input = input;
//     this->lexer.init(input);
//     this->lookahead = this->lexer.next();

//     return this->Program();
//   }

//   void require1(TokenType type) {
//     if (this->lookahead.type != type) throw "r";
//   }

//   void Program() {
//     return this->NumericLiteral();
//   };

//   void NumericLiteral() {
//     require1(TokenType::number);

//   }
// };


int main() {
  Lexer lexer;
  lexer.init("! & | ~ ^ int a = 5.64; float b = 4; class Foo { Foo(int a, bool b): aa(a), bb(b)}");
  std::vector<Token> tokens = lexer.tokenize();

  for(auto tok : tokens) {
    if (tok.type_printable.length() == 1) 
      std::cout << "type: " << tok.type_printable << "\t\t literal: " << tok.literal << "\t position: " << tok.position.start << std::endl; 
    else
      std::cout << "type: " << tok.type_printable << "\t literal: " << tok.literal << "\t position: " << tok.position.start << std::endl; 
  }
}

