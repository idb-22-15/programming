#pragma once
#include <exception>
#include <experimental/optional>
#include <map>
#include <string>
#include "Lexer.cpp"
#include "node-types.cpp"

class Parser {
 private:
  std::vector<Token> tokens;
  Lexer lexer;

 public:
  Program parse(std::string input) {
    this->lexer.init(input);
    this->tokens = this->lexer.tokenize();

    Program program;

    while (!this->eof()) {
      program.body.push_back(this->parse_statement());
    }
    return program;
  }

 private:
  bool eof() { return this->at().type == TokenType::eof; }

  Token at() { return this->tokens[0]; }

  Token eat() {
    Token tok = this->tokens.front();
    this->tokens.erase(this->tokens.begin());
    return tok;
  }

  Token expect(TokenType type) {
    Token tok = this->eat();
    if (tok.type != type)
      throw UnexpectedToken(type, tok);
    return tok;
  }

  // void require2(TokenType type1, TokenType type2) {
  //   if (this->at().type != type1 && this->at().type != type2)
  //     throw UnexpectedToken(type, this->at());
  // }

  Statement parse_statement() {
    switch (this->at().type) {
      case TokenType::consttok:
      case TokenType::inttok:
      case TokenType::floattok:
      case TokenType::doubletok:
      case TokenType::chartok:
      case TokenType::booltok:
      case TokenType::autotok:
        return this->parse_var_declaration();
      default:
        return this->parse_expr();
        // throw UnexpectedToken(this->at());
    };

    // this->parse_expr();
  }

  Statement parse_var_declaration() {
    TokenType type = this->at().type;
    bool is_const = false;
    if (type == TokenType::consttok) {
      is_const = true;
      this->eat();
      type = this->at().type;
    }

    switch (type) {
      case TokenType::inttok:
      case TokenType::floattok:
      case TokenType::doubletok:
      case TokenType::chartok:
      case TokenType::booltok:
      case TokenType::autotok: {
        this->eat();
        std::string ident = this->expect(TokenType::ident).literal;
        switch (this->at().type) {
          case TokenType::semicolon:
            this->eat();
            return VarDeclaration(is_const, ident, std::experimental::nullopt);
          case TokenType::eql: {
            this->eat();
            Expr value = this->parse_expr();
            this->expect(TokenType::semicolon);
            return VarDeclaration(is_const, ident, value);
          }
          default:
            throw UnexpectedToken(this->at());
        }
      }
      default:
        throw UnexpectedToken(this->at());
    };
  }

  Expr parse_expr() { return this->parse_additive_expr(); };

  Expr parse_additive_expr() {
    Expr left = this->parse_multiplicative_expr();
    TokenType op = this->at().type;
    while (op == TokenType::plus || op == TokenType::minus) {
      op = this->eat().type;
      Expr right = this->parse_multiplicative_expr();
      left = BinaryExpr(left, right, op);
    }
    return left;
  }

  Expr parse_multiplicative_expr() {
    Expr left = this->parse_primary_expr();
    TokenType op = this->at().type;
    while (op == TokenType::asteriks || op == TokenType::slash ||
           op == TokenType::persent) {
      op = this->eat().type;
      Expr right = this->parse_primary_expr();
      left = BinaryExpr(left, right, op);
    }
    return left;
  }

  Expr parse_primary_expr() {
    switch (this->at().type) {
      case TokenType::number:
        return NumericLiteral(std::stod(this->eat().literal));
      case TokenType::charlit:
        return CharLiteral(std::stoi(this->eat().literal));
      case TokenType::string:
        return StringLiteral(this->eat().literal);
      case TokenType::lparen: {
        this->eat();
        Expr value = this->parse_expr();
        this->expect(TokenType::rparen);
        return value;
      }
      default:
        throw UnexpectedToken(this->at());
    }
  }

  void parse_constructor() { expect(TokenType::ident); }

  void parse_args() {
    expect(TokenType::lparen);

    while (this->at().type != TokenType::rparen) {
    }
  }
};