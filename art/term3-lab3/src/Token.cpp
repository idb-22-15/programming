#include <string>
#include <map>
#include <regex>

#include "TokenType.cpp"
// #pragma once

struct Position {
  size_t start;
  size_t end;
  Position(size_t start, size_t end): start(start), end(end){}
};

struct Token {
  TokenType type;
  std::string type_printable;
  std::string literal;
  Position position;

  static const std::map<std::string, TokenType> reserved_idents;
  static const std::map<TokenType, std::string> printable_literals;
  static const std::map<TokenType, std::regex> regex_table;

  Token(TokenType type, std::string literal, Position position): position(position) {
    this->type = type;
    this->type_printable = Token::printable_literals.at(type);
    this->literal = literal;
  } 
};

const std::map<std::string, TokenType> Token::reserved_idents {
  {"int",      TokenType::inttok},
  {"float",    TokenType::floattok},
  {"double",   TokenType::doubletok},
  {"char",     TokenType::chartok},
  {"bool",     TokenType::booltok},
  {"class",    TokenType::classtok},
  {"struct",   TokenType::structtok},
  {"if",       TokenType::iftok},
  {"else",     TokenType::elsetok},
  {"do",       TokenType::dotok},
  {"while",    TokenType::whiletok},
  {"for",      TokenType::fortok},
  {"const",    TokenType::consttok},
  {"auto",     TokenType::autotok}
};


const std::map<TokenType, std::string> Token::printable_literals {
  {TokenType::number,     "number"},
  {TokenType::string,     "string"},
  {TokenType::ident,      "ident"},

  {TokenType::lparen,     "("},
  {TokenType::rparen,     ")"},
  {TokenType::lsquirly,   "{"},
  {TokenType::rsquirly,   "}"},
  {TokenType::lsquare,    "["},
  {TokenType::rsquare,    "]"},
  {TokenType::slash,      "/"},
  {TokenType::linecomm,   "line comment"},
  {TokenType::longcomm,   "lomg comment"},
  {TokenType::asteriks,   "*"},
  {TokenType::persent,    "%"},
  {TokenType::plus,       "+"},
  {TokenType::minus,      "-"},
  {TokenType::eql,        "="},
  {TokenType::neq,        "!="},
  {TokenType::lss,        "<"},
  {TokenType::leq,        "<="},
  {TokenType::gtr,        ">"},
  {TokenType::geq,        ">="},
  {TokenType::colon,      ":"},
  {TokenType::semicolon,  ";"},
  {TokenType::comma,      ","},
  {TokenType::ampersand,  "&"},
  {TokenType::arrow,      "->"},
  {TokenType::andsym,     "&&"},
  {TokenType::orsym,      "||"},
  {TokenType::notsym,     "!"},
  {TokenType::logicand,   "&"},
  {TokenType::logicor,    "|"},
  {TokenType::logicnot,   "~"},
  {TokenType::logicxor,   "^"},

  {TokenType::inttok,     "int"},
  {TokenType::floattok,   "float"},
  {TokenType::doubletok,  "double"},
  {TokenType::chartok,    "char"},
  {TokenType::booltok,    "bool"},
  {TokenType::classtok,   "class"},
  {TokenType::structtok,  "struct"},
  {TokenType::iftok,      "if"},
  {TokenType::elsetok,    "else"},
  {TokenType::dotok,      "do"},
  {TokenType::whiletok,   "while"},
  {TokenType::fortok,     "for"},
  {TokenType::consttok,   "const"},
  {TokenType::autotok,    "auto"},

  {TokenType::eof,        "eof"},
  {TokenType::illegal,    "illegal"}
};

const std::map<TokenType, std::regex> Token::regex_table {
  {TokenType::number,     std::regex("^-?\\d+(\\.\\d+)?")},
  {TokenType::string,     std::regex("^\"(\\\\.|[^\\\\\"])*\"")},
  {TokenType::ident,      std::regex("^[a-zA-Z_][a-zA-Z0-9_]*")},

  {TokenType::lparen,     std::regex("^\\(")},
  {TokenType::rparen,     std::regex("^\\)")},
  {TokenType::lsquirly,   std::regex("^\\{")},
  {TokenType::rsquirly,   std::regex("^\\}")},
  {TokenType::lsquare,    std::regex("^\\[")},
  {TokenType::rsquare,    std::regex("^\\]")},
  {TokenType::slash,      std::regex("^/")},
  {TokenType::linecomm,   std::regex("^//.*\n")},
  {TokenType::longcomm,   std::regex("/\\*.*?\\*/")},
  {TokenType::asteriks,   std::regex("^\\*")},
  {TokenType::persent,    std::regex("^%")},
  {TokenType::plus,       std::regex("^\\+")},
  {TokenType::minus,      std::regex("^-")},
  {TokenType::eql,        std::regex("^=")},
  {TokenType::neq,        std::regex("^!=")},
  {TokenType::lss,        std::regex("^<")},
  {TokenType::leq,        std::regex("^<=")},
  {TokenType::gtr,        std::regex("^>")},
  {TokenType::geq,        std::regex("^>=")},
  {TokenType::colon,      std::regex("^:")},
  {TokenType::semicolon,  std::regex("^;")},
  {TokenType::comma,      std::regex("^,")},
  {TokenType::ampersand,  std::regex("^\\&")},
  {TokenType::arrow,      std::regex("^->")},
  {TokenType::andsym,     std::regex("^\\&\\&")},
  {TokenType::orsym,      std::regex("^\\|\\|")},
  {TokenType::notsym,     std::regex("^!")},
  {TokenType::logicand,   std::regex("^\\&")},
  {TokenType::logicor,    std::regex("^\\|")},
  {TokenType::logicnot,   std::regex("^~")},
  {TokenType::logicxor,   std::regex("^\\^")},
};