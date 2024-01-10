#pragma once
#include "Token.cpp"

using std::string;
using std::to_string;

class ParserException : public std::exception {
 private:
  Token token;
  string message;

 public:
  ParserException(Token token, string message) : token(token) {
    this->message = "Получен токен: `" + token.lit +
                    "` на позиции: строка: " + to_string(token.pos.row) +
                    ", столбец: " + to_string(token.pos.col) + "; " + message;
  }

  const char* what() const throw() { return this->message.c_str(); }
};