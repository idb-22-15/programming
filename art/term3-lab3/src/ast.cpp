#pragma once
#include <experimental/optional>
#include <map>
#include <string>
#include <variant>

#include "Token.cpp"

enum class NodeType {
  // statements
  program,
  var_declaration,
  function_declaration,
  class_declaration,

  // expressions
  binary_expr,
  assignment_expr,
  identifier,
  numeric_literal,
  char_literal,
  bool_literal,
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
    {NodeType::class_declaration, "class_declaration"},

    {NodeType::binary_expr, "binary_expr"},
    {NodeType::assignment_expr, "assignment_expr"},
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

class AssignmentExpr : public Expr {
 public:
  const NodeType type = NodeType::assignment_expr;
  Expr assigne;
  Expr value;
  AssignmentExpr(Expr assigne, Expr value) : assigne(assigne), value(value) {}
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

class BoolLiteral : public Expr {
 public:
  const NodeType type = NodeType::bool_literal;
  const bool value;
  BoolLiteral(bool value) : value(value) {}
};

class Declaration : public Statement {};

class VarType {
 public:
  TokenType type;
  bool is_const = false;
  bool is_signed = true;
  VarType(TokenType type, bool is_const = false, bool is_signed = true)
      : is_const(is_const), is_signed(is_signed) {}
};

class VarDeclaration : public Declaration {
 public:
  const NodeType type = NodeType::var_declaration;
  VarType var_type;
  std::string identifier;
  std::experimental::optional<Expr> value;
  VarDeclaration(VarType var_type,
                 std::string identifier,
                 std::experimental::optional<Expr> value)
      : var_type(var_type), identifier(identifier), value(value) {}
};

class FunctionDeclaration : public Declaration {
 public:
  const NodeType type = NodeType::function_declaration;
  VarType return_type;
  std::string identifier;
  std::vector<VarDeclaration> params;
  std::experimental::optional<std::vector<Statement>> body;
  FunctionDeclaration(VarType return_type,
                      std::string identifier,
                      std::vector<VarDeclaration> params,
                      std::experimental::optional<std::vector<Statement>> body)
      : return_type(return_type),
        identifier(identifier),
        params(params),
        body(body) {}
};

enum class AccessModifier {
  publicmod,
  privatemod,
  protectedmod,
};
class ClassItem {
 public:
  AccessModifier mod;
  Declaration item;
  ClassItem(AccessModifier mod, Declaration item) : mod(mod), item(item) {}
};

class ClassDeclaration : public Declaration {
 public:
  const NodeType type = NodeType::class_declaration;
  std::string identifier;
  std::vector<ClassItem> items;
  ClassDeclaration(std::string identifier, std::vector<ClassItem> items)
      : identifier(identifier), items(items) {}
};
