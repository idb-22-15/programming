#pragma once
#include <iostream>
#include <string>
#include "Position.cpp"
#include "TokenType.cpp"

using std::string;

class Token {
 public:
  TokenType type;
  string lit;  // string literal
  Position pos;

  Token(TokenType type, string lit, Position pos)
      : type(type), lit(lit), pos(pos) {}
  Token(TokenType type, char charLit, Position pos) : type(type), pos(pos) {
    this->lit = charLit;
  }

  void printToken() {
    std::cout << "Начало: " << this->pos.start << " конец: " << this->pos.end
              << " литерал: " << this->lit << std::endl;
  }

  static string printType(TokenType type) {
    if (type == TokenType::OpenParen)
      return "(";
    else if (type == TokenType::CloseParen)
      return ")";
    else if (type == TokenType::OpenSquirly)
      return "{";
    else if (type == TokenType::CloseSquirly)
      return "}";
    else if (type == TokenType::OpenBracket)
      return "[";
    else if (type == TokenType::CloseBracket)
      return "]";
    else if (type == TokenType::Semicolon)
      return ";";
    else if (type == TokenType::Comma)
      return ",";
    else if (type == TokenType::Assign)
      return "=";
    else if (type == TokenType::Int)
      return "int";
    else if (type == TokenType::Ident)
      return "<ident>";
    else if (type == TokenType::IntLiteral)
      return "<integer literal>";
    else if (type == TokenType::LineComment)
      return "<line comment>";
    else if (type == TokenType::LongComment)
      return "<long comment>";
    else if (type == TokenType::Eof)
      return "<eof>";
    else if (type == TokenType::Illegal)
      return "<illegal>";

    return "<тип не существует>";
  }
};