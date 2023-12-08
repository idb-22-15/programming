#include <experimental/optional>
#include <string>
#include <regex>
#include <vector>
#include "Token.cpp"

class Lexer {
private:
  std::string input;
  size_t cursor = 0;

  std::experimental::optional<std::string> _match(std::string str, std::regex regex) {
      std::smatch results;

       if (std::regex_search(str, results, regex)) {
        this->cursor += results[0].length();
        return results[0];
      };

      return std::experimental::nullopt;
  }

  bool has_more_tokens() {return this->cursor < this->input.length();}

 public:
  void init(std::string input) {
    this->input = input;
    this->cursor = 0;
  }

  char at() {return this->input[this->cursor];}


  void skip_whitespace() {
    while (isspace(this->at()) && this->has_more_tokens()) this->cursor++;
  }

  std::vector<Token> tokenize() {
    std::vector<Token> tokens;
    
    Token tok = this->next();
    tokens.push_back(tok);
    while (tok.type != TokenType::eof) {
      tok = this->next();
      tokens.push_back(tok);
    }

    return tokens;
  }

  Token next() {
    this->skip_whitespace();

    if (!this->has_more_tokens()) return Token(TokenType::eof, "\0", Position(this->cursor, this->cursor));

    for (auto pair : Token::regex_table) {
      TokenType token_type = pair.first;
      std::regex regex = pair.second;
      size_t start_cursor = this->cursor;
      auto result = this->_match(this->input.substr(this->cursor), regex);
      if (!result) continue;
        
      if (token_type == TokenType::ident) {
        auto it = Token::reserved_idents.find(result.value());
        if (it != Token::reserved_idents.end()) return Token(it->second, result.value(), Position(start_cursor, this->cursor));
      }
      return Token(token_type, result.value(), Position(start_cursor, this->cursor));
    }
    
    std::string illegal_literal = "";
    illegal_literal += this->at();
    return Token(TokenType::illegal, illegal_literal, Position(this->cursor, this->cursor));
  }
};