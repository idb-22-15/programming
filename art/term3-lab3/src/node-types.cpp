#pragma once
#include <experimental/optional>
#include <map>
#include <string>

#include "Token.cpp"

enum class NodeType {
  // statements
  program,
  var_declaration,

  // expressions
  binary_expr,
  identifier,
  numeric_literal,
  char_literal,
  string_literal,
};

class Statement {
 public:
  NodeType type;
  static const std::map<NodeType, std::string> node_types_table_printable;
};

const std::map<NodeType, std::string> Statement::node_types_table_printable{
    {NodeType::program, "program"},
    {NodeType::var_declaration, "var_declaration"},

    {NodeType::binary_expr, "binary_expr"},
    {NodeType::identifier, "identifier"},
    {NodeType::numeric_literal, "numberic_literal"},
    {NodeType::char_literal, "char_literal"},
    {NodeType::string_literal, "string_literal"},
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
  BinaryExpr(Expr left, Expr right, TokenType op)
      : left(left), right(right), op(op) {}
};

class Identifier : public Expr {
 public:
  const NodeType type = NodeType::identifier;
  std::string symbol;
};

class StringLiteral : public Expr {
 public:
  const NodeType type = NodeType::string_literal;
  const std::string string;
  StringLiteral(std::string string) : string(string) {}
};

class NumericLiteral : public Expr {
 public:
  const NodeType type = NodeType::numeric_literal;
  const double value;
  NumericLiteral(double value) : value(value) {}
};

class CharLiteral : public Expr {
 public:
  const NodeType type = NodeType::char_literal;
  const char ch;
  CharLiteral(char ch) : ch(ch) {}
};

class VarDeclaration : public Statement {
 public:
  const NodeType type = NodeType::var_declaration;
  bool is_const;
  std::string identifier;
  std::experimental::optional<Expr> value;
  VarDeclaration(bool is_const,
                 std::string identifier,
                 std::experimental::optional<Expr> value)
      : is_const(is_const), identifier(identifier), value(value) {}
};

class UnexpectedToken : public std::exception {
 private:
  std::experimental::optional<TokenType> expected;
  Token received;
  std::string message;

 public:
  UnexpectedToken(Token received) : received(received) {
    this->message = "Unexpected token; ";
    this->message += "received type: " + this->received.type_printable +
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