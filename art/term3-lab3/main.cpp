#include <exception>
#include <experimental/optional>
#include <iostream>
#include <string>
#include "./src/Lexer.cpp"

enum class NodeType {
  // statements
  program,
  var_declaration,

  // expressions
  binary_expr,
  identifier,
  numeric_literal,
  string_literal
};

class Statement {
 public:
  NodeType type;
};

class Program : public Statement {
 public:
  const NodeType type = NodeType::program;
  std::vector<Statement> body;
};

class Expr : public Statement {};
class BinaryExpr : public Expr {
 public:
  const NodeType type = NodeType::binary_expr;
  Expr left;
  Expr right;
  TokenType op;
};

class Identifier : public Expr {
 public:
  const NodeType type = NodeType::identifier;
  std::string symbol;
};

class StringLiteral : public Expr {
 public:
  const NodeType type = NodeType::string_literal;
  std::string string;
  StringLiteral(std::string string) : string(string) {}
};

class NumericLiteral : public Expr {
 public:
  const NodeType type = NodeType::numeric_literal;
  const double value;
  NumericLiteral(double value) : value(value) {}
};

class VarDeclaration {
 public:
  const NodeType type = NodeType::var_declaration;
  bool constant;
  std::string identifier;
  std::experimental::optional<Expr> value;
};

class UnexpectedToken : public std::exception {
  std::experimental::optional<TokenType> expected;
  Token received;
  std::string message;

 public:
  UnexpectedToken(Token received) : received(received) {
    this->message = "Unexpected token";
    this->message += "; received type: " + this->received.type_printable +
                     ", literal: " + this->received.literal + ", start: " +
                     std::to_string(this->received.position.start);
  }

  UnexpectedToken(TokenType expected, Token received) : received(received) {
    this->expected = std::experimental::make_optional(expected);
    this->message = "Expected type: " + Token::printable_literals.at(expected) +
                    "; received type: " + this->received.type_printable +
                    ", literal: " + this->received.literal +
                    ", start: " + std::to_string(this->received.position.start);
  }

  virtual const char* what() const throw() { return this->message.c_str(); }
};

class Parser {
  std::vector<Token> tokens;

  Lexer lexer;

  bool eof() { return this->at().type == TokenType::eof; }

  Token at() { return this->tokens[0]; }

  Token eat() {
    Token tok = this->tokens.front();
    this->tokens.erase(this->tokens.begin());
    return tok;
  }

 public:
  void parse(std::string input) {
    this->lexer.init(input);
    this->tokens = this->lexer.tokenize();

    return this->parse_program();
  }

  void expect(TokenType type) {
    if (this->at().type != type)
      throw UnexpectedToken(type, this->at());
  }

  // void require2(TokenType type1, TokenType type2) {
  //   if (this->at().type != type1 && this->at().type != type2)
  //     throw UnexpectedToken(type, this->at());
  // }

  void parse_program() { return this->parse_expr(); };

  void parse_statement() { this->parse_expr(); }

  Expr parse_expr() { this->parse_additive_expr(); };

  Expr parse_additive_expr() {
    this->parse_multiplicative_expr();
    TokenType op = this->at().type;

    while (op == TokenType::plus || op == TokenType::minus) {
      op = this->eat().type;
      this->parse_multiplicative_expr();
    }
  }

  Expr parse_multiplicative_expr() {
    Expr left = this->parse_primary_expr();
    TokenType op = this->at().type;
    while (op == TokenType::asteriks || op == TokenType::slash ||
           op == TokenType::persent) {
      op = this->eat().type;

      this->parse_primary_expr();
    }
  }

  Expr parse_primary_expr() {
    TokenType type = this->at().type;
    switch (type) {
      case TokenType::number:
        return NumericLiteral(std::stod(this->eat().literal));
      case TokenType::string:
        return StringLiteral(this->eat().literal);
      case TokenType::lparen:
        this->eat();
        Expr value = this->parse_expr();
        this->expect(TokenType::rparen);
        return value;
    }
    throw UnexpectedToken(this->at());
  }

  void parse_constructor() { expect(TokenType::ident); }

  void parse_args() {
    expect(TokenType::lparen);

    while (this->at().type != TokenType::rparen) {
    }
  }
};

int main() {
  Parser parser;

  try {
    parser.parse("(4 + 2) / 3 + 8");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  // Lexer lexer;
  // lexer.init(
  //     "! & | ~ ^ int a = 5.64; float b = 4; class Foo { Foo(int a, bool b): "
  //     "aa(a), bb(b)}");
  // std::vector<Token> tokens = lexer.tokenize();

  // for (auto tok : tokens) {
  //   if (tok.type_printable.length() == 1)
  //     std::cout << "type: " << tok.type_printable
  //               << "\t\t literal: " << tok.literal
  //               << "\t position: " << tok.position.start << std::endl;
  //   else
  //     std::cout << "type: " << tok.type_printable
  //               << "\t literal: " << tok.literal
  //               << "\t position: " << tok.position.start << std::endl;
  // }
}
