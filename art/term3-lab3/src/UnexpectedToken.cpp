#pragma once
#include <experimental/optional>
#include <iomanip>
#include <iostream>
#include "Token.cpp"
#include "utils/colors.cpp"

class UnexpectedToken : public std::exception {
 public:
  const Token received;

 private:
  std::experimental::optional<TokenType> expected;
  std::string message;

 public:
  UnexpectedToken(Token received, std::string message = "")
      : received(received) {
    this->message = std::to_string(this->received.position.line) + ":" +
                    std::to_string(this->received.position.col) + ": ";
    this->message += message == "" ? "Unexpected token; "
                                   : "Unexpected token; " + message + "; ";
    this->message += "received: `" +
                     colorized_string(this->received.literal, Color::cyan) +
                     "`";
  }

  UnexpectedToken(TokenType expected, Token received) : received(received) {
    this->expected = std::experimental::make_optional(expected);
    this->message = std::to_string(this->received.position.line) + ":" +
                    std::to_string(this->received.position.col) + ": ";
    this->message +=
        "Expected type: " + Token::token_types_printable.at(expected) +
        "; received: `" +
        colorized_string(this->received.type_printable, Color::cyan) + "`";
  }

  virtual const char* what() const throw() { return this->message.c_str(); }

  void print_error_in_context(const std::string& input) const {
    Token tok = this->received;
    size_t lines_between_error = 2;
    size_t start_line = tok.position.line <= lines_between_error
                            ? 1
                            : tok.position.line - lines_between_error;
    size_t end_line = tok.position.line + lines_between_error;

    bool is_line_start = true;
    size_t current_line = 1;
    for (size_t i = 0; i < input.length(); i++) {
      bool is_between = current_line >= start_line && current_line <= end_line;
      bool is_error_line = current_line == tok.position.line;
      if (is_between) {
        if (is_line_start) {
          if (is_error_line)
            std::cout << std::setw(5) << std::to_string(tok.position.line)
                      << " | ";
          else
            std::cout << "      | ";
        }

        if (i >= tok.position.start && i < tok.position.end)
          std::cout << colorized_string(input.substr(i, 1), Color::bright_red);
        else
          std::cout << colorized_string(input.substr(i, 1), Color::yellow);
      }

      is_line_start = false;
      if (input[i] == '\n') {
        current_line++;
        is_line_start = true;
      }
    }
    std::cout << std::endl;
  }
};
