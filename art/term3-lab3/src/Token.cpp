#pragma once
#include <map>
#include <regex>
#include <string>
#include "TokenType.cpp"

struct Position {
  size_t start;
  size_t end;
  Position(size_t start, size_t end) : start(start), end(end) {}
};

struct Token {
  TokenType type;
  std::string type_printable;
  std::string literal;
  Position position;

  static const std::map<std::string, TokenType> reserved_idents;
  static const std::map<TokenType, std::string> printable_literals;
  static const std::map<TokenType, std::regex> regex_table;

  Token(TokenType type, std::string literal, Position position)
      : position(position) {
    this->type = type;
    this->type_printable = Token::printable_literals.at(type);
    this->literal = literal;
  }
};

const std::map<std::string, TokenType> Token::reserved_idents{
    {"int", TokenType::inttok},       {"float", TokenType::floattok},
    {"double", TokenType::doubletok}, {"char", TokenType::chartok},
    {"bool", TokenType::booltok},     {"class", TokenType::classtok},
    {"struct", TokenType::structtok}, {"if", TokenType::iftok},
    {"else", TokenType::elsetok},     {"do", TokenType::dotok},
    {"while", TokenType::whiletok},   {"for", TokenType::fortok},
    {"const", TokenType::consttok},   {"auto", TokenType::autotok}};

const std::map<TokenType, std::string> Token::printable_literals{
    {TokenType::number, "number lit"},
    {TokenType::charlit, "char lit"},
    {TokenType::string, "string lit"},
    {TokenType::ident, "ident"},

    {TokenType::lparen, "lparen"},
    {TokenType::rparen, "rparen"},
    {TokenType::lsquirly, "lsquirly"},
    {TokenType::rsquirly, "rsquirly"},
    {TokenType::lsquare, "lsqare"},
    {TokenType::rsquare, "rsquare"},
    {TokenType::linecomm, "line comm"},
    {TokenType::longcomm, "long comm"},
    {TokenType::slash, "slash"},
    {TokenType::asteriks, "asteriks"},
    {TokenType::persent, "persent"},
    {TokenType::inc, "inc"},
    {TokenType::plus, "pluc"},
    {TokenType::dec, "dec"},
    {TokenType::arrow, "arrow"},
    {TokenType::minus, "minus"},
    {TokenType::eql, "eql"},
    {TokenType::neq, "neq"},
    {TokenType::leq, "leq"},
    {TokenType::lss, "lss"},
    {TokenType::geq, "geq"},
    {TokenType::gtr, "gtr"},
    {TokenType::colon, "colon"},
    {TokenType::semicolon, "semicolon"},
    {TokenType::comma, "comma"},
    {TokenType::logicand, "logicand"},
    {TokenType::logicor, "logicor"},
    {TokenType::logicnot, "logicnot"},
    {TokenType::bitcand, "bitand"},
    {TokenType::bitcor, "bitor"},
    {TokenType::bitnot, "bitnot"},
    {TokenType::bitxor, "bitxor"},

    {TokenType::inttok, "int"},
    {TokenType::floattok, "float"},
    {TokenType::doubletok, "double"},
    {TokenType::chartok, "char"},
    {TokenType::booltok, "bool"},
    {TokenType::classtok, "class"},
    {TokenType::structtok, "struct"},
    {TokenType::iftok, "if"},
    {TokenType::elsetok, "else"},
    {TokenType::dotok, "do"},
    {TokenType::whiletok, "while"},
    {TokenType::fortok, "for"},
    {TokenType::consttok, "const"},
    {TokenType::autotok, "auto"},

    {TokenType::eof, "eof"},
    {TokenType::illegal, "illegal"}};

const std::map<TokenType, std::regex> Token::regex_table{
    {TokenType::number, std::regex("^-?\\d+(\\.\\d+)?")},
    {TokenType::charlit, std::regex("^'.'")},
    {TokenType::string, std::regex("^\"(\\\\.|[^\\\\\"])*\"")},
    {TokenType::ident, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*")},

    {TokenType::lparen, std::regex("^\\(")},
    {TokenType::rparen, std::regex("^\\)")},
    {TokenType::lsquirly, std::regex("^\\{")},
    {TokenType::rsquirly, std::regex("^\\}")},
    {TokenType::lsquare, std::regex("^\\[")},
    {TokenType::rsquare, std::regex("^\\]")},
    {TokenType::linecomm, std::regex("^//.*\n")},
    {TokenType::longcomm, std::regex("^/\\*.*?\\*/")},
    {TokenType::slash, std::regex("^/")},
    {TokenType::asteriks, std::regex("^\\*")},
    {TokenType::persent, std::regex("^%")},
    {TokenType::inc, std::regex("^\\+\\+")},
    {TokenType::plus, std::regex("^\\+")},
    {TokenType::dec, std::regex("^--")},
    {TokenType::arrow, std::regex("^->")},
    {TokenType::minus, std::regex("^-")},
    {TokenType::eql, std::regex("^=")},
    {TokenType::neq, std::regex("^!=")},
    {TokenType::leq, std::regex("^<=")},
    {TokenType::lss, std::regex("^<")},
    {TokenType::geq, std::regex("^>=")},
    {TokenType::gtr, std::regex("^>")},
    {TokenType::colon, std::regex("^:")},
    {TokenType::semicolon, std::regex("^;")},
    {TokenType::comma, std::regex("^,")},
    {TokenType::logicand, std::regex("^\\&\\&")},
    {TokenType::logicor, std::regex("^\\|\\|")},
    {TokenType::logicnot, std::regex("^!")},
    {TokenType::bitcand, std::regex("^\\&")},
    {TokenType::bitcor, std::regex("^\\|")},
    {TokenType::bitnot, std::regex("^~")},
    {TokenType::bitxor, std::regex("^\\^")},
};