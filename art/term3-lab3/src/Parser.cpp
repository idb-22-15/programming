#pragma once
#include <exception>
#include <experimental/optional>
#include <map>
#include <string>
#include "Lexer.cpp"
#include "UnexpectedToken.cpp"
#include "ast.cpp"
class Parser {
 private:
  std::vector<Token> tokens;
  Lexer lexer;

 public:
  Program parse(std::string input) {
    this->lexer.init(input);
    this->tokens = this->lexer.tokenize();

    std::vector<Statement> body;
    while (!this->eof()) {
      body.push_back(this->parse_statement());
    }
    return Program(body);
  }

 private:
  bool eof() { return this->at().type == TokenType::eof; }
  bool eof_or_illegal() {
    return this->at().type == TokenType::eof ||
           this->at().type == TokenType::illegal;
  }

  Token at() { return this->tokens[0]; }

  void unget(Token tok) { this->tokens.insert(this->tokens.begin(), tok); }

  Token eat() {
    Token tok = this->tokens.front();
    this->tokens.erase(this->tokens.begin());
    return tok;
  }

  Token expect(const TokenType& type) {
    Token tok = this->eat();
    if (tok.type != type)
      throw UnexpectedToken(type, tok);
    return tok;
  }

  Token expect(const TokenType& type1, const TokenType& type2) {
    Token tok = this->eat();
    if (tok.type != type1 && tok.type != type2)
      throw UnexpectedToken(
          tok, "Expected type: " + Token::token_types_printable.at(type1) +
                   " or " + Token::token_types_printable.at(type2));
    return tok;
  }

  Token expect(const TokenType& type1,
               const TokenType& type2,
               const TokenType& type3) {
    Token tok = this->eat();
    if (tok.type != type1 && tok.type != type2 && tok.type != type3)
      throw UnexpectedToken(
          tok, "Expected type: " + Token::token_types_printable.at(type1) +
                   " or " + Token::token_types_printable.at(type2) + " or " +
                   Token::token_types_printable.at(type3));
    return tok;
  }

  Statement parse_statement() {
    switch (this->at().type) {
      case TokenType::statictok:
      case TokenType::consttok:
      case TokenType::autotok:
      case TokenType::voidtok:
      case TokenType::unsignedtok:
      case TokenType::inttok:
      case TokenType::floattok:
      case TokenType::doubletok:
      case TokenType::chartok:
      case TokenType::booltok:
        return this->parse_declaration();
      case TokenType::classtok:
      case TokenType::structtok:
        return this->parse_class_declaration();
      case TokenType::lsquirly:
        return this->parse_block_statement();
      case TokenType::returntok:
        return this->parse_return_statement();
      case TokenType::semicolon: {
        this->eat();
        return Statement();
      }
      default:
        Expr value = this->parse_expr();
        this->expect(TokenType::semicolon);
        return value;
    };
  }

  BlockStatement parse_block_statement() {
    this->expect(TokenType::lsquirly);
    std::vector<Statement> body;
    while (this->at().type != TokenType::rsquirly) {
      body.push_back(this->parse_statement());
      if (this->eof_or_illegal())
        throw UnexpectedToken(this->at(), "Parse block statement body");
    }
    this->expect(TokenType::rsquirly);
    return BlockStatement(body);
  }

  ReturnStatement parse_return_statement() {
    this->expect(TokenType::returntok);
    Expr value = this->parse_expr();
    this->expect(TokenType::semicolon);
    return ReturnStatement(value);
  }

  Declaration parse_declaration() {
    VarType var_type = this->parse_var_type();
    Token identtok = this->expect(TokenType::ident);

    switch (this->at().type) {
      case TokenType::semicolon:
      case TokenType::eql:
        return this->parse_var_declaration(var_type, identtok);
      case TokenType::lparen:
        return this->parse_function_declaration(var_type, identtok.literal);
      default:
        throw UnexpectedToken(this->at(),
                              "Expected type: semicolon, eql or lparen");
    }
  }

  VarType parse_var_type() {
    bool is_static = false;
    bool is_const = false;
    bool is_signed = true;
    if (this->at().type == TokenType::statictok) {
      this->eat();
      is_static = true;
    }

    if (this->at().type == TokenType::consttok) {
      this->eat();
      is_const = true;
    }

    if (this->at().type == TokenType::unsignedtok) {
      this->eat();
      is_signed = false;
    }

    switch (this->at().type) {
      case TokenType::voidtok:
      case TokenType::inttok:
      case TokenType::chartok:
      case TokenType::floattok:
      case TokenType::doubletok:
      case TokenType::booltok: {
        Token tok = this->eat();
        if (!is_signed &&
            !(tok.type == TokenType::inttok || tok.type == TokenType::chartok ||
              tok.type == TokenType::booltok))
          throw UnexpectedToken(this->at(), "Type cannot be unsigned");
        if (this->at().type == TokenType::ident)
          return VarType(tok.type, is_static, is_const, is_signed);
        throw UnexpectedToken(TokenType::ident, this->at());
      }
      default:
        throw UnexpectedToken(this->at(), "Parse variable type");
    }
  }

  VarDeclaration parse_var_declaration(VarType var_type, Token identtok) {
    switch (this->at().type) {
      case TokenType::semicolon: {
        this->eat();
        if (var_type.type == TokenType::voidtok)
          throw UnexpectedToken(identtok, "Variable cannot be of type void");
        if (var_type.is_const)
          throw UnexpectedToken(identtok,
                                "Must assign value to constant expression");
        return VarDeclaration(var_type, identtok.literal,
                              std::experimental::nullopt);
      }
      case TokenType::eql: {
        this->eat();
        Expr expr = this->parse_expr();
        //! FIXME
        switch (expr.type) {
          case NodeType::numeric_literal: {
            if (var_type.type != TokenType::inttok &&
                var_type.type != TokenType::floattok &&
                var_type.type != TokenType::doubletok &&
                var_type.type != TokenType::chartok)
              throw UnexpectedToken(
                  this->at(),
                  "Cannot assing number to variable with such type");
          }
          case NodeType::char_literal: {
            if (var_type.type != TokenType::inttok &&
                var_type.type != TokenType::chartok)
              throw UnexpectedToken(
                  this->at(),
                  "Cannot assing char literal to variable with such type");
          }
          case NodeType::bool_literal: {
            if (var_type.type != TokenType::booltok)
              throw UnexpectedToken(this->at(), "Variable must be type bool");
          }
          case NodeType::string_literal: {
            throw UnexpectedToken(this->at(), "Cannot assing string literal");
          }
          default:
            break;
        }

        this->expect(TokenType::semicolon);
        return VarDeclaration(var_type, identtok.literal, expr);
      }
      default:
        throw UnexpectedToken(this->at(), "Parse var declaration");
    }
  }

  Declaration parse_function_declaration(VarType return_type,
                                         const std::string& identifier) {
    std::vector<VarDeclaration> params = this->parse_args();

    switch (this->at().type) {
      case TokenType::semicolon:
        this->eat();
        return FunctionDeclaration(return_type, identifier, params,
                                   std::experimental::nullopt);
      case TokenType::lsquirly: {
        std::vector<Statement> body = this->parse_function_body();
        return FunctionDeclaration(return_type, identifier, params, body);
      }
      default:
        throw UnexpectedToken(this->at(), "Parse function declaration");
    }
  }

  std::vector<Statement> parse_function_body() {
    this->expect(TokenType::lsquirly);
    std::vector<Statement> body;

    while (this->at().type != TokenType::rsquirly) {
      body.push_back(this->parse_statement());
      if (this->eof_or_illegal())
        throw UnexpectedToken(this->at(), "Parse function body");
    }
    this->expect(TokenType::rsquirly);
    return body;
  }

  Expr parse_expr() { return this->parse_assignment_expr(); };

  AssignmentExpr parse_assignment_expr() {
    Expr left = this->parse_additive_expr();

    if (this->at().type == TokenType::eql) {
      this->eat();
      Expr value = this->parse_assignment_expr();
      return AssignmentExpr(left, value);
    }

    return left;
  }

  BinaryExpr parse_additive_expr() {
    Expr left = this->parse_multiplicative_expr();
    while (this->at().type == TokenType::plus ||
           this->at().type == TokenType::minus) {
      TokenType op = this->eat().type;
      Expr right = this->parse_multiplicative_expr();
      left = BinaryExpr(left, right, op);
    }
    return left;
  }

  BinaryExpr parse_multiplicative_expr() {
    Expr left = this->parse_primary_expr();
    while (this->at().type == TokenType::asteriks ||
           this->at().type == TokenType::slash ||
           this->at().type == TokenType::persent) {
      TokenType op = this->eat().type;
      Expr right = this->parse_primary_expr();
      left = BinaryExpr(left, right, op);
    }
    return left;
  }

  Expr parse_primary_expr() {
    Token tok = this->eat();
    switch (tok.type) {
      case TokenType::ident:
        return Identifier(tok.literal);
      case TokenType::number:
        return NumericLiteral(std::stod(tok.literal));
      case TokenType::charlit:
        return CharLiteral(tok.literal.at(1));
      case TokenType::truetok:
      case TokenType::falsetok: {
        bool value = tok.type == TokenType::truetok ? true : false;
        return BoolLiteral(value);
      }
      case TokenType::string: {
        return StringLiteral(tok.literal.substr(1, tok.literal.length() - 2));
      }
      case TokenType::lparen: {
        Expr value = this->parse_expr();
        this->expect(TokenType::rparen);
        return value;
      }
      default:
        throw UnexpectedToken(this->at(), "Parse primary expr");
    }
  }

  std::vector<VarDeclaration> parse_args() {
    std::vector<VarDeclaration> args;
    this->expect(TokenType::lparen);
    if (this->at().type != TokenType::rparen)
      args = this->parse_args_list();
    this->expect(TokenType::rparen);
    return args;
  }

  std::vector<VarDeclaration> parse_args_list() {
    std::vector<VarDeclaration> args;
    args.push_back(this->parse_args_list_item());
    while (this->at().type == TokenType::comma) {
      this->eat();
      VarDeclaration item = this->parse_args_list_item();
      if (!item.value && args.back().value)
        throw UnexpectedToken(this->at(),
                              "Args with default values must be in front");
      args.push_back(item);
      if (this->eof_or_illegal())
        throw UnexpectedToken(this->at(), "Parse args list");
    }
    return args;
  }

  VarDeclaration parse_args_list_item() {
    VarType var_type = this->parse_var_type();
    Token identtok = this->expect(TokenType::ident);

    if (this->at().type == TokenType::eql) {
      this->eat();
      Expr value = this->parse_expr();
      return VarDeclaration(var_type, identtok.literal,
                            std::experimental::make_optional(value));
    }

    return VarDeclaration(var_type, identtok.literal,
                          std::experimental::nullopt);
  }

  ClassDeclaration parse_class_declaration() {
    Token classtok = this->expect(TokenType::classtok, TokenType::structtok);
    Token ident = this->expect(TokenType::ident);
    std::vector<ClassParent> parents = this->parse_class_parents_list();

    this->expect(TokenType::lsquirly);
    std::vector<ClassItem> items;
    AccessModifier current_mode = classtok.type == TokenType::classtok
                                      ? AccessModifier::privatemod
                                      : AccessModifier::publicmod;

    while (this->at().type != TokenType::rsquirly) {
      switch (this->at().type) {
        case TokenType::ident: {
          FunctionDeclaration constructor =
              this->parse_constructor(ident.literal);
          items.push_back(ClassItem(current_mode, constructor));
          break;
        }
        case TokenType::bitnot: {
          FunctionDeclaration destructor =
              this->parse_dectructor(ident.literal);
          items.push_back(ClassItem(current_mode, destructor));
          break;
        }
        case TokenType::publictok:
        case TokenType::privatetok:
        case TokenType::protectedtok: {
          current_mode = this->parse_class_item_access_modifier();
          break;
        }
        case TokenType::classtok:
        case TokenType::structtok: {
          Declaration class_declaration = this->parse_class_declaration();
          items.push_back(ClassItem(current_mode, class_declaration));
          break;
        }
        default:
          Declaration declaration = this->parse_declaration();
          items.push_back(ClassItem(current_mode, declaration));
      }
      if (this->eof_or_illegal())
        throw UnexpectedToken(this->at(), "Parse class body");
    }

    this->expect(TokenType::rsquirly);
    this->expect(TokenType::semicolon);
    return ClassDeclaration(ident.literal, parents, items);
  };

  std::vector<ClassParent> parse_class_parents_list() {
    std::vector<ClassParent> parents;
    if (this->at().type == TokenType::colon) {
      this->eat();
      do {
        Token modtok = this->expect(TokenType::publictok, TokenType::privatetok,
                                    TokenType::protectedtok);
        AccessModifier mod = modtok.type == TokenType::publictok
                                 ? AccessModifier::publicmod
                             : modtok.type == TokenType::privatetok
                                 ? AccessModifier::privatemod
                                 : AccessModifier::protectedmod;

        std::string parent_name = this->expect(TokenType::ident).literal;
        parents.push_back(ClassParent(mod, parent_name));
      } while (this->at().type == TokenType::comma &&
               this->eat().type == TokenType::comma);
    }
    return parents;
  }

  AccessModifier parse_class_item_access_modifier() {
    AccessModifier current_mode = AccessModifier::privatemod;
    Token modtok = this->expect(TokenType::publictok, TokenType::privatetok,
                                TokenType::protectedtok);
    if (modtok.type == TokenType::publictok)
      current_mode = AccessModifier::publicmod;
    else if (modtok.type == TokenType::privatetok)
      current_mode = AccessModifier::privatemod;
    else if (modtok.type == TokenType::protectedtok)
      current_mode = AccessModifier::protectedmod;

    this->expect(TokenType::colon);
    return current_mode;
  }

  FunctionDeclaration parse_constructor(const std::string& class_ident) {
    Token identtok = this->expect(TokenType::ident);
    if (identtok.literal != class_ident)
      throw UnexpectedToken(identtok, "Wrong constructor name");
    std::vector<VarDeclaration> args = this->parse_args();
    if (this->at().type == TokenType::colon)
      this->parse_constructor_init_list();
    std::vector<Statement> body = this->parse_function_body();
    return FunctionDeclaration(VarType(TokenType::voidtok), identtok.literal,
                               args, body);
  }

  void parse_constructor_init_list() {
    this->expect(TokenType::colon);
    while (this->at().type != TokenType::lsquirly) {
      this->expect(TokenType::ident);

      this->expect(TokenType::lparen);
      this->expect(TokenType::ident);
      this->expect(TokenType::rparen);
      if (this->at().type == TokenType::comma)
        this->eat();
      if (this->eof_or_illegal())
        throw UnexpectedToken(this->at(), "Parse constructor init list");
    }
  }

  FunctionDeclaration parse_dectructor(const std::string& class_ident) {
    this->expect(TokenType::bitnot);
    Token identtok = this->expect(TokenType::ident);
    if (identtok.literal != class_ident)
      throw UnexpectedToken(identtok, "Wrong destructor name");
    this->expect(TokenType::lparen);
    this->expect(TokenType::rparen);
    std::vector<Statement> body = this->parse_function_body();
    return FunctionDeclaration(TokenType::voidtok, class_ident,
                               std::vector<VarDeclaration>(), body);
  }
};