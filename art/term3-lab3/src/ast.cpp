#pragma once
#include <experimental/optional>
#include <map>
#include <string>
#include <variant>

#include "Token.cpp"

enum class NodeType {
  // statements
  statement,
  program,
  block_statement,
  return_statement,
  if_statement,

  // declarations
  var_declaration,
  function_declaration,
  class_declaration,

  // expressions
  expr,
  binary_expr,
  assignment_expr,

  // literals
  identifier,
  numeric_literal,
  char_literal,
  bool_literal,
  string_literal,
};

class Statement {
 public:
  NodeType type = NodeType::statement;
  static const std::map<NodeType, std::string> node_types_table_printable;
};

const std::map<NodeType, std::string> Statement::node_types_table_printable{
    {NodeType::program, "program"},

    {NodeType::block_statement, "block_statement"},
    {NodeType::return_statement, "return_statement"},

    {NodeType::var_declaration, "var_declaration"},
    {NodeType::function_declaration, "function_declaration"},
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
  const std::vector<Statement> body;
  Program(std::vector<Statement> body) : body(body){};
};

class Expr : public Statement {
 public:
  NodeType type = NodeType::expr;
  virtual ~Expr() = default;
};

class BlockStatement : public Statement {
 public:
  const NodeType type = NodeType::block_statement;
  const std::vector<Statement> body;
  BlockStatement(std::vector<Statement> body) : body(body){};
};

class ReturnStatement : public Statement {
 public:
  const NodeType type = NodeType::return_statement;
  const Expr* value;
  ReturnStatement(Expr* value) : value(value) {}
};
class BinaryExpr : public Expr {
 public:
  const NodeType type = NodeType::binary_expr;
  const Expr* left;
  const Expr* right;
  const TokenType op;
  BinaryExpr(Expr* left, Expr* right, TokenType op)
      : left(left), right(right), op(op) {}
};

class IfStatement : public Statement {
 public:
  const NodeType type = NodeType::if_statement;
  const Expr* condition;
  const Statement* body;
  const Statement* else_body;
  IfStatement(Expr* condition, Statement* body, Statement* else_body)
      : condition(condition), body(body), else_body(else_body) {}
};

class AssignmentExpr : public Expr {
 public:
  const NodeType type = NodeType::assignment_expr;
  const Expr* assigne;
  const Expr* value;
  AssignmentExpr(Expr* assigne, Expr* value) : assigne(assigne), value(value) {}
};

class Identifier : public Expr {
 public:
  const NodeType type = NodeType::identifier;
  const std::string identifier;
  Identifier(std::string identifier) : identifier(identifier) {}
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
  const TokenType type;
  const bool is_static = false;
  const bool is_const = false;
  const bool is_signed = true;
  VarType(TokenType type,
          bool is_static = false,
          bool is_const = false,
          bool is_signed = true)
      : type(type),
        is_static(is_static),
        is_const(is_const),
        is_signed(is_signed) {}
};

class VarDeclaration : public Declaration {
 public:
  const NodeType type = NodeType::var_declaration;
  const VarType var_type;
  const std::string identifier;
  const std::experimental::optional<Expr*> value;
  VarDeclaration(VarType var_type,
                 std::string identifier,
                 std::experimental::optional<Expr*> value)
      : var_type(var_type), identifier(identifier), value(value) {}
};

class FunctionDeclaration : public Declaration {
 public:
  const NodeType type = NodeType::function_declaration;
  const VarType return_type;
  const std::string identifier;
  const std::vector<VarDeclaration> params;
  const std::experimental::optional<std::vector<Statement>> body;
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

class ClassParent {
 public:
  const AccessModifier mod;
  const std::string identifier;
  ClassParent(AccessModifier mod, std::string identifier)
      : mod(mod), identifier(identifier) {}
};

class ClassItem {
 public:
  const AccessModifier mod;
  const Declaration item;
  ClassItem(AccessModifier mod, Declaration item) : mod(mod), item(item) {}
};

class ClassDeclaration : public Declaration {
 public:
  const NodeType type = NodeType::class_declaration;
  const std::string identifier;
  const std::vector<ClassParent> parents;
  const std::vector<ClassItem> items;
  ClassDeclaration(std::string identifier,
                   std::vector<ClassParent> parents,
                   std::vector<ClassItem> items)
      : identifier(identifier), parents(parents), items(items) {}
};
