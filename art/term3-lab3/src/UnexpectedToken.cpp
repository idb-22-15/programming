#pragma once
#include <experimental/optional>
#include "Token.cpp"

class UnexpectedToken : public std::exception {
 public:
  const Token received;

 private:
  std::experimental::optional<TokenType> expected;
  std::string message;

 public:
  UnexpectedToken(Token received, std::string message = "")
      : received(received) {
    this->message = "line:" + std::to_string(this->received.position.line) +
                    " " + "col:" + std::to_string(this->received.position.col) +
                    " ";

    this->message += message == "" ? "Unexpected token; "
                                   : "Unexpected token; " + message + "; ";
    // if (message != "")
    //   this->message += message + "; ";
    this->message += "received type: " + this->received.type_printable +
                     ", literal: " + this->received.literal;
  }

  UnexpectedToken(TokenType expected, Token received) : received(received) {
    this->expected = std::experimental::make_optional(expected);
    this->message = "line:" + std::to_string(this->received.position.line) +
                    " " + "col:" + std::to_string(this->received.position.col) +
                    " ";

    this->message +=
        "Expected type: " + Token::token_types_printable.at(expected) +
        "; received type: " + this->received.type_printable +
        ", literal: " + this->received.literal;
  }

  virtual const char* what() const throw() { return this->message.c_str(); }
};