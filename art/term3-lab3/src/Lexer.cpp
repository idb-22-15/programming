#pragma once
#include <experimental/optional>
#include <regex>
#include <string>
#include <vector>
#include "Token.cpp"

class Lexer {
 private:
  std::string input;
  size_t cursor = 0;
  size_t line = 1;
  size_t col = 1;

 public:
  void init(std::string& input) {
    this->input = input;
    this->cursor = 0;
  }

  std::vector<Token> tokenize() {
    std::vector<Token> tokens;

    Token tok = this->next();
    tokens.push_back(tok);
    while (tok.type != TokenType::eof) {
      tok = this->next();
      tokens.push_back(tok);
    }
    std::vector<Token> filtered_tokens;
    std::copy_if(tokens.begin(), tokens.end(),
                 std::back_inserter(filtered_tokens), [](Token tok) {
                   return !(tok.type == TokenType::linecomm ||
                            tok.type == TokenType::longcomm);
                 });

    return filtered_tokens;
  }

 private:
  std::experimental::optional<std::string> match(const std::string& str,
                                                 const std::regex& regex) {
    std::smatch results;

    if (std::regex_search(str, results, regex)) {
      this->move_cursor(results[0].length());
      return std::experimental::make_optional(results[0]);
    };
    return std::experimental::nullopt;
  }

  bool has_more_tokens() { return this->cursor < this->input.length(); }

  char at() { return this->input[this->cursor]; }

  char peek() {
    if (this->has_more_tokens())
      return this->input[this->cursor + 1];
    else
      return '\0';
  }

  void skip_whitespace() {
    while (isspace(this->at()) && this->has_more_tokens()) {
      if (this->at() == '\n') {
        this->col = -1;
        this->line++;
      }
      this->move_cursor();
    }
  }

  size_t move_cursor(size_t steps = 1) {
    size_t prev = this->cursor;
    for (size_t step = 0; step < steps; step++) {
      this->cursor++;
      this->col++;
    }
    return prev;
  }

  Token next() {
    this->skip_whitespace();

    if (!this->has_more_tokens())
      return Token(TokenType::eof, "\0",
                   Position(this->cursor, this->cursor, this->line, this->col));

    if (this->at() == '/' && this->peek() == '/') {
      this->move_cursor(2);
      size_t start_comment = this->cursor;
      size_t line = this->line;
      size_t col = this->col;
      while (this->at() != '\n' && this->has_more_tokens()) {
        this->move_cursor();
      }
      bool is_eof = (this->at() != '\n' && !this->has_more_tokens());
      size_t shift = is_eof ? 0 : 1;
      return Token(TokenType::linecomm,
                   this->input.substr(start_comment,
                                      this->cursor - start_comment - shift),
                   Position(start_comment, this->cursor, line, col));
    } else if (this->at() == '/' && this->peek() == '*') {
      this->move_cursor(2);
      size_t start_comment = this->cursor;
      size_t line = this->line;
      size_t col = this->col;
      while (!(this->at() == '*' && this->peek() == '/')) {
        this->move_cursor();
        if (!this->has_more_tokens())
          return Token(TokenType::illegal, "/*",
                       Position(start_comment, start_comment + 2, line, col));
      }
      this->move_cursor(2);
      return Token(
          TokenType::longcomm,
          this->input.substr(start_comment, this->cursor - start_comment - 2),
          Position(start_comment, this->cursor - 2, line, col));
    } else if (this->at() == '/') {
      size_t start_cursor = this->move_cursor();
      size_t line = this->line;
      size_t col = this->col;
      return Token(TokenType::slash, "/",
                   Position(start_cursor, this->cursor, line, col));
    }

    for (auto pair : Token::regex_table) {
      TokenType token_type = pair.first;
      std::regex regex = pair.second;
      size_t start_cursor = this->cursor;
      size_t line = this->line;
      size_t col = this->col;
      std::experimental::optional<std::string> result =
          this->match(this->input.substr(this->cursor), regex);
      if (!result)
        continue;
      if (token_type == TokenType::ident) {
        auto it = Token::reserved_idents.find(result.value());
        if (it != Token::reserved_idents.end())
          return Token(it->second, result.value(),
                       Position(start_cursor, this->cursor, line, col));
      }
      return Token(token_type, result.value(),
                   Position(start_cursor, this->cursor, line, col));
    }

    std::string illegal_literal = "";
    illegal_literal += this->at();
    size_t start_cursor = this->move_cursor();
    size_t line = this->line;
    size_t col = this->col;
    return Token(TokenType::illegal, illegal_literal,
                 Position(start_cursor, this->cursor, line, col));
  }
};