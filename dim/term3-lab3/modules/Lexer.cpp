#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Token.cpp"

using std::string;
using std::vector;

class Lexer {
 private:
  string text;
  size_t cur = 0;  // cursor
  size_t row = 1;
  size_t col = 1;

 public:
  vector<Token> lexicalAnalisis(const string& text) {
    this->text = text;
    this->cur = 0;
    this->row = 1;
    this->col = 1;

    vector<Token> tokenList;
    Token tok = this->getNextToken();
    tokenList.push_back(tok);
    while (tok.type != TokenType::Eof) {
      tok = this->getNextToken();
      tokenList.push_back(tok);
    }

    vector<Token> tokenListFiltered = this->getfilteredTokenList(tokenList);
    return tokenListFiltered;
  };

 private:
  vector<Token> getfilteredTokenList(const vector<Token> tokenList) {
    vector<Token> tokenListFiltered;

    for (Token token : tokenList) {
      if (!(token.type == TokenType::LineComment ||
            token.type == TokenType::LongComment)) {
        tokenListFiltered.push_back(token);
      }
    }
    return tokenListFiltered;
  }

  bool isEnd() { return this->cur >= this->text.length(); }
  char get() { return this->text[this->cur]; };
  char getNext() {
    if (!this->isEnd())
      return this->text[this->cur + 1];
    else
      return '\0';
  }

  char eraseChar() {
    if (!this->isEnd()) {
      char ch = this->get();
      this->move();
      return ch;
    } else
      return '\0';
  }

  int move() {
    if (this->get() == '\n') {
      this->row++;
      this->col = 0;
    }
    this->col++;
    return this->cur++;
  }

  bool isSpace() {
    char ch = this->get();
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
  }

  void skipSpaces() {
    while (this->isSpace()) {
      this->move();
    }
  }

  Token getNextToken() {
    this->skipSpaces();
    char ch = this->get();
    Position posChar(this->cur, this->cur + 1, this->row, this->col);
    switch (ch) {
      case '(': {
        this->eraseChar();
        return Token(TokenType::OpenParen, ch, posChar);
      }
      case ')': {
        this->eraseChar();
        return Token(TokenType::CloseParen, ch, posChar);
      }
      case '{': {
        this->eraseChar();
        return Token(TokenType::OpenSquirly, ch, posChar);
      }
      case '}': {
        this->eraseChar();
        return Token(TokenType::CloseSquirly, ch, posChar);
      }
      case '[': {
        this->eraseChar();
        return Token(TokenType::OpenBracket, ch, posChar);
      }
      case ']': {
        this->eraseChar();
        return Token(TokenType::CloseBracket, ch, posChar);
      }
      case ';': {
        this->eraseChar();
        return Token(TokenType::Semicolon, ch, posChar);
      }
      case ',': {
        this->eraseChar();
        return Token(TokenType::Comma, ch, posChar);
      }
      case '=': {
        this->eraseChar();
        return Token(TokenType::Assign, ch, posChar);
      }
      case '/': {
        if (this->getNext() == '/') {
          size_t start = this->cur;
          size_t row = this->row;
          size_t col = this->col;
          string comment = "";
          while (this->get() != '\n' && !this->isEnd()) {
            comment += this->eraseChar();
          }
          size_t end = this->cur;
          if (this->get() == '\n')
            this->move();

          Position pos(start, end, row, col);
          return Token(TokenType::LineComment, comment, pos);
        }

        else if (this->getNext() == '*') {
          size_t start = this->cur;
          size_t row = this->row;
          size_t col = this->col;
          string comment = "";
          while (!(this->get() == '*' && this->getNext() == '/')) {
            comment += this->eraseChar();
            if (this->isEnd())
              return Token(TokenType::Illegal, "/*",
                           Position(start, start + 2, row, col));
          }
          if (this->get() == '*' && this->getNext() == '/') {
            comment += this->eraseChar();
            comment += this->eraseChar();
          }

          size_t end = this->cur;
          Position pos(start, end, row, col);
          return Token(TokenType::LongComment, comment, pos);
        }

        this->eraseChar();
        return Token(TokenType::Illegal, ch, posChar);
      }
      case '\0': {
        Position pos(this->cur, this->cur, this->row, this->col);
        return Token(TokenType::Eof, ch, pos);
      }
      default:
        break;
    }

    if (isdigit(ch)) {
      size_t start = this->cur;
      size_t row = this->row;
      size_t col = this->col;
      string intLiteral = "";
      while (isdigit(this->get())) {
        intLiteral += this->eraseChar();
      }
      size_t end = this->cur;
      Position pos(start, end, row, col);
      return Token(TokenType::IntLiteral, intLiteral, pos);
    }

    if (this->isIdentChar() && !isdigit(this->get())) {
      size_t start = this->cur;
      size_t row = this->row;
      size_t col = this->col;
      string ident = "";
      while (this->isIdentChar()) {
        ident += this->eraseChar();
      }
      size_t end = this->cur;
      Position pos(start, end, row, col);

      if (ident == "int")
        return Token(TokenType::Int, ident, pos);

      return Token(TokenType::Ident, ident, pos);
    }

    this->eraseChar();
    return Token(TokenType::Illegal, ch, posChar);
  }

  bool isIdentChar() {
    return isalpha(this->get()) || isdigit(this->get()) || this->get() == '_';
  }
};
