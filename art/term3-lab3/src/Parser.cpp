#pragma once
#include <exception>
#include <experimental/optional>
#include <map>
#include <string>
#include "Lexer.cpp"
#include "ast.cpp"

class UnexpectedToken : public std::exception {
 public:
  Token received;

 private:
  std::experimental::optional<TokenType> expected;
  std::string message;

 public:
  UnexpectedToken(Token received, std::string message = "")
      : received(received) {
    this->message = "Unexpected token; ";
    if (message != "")
      this->message += message + "; ";
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
    return this->parse_function_declaration();
    switch (this->at().type) {
      case TokenType::consttok:
      case TokenType::inttok:
      case TokenType::floattok:
      case TokenType::doubletok:
      case TokenType::chartok:
      case TokenType::booltok:
      case TokenType::autotok:
        return this->parse_function_declaration();
      default:
        return this->parse_expr();
        // throw UnexpectedToken(this->at());
    };

    // this->parse_expr();
  }

  Statement parse_function_declaration() {
    this->parse_typed_ident();
    this->parse_args();
    this->expect(TokenType::lsquirly);

    this->expect(TokenType::rsquirly);
    this->expect(TokenType::semicolon);
    return Statement();
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
            throw UnexpectedToken(this->at(), "Expected type semicolon or eql");
        }
      }
      default:
        throw UnexpectedToken(this->at(), "Parse var declaration");
    };
  }

  Expr parse_expr() { return this->parse_additive_expr(); };

  Expr parse_additive_expr() {
    Expr left = this->parse_multiplicative_expr();
    while (this->at().type == TokenType::plus ||
           this->at().type == TokenType::minus) {
      TokenType op = this->eat().type;
      Expr right = this->parse_multiplicative_expr();
      left = BinaryExpr(left, right, op);
    }
    return left;
  }

  Expr parse_multiplicative_expr() {
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
    switch (this->at().type) {
      case TokenType::number:
        return NumericLiteral(std::stod(this->eat().literal));
      case TokenType::charlit:
        return CharLiteral(this->eat().literal.at(1));
      case TokenType::string: {
        std::string str = this->eat().literal;
        str = str.substr(1, str.length() - 2);
        return StringLiteral(str);
      }
      case TokenType::lparen: {
        this->eat();
        Expr value = this->parse_expr();
        this->expect(TokenType::rparen);
        return value;
      }
      default:
        throw UnexpectedToken(this->at(), "Parse primary expr");
    }
  }

  void parse_constructor() { expect(TokenType::ident); }

  void parse_args() {
    this->expect(TokenType::lparen);
    if (this->at().type != TokenType::rparen)
      this->parse_args_list();
    this->expect(TokenType::rparen);
  }

  void parse_typed_ident() {
    bool is_unsigned = false;
    if (this->at().type == TokenType::consttok) {
      this->eat();
    }

    if (this->at().type == TokenType::unsignedtok) {
      this->eat();
      is_unsigned = true;
    }

    switch (this->at().type) {
      case TokenType::voidtok:
      case TokenType::inttok:
      case TokenType::chartok:
      case TokenType::floattok:
      case TokenType::doubletok:
      case TokenType::booltok: {
        if (is_unsigned && !(this->at().type == TokenType::inttok ||
                             this->at().type == TokenType::chartok ||
                             this->at().type == TokenType::booltok))
          throw UnexpectedToken(this->at(), "Type cannot be unsigned");
        this->eat();
        this->expect(TokenType::ident);
        return;
      }
      default:
        throw UnexpectedToken(this->at(), "Parse typed ident");
    }
  }

  void parse_args_list() {
    this->parse_typed_ident();
    while (this->at().type == TokenType::comma) {
      this->eat();
      this->parse_typed_ident();
    }
  }
};