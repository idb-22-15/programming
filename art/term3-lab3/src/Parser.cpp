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
                     std::to_string(this->received.position.start) +
                     ", end: " + std::to_string(this->received.position.end);
  }

  UnexpectedToken(TokenType expected, Token received) : received(received) {
    this->expected = std::experimental::make_optional(expected);
    this->message = "Expected type: " + Token::printable_literals.at(expected) +
                    "; received type: " + this->received.type_printable +
                    ", literal: " + this->received.literal + ", start: " +
                    std::to_string(this->received.position.start) +
                    ", end: " + std::to_string(this->received.position.end);
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

  Token expect(TokenType type) {
    Token tok = this->eat();
    if (tok.type != type)
      throw UnexpectedToken(type, tok);
    return tok;
  }

  Token expect(TokenType type1, TokenType type2) {
    Token tok = this->eat();
    if (tok.type != type1 && tok.type != type2)
      throw UnexpectedToken(
          tok, "Expected type: " + Token::printable_literals.at(type1) +
                   " or " + Token::printable_literals.at(type2));
    return tok;
  }

  Token expect(TokenType type1, TokenType type2, TokenType type3) {
    Token tok = this->eat();
    if (tok.type != type1 && tok.type != type2)
      throw UnexpectedToken(
          tok, "Expected type: " + Token::printable_literals.at(type1) +
                   " or " + Token::printable_literals.at(type2) + " or " +
                   Token::printable_literals.at(type3));
    return tok;
  }

  Statement parse_statement() {
    // return this->parse_function_declaration();
    switch (this->at().type) {
      case TokenType::unsignedtok:
      case TokenType::consttok:
      case TokenType::inttok:
      case TokenType::floattok:
      case TokenType::doubletok:
      case TokenType::chartok:
      case TokenType::booltok:
      case TokenType::autotok:
        return this->parse_var_declaration();
      case TokenType::classtok:
      case TokenType::structtok:
        return this->parse_class_declaration();
      case TokenType::semicolon: {
        this->eat();
        return Statement();
      }
      default:
        return this->parse_expr();
    };
  }

  Declaration parse_function_declaration(VarType return_type,
                                         std::string identifier) {
    std::vector<VarDeclaration> params = this->parse_args();

    switch (this->at().type) {
      case TokenType::semicolon:
        this->eat();
        return FunctionDeclaration(return_type, identifier, params,
                                   std::experimental::nullopt);
      case TokenType::lsquirly: {
        this->eat();

        std::vector<Statement> body;

        while (this->at().type != TokenType::rsquirly) {
          body.push_back(this->parse_statement());
          if (this->eof_or_illegal())
            throw UnexpectedToken(this->at(), "Parse function body");
        }
        this->expect(TokenType::rsquirly);
        return FunctionDeclaration(return_type, identifier, params, body);
      }
      default:
        throw UnexpectedToken(this->at(), "Parse function declaration");
    }
  }

  Declaration parse_var_declaration() {
    VarType var_type = this->parse_var_type();
    Token ident = this->expect(TokenType::ident);

    switch (this->at().type) {
      case TokenType::semicolon:
        this->eat();
        if (var_type.is_const)
          throw UnexpectedToken(this->at(),
                                "Must assign value to constant expression");
        return VarDeclaration(var_type, ident.literal,
                              std::experimental::nullopt);
      case TokenType::eql: {
        this->eat();
        Expr value = this->parse_expr();
        this->expect(TokenType::semicolon);
        return VarDeclaration(var_type, ident.literal, value);
      }
      case TokenType::lparen:
        return this->parse_function_declaration(var_type, ident.literal);
      default:
        throw UnexpectedToken(this->at(),
                              "Expected type semicolon, eql or lparen");
    }
  }

  Expr parse_expr() { return this->parse_additive_expr(); };

  Expr parse_assignment_expr() {
    Expr left = this->parse_additive_expr();

    if (this->at().type == TokenType::eql) {
      this->eat();  // advance past equals
      Expr value = this->parse_assignment_expr();
      return AssignmentExpr(left, value);
    }

    return left;
  }

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
      case TokenType::truetok:
      case TokenType::falsetok: {
        TokenType type = this->eat().type;
        bool value = type == TokenType::truetok ? true : false;
        return BoolLiteral(value);
      }
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
      args.push_back(this->parse_args_list_item());
    }
    return args;
  }

  VarDeclaration parse_args_list_item() {
    VarType var_type = this->parse_var_type();
    Token ident = this->expect(TokenType::ident);

    if (this->at().type == TokenType::eql) {
      this->eat();
      Expr value = this->parse_expr();
      return VarDeclaration(var_type, ident.literal, value);
    }

    return VarDeclaration(var_type, ident.literal, std::experimental::nullopt);
  }

  VarType parse_var_type() {
    bool is_const = false;
    bool is_signed = true;
    if (this->at().type == TokenType::consttok) {
      this->eat();
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
          return VarType(tok.type, is_const, is_signed);
        throw UnexpectedToken(TokenType::ident, this->at());
      }
      default:
        throw UnexpectedToken(this->at(), "Parse variable type");
    }
  }

  Statement parse_class_declaration() {
    Token classtok = this->expect(TokenType::classtok, TokenType::structtok);
    Token ident = this->expect(TokenType::ident);
    if (this->at().type == TokenType::colon) {
      this->eat();
      do {
        this->expect(TokenType::publictok, TokenType::privatetok,
                     TokenType::protectedtok);
        this->expect(TokenType::ident);
      } while (this->at().type == TokenType::comma);
    }

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
        case TokenType::publictok:
        case TokenType::privatetok:
        case TokenType::protectedtok: {
          Token modtok = this->eat();
          if (modtok.type == TokenType::publictok)
            current_mode = AccessModifier::publicmod;
          else if (modtok.type == TokenType::privatetok)
            current_mode = AccessModifier::privatemod;
          else if (modtok.type == TokenType::protectedtok)
            current_mode = AccessModifier::protectedmod;

          this->expect(TokenType::colon);
          break;
        }
        default:
          Declaration declaration = this->parse_var_declaration();
          items.push_back(ClassItem(current_mode, declaration));
      }
      if (this->eof_or_illegal())
        throw UnexpectedToken(this->at(), "Parse class body");
    }

    this->expect(TokenType::rsquirly);
    this->expect(TokenType::semicolon);
    return ClassDeclaration(ident.literal, items);
  };

  FunctionDeclaration parse_constructor(std::string class_ident) {
    Token identtok = this->expect(TokenType::ident);
    if (identtok.literal != class_ident)
      throw UnexpectedToken(this->at(), "Wrong constructor name");
    std::vector<VarDeclaration> args = this->parse_args();
    if (this->at().type == TokenType::colon)
      this->parse_constructor_init_list();

    std::vector<Statement> body;
    this->expect(TokenType::lsquirly);

    while (this->at().type != TokenType::rsquirly) {
      body.push_back(this->parse_statement());
      if (this->eof_or_illegal())
        throw UnexpectedToken(this->at(), "Parse constructor body");
    }
    this->expect(TokenType::rsquirly);
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

  // void parse_class_item_access_modifier() {
};