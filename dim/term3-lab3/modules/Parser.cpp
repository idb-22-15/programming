#pragma once
#include "FileReader.cpp"
#include "Lexer.cpp"
#include "ParserException.cpp"
#include "optional"

using std::make_optional;
using std::nullopt;
using std::optional;
using std::stoi;
using std::string;
using std::vector;

class Parser {
 private:
  vector<Token> tokenList;

 public:
  void parseFile(string filename) {
    try {
      std::cout << "Файл: " << filename << std::endl;
      string text = FileReader::tryReadFileToString(filename);
      this->parse(text);
    } catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
    }
  }

 private:
  void parse(string text) {
    Lexer lexer;
    this->tokenList = lexer.lexicalAnalisis(text);

    while (!this->isEnd()) {
      try {
        TokenType type = this->get().type;

        if (type == TokenType::Int) {
          this->parseArray();
        }

        else if (type == TokenType::Ident) {
          this->parseAssign();
        }

        else if (type == TokenType::Semicolon) {
          this->require(TokenType::Semicolon);
        }

        else {
          throw ParserException(this->eraseToken(),
                                "Конструкция не поддерживаается");
        }
      } catch (const ParserException& e) {
        std::cout << e.what() << std::endl;
      }
    }
  }

  Token get() { return this->tokenList[0]; }
  Token eraseToken() {
    Token token = this->get();
    if (!this->isEnd())
      this->tokenList.erase(this->tokenList.begin());
    return token;
  }
  bool isEnd() { return this->get().type == TokenType::Eof; }

  Token require(TokenType type, string locationMessage = "") {
    Token token = this->eraseToken();
    string errorMessage = locationMessage.length() == 0
                              ? "Ожидался тип: " + Token::printType(type)
                              : "Ожидался тип: " + Token::printType(type) +
                                    "; Место: " + locationMessage;
    if (token.type != type)
      throw ParserException(token, errorMessage);
    return token;
  }

  void parseArray() {
    string locationMessage = "Массив";
    this->require(TokenType::Int, locationMessage);    // int
    this->require(TokenType::Ident, locationMessage);  // array
    vector<optional<size_t>> dimentions =
        this->parseArrayDimentions();  // [] or [10] or [5][2] or [?][?]..[?]

    if (this->get().type == TokenType::Semicolon) {
      Token token = this->require(TokenType::Semicolon, locationMessage);  // ;
      if (!this->allDimentionsDefined(dimentions)) throw ParserException(token, "Размерность не определена");
      return;
    }

    this->require(TokenType::Assign);     // =
    this->parseArrayBody(dimentions);     // {1, 2, 3} or {{1}, {2}, {3}}
    this->require(TokenType::Semicolon);  // ;
  }

  vector<optional<size_t>> parseArrayDimentions() {
    vector<optional<size_t>> dimentions;
    while (this->get().type != TokenType::Assign &&
           this->get().type != TokenType::Semicolon) {
      optional<size_t> size = this->parseArrayDimention();  // [] or [1]
      dimentions.push_back(size);
    }
    return dimentions;
  }

  optional<size_t> parseArrayDimention() {
    string locationMessage = "Размерность массива";
    optional<size_t> size = nullopt;

    this->require(TokenType::OpenBracket, locationMessage);  // [

    if (this->get().type != TokenType::CloseBracket) {  // <empty>
      Token intToken =
          this->require(TokenType::IntLiteral, locationMessage);  // 1
      size = make_optional<size_t>(stoi(intToken.lit));
    }
    this->require(TokenType::CloseBracket, locationMessage);  // ]

    return size;
  }

  size_t parseArrayInnerBody(vector<optional<size_t>> dimentions,
                             size_t level = 1) {
    string locationMessage = "Подмассив";
    size_t countItems = 0;
    size_t countDimentions = dimentions.size();
    optional<size_t> dimentionSize = dimentions[level - 1];
    optional<size_t> restSize = this->restDimentionsSize(dimentions, level);

    if (level == countDimentions) {
      this->require(TokenType::OpenSquirly, locationMessage);  // {

      if (this->get().type != TokenType::CloseSquirly) {  // not }
        countItems += this->parseArrayItem(countDimentions, level);
      }

      while (this->get().type == TokenType::Comma) {
        this->require(TokenType::Comma, locationMessage);  // ,
        if (this->get().type != TokenType::CloseSquirly) {  // проверка на висячую запятую
            countItems += this->parseArrayItem(countDimentions, level);
        }
      }

      this->require(TokenType::CloseSquirly, locationMessage);  // }
    } else {
      this->require(TokenType::OpenSquirly, locationMessage);  // {

      if (this->get().type == TokenType::IntLiteral) {
        countItems += this->parseArrayItem(countDimentions, level);
      } else
        countItems += this->parseArrayInnerBody(dimentions, level + 1);

      while (this->get().type == TokenType::Comma) {
        this->require(TokenType::Comma);  // ,
        if (this->get().type != TokenType::CloseSquirly) {
          if (this->get().type == TokenType::IntLiteral) {
            countItems += this->parseArrayItem(countDimentions, level);
          } else
            countItems += this->parseArrayInnerBody(dimentions, level + 1);
        }
      }
      this->require(TokenType::CloseSquirly, locationMessage);  // }
    }

    if (restSize && countItems > restSize.value())  
      throw ParserException(this->eraseToken(),
        "В массиве на уровне " + to_string(level) +
            " инициализированно слишком много элементов; "
            "Размерность: " +
            to_string(restSize.value()) +
            ", элементов: " + to_string(countItems));

    return countItems;
  }

  void parseArrayBody(vector<optional<size_t>> dimentions) {
    optional<size_t> size = this->restDimentionsSize(dimentions);
    size_t countItems = this->parseArrayInnerBody(dimentions);

    if (!size && dimentions.size() >= 2)
      throw ParserException(this->eraseToken(),
                            "Матрица имеет незавешённую размерность");
  }

  size_t parseArrayItem(size_t countDimentions, size_t level) {
    string locationMessage =
        "Элемент массива на уровне вложенности " + to_string(level);
    if (countDimentions == level) {
      if (this->get().type == TokenType::OpenSquirly) {
        this->require(TokenType::OpenSquirly, locationMessage);   // {
        this->require(TokenType::IntLiteral, locationMessage);    // 99
        this->require(TokenType::CloseSquirly, locationMessage);  // }
      } else
        this->require(TokenType::IntLiteral, locationMessage);  // 99
    } else
      this->require(TokenType::IntLiteral, locationMessage);  // 99
    return 1;
  }

  void parseAssign() {
    string locationMessage = "Присваивание значения элементу массива";
    this->require(TokenType::Ident);  // array 
    vector<optional<size_t>> dimentions = this->parseArrayDimentions();  // [2]
    this->require(TokenType::Assign);                                    // =
    this->require(TokenType::IntLiteral);                                // 100
    Token token = this->require(TokenType::Semicolon);                   // ;
    if (!this->allDimentionsDefined(dimentions))
      throw ParserException(token, "Размерность не определена до конца");
  }

  bool allDimentionsDefined(vector<optional<size_t>> dimentions) {
    bool defined = true;
    for (optional<size_t> dimention : dimentions) {
      if (dimention == nullopt) {
        defined = false;
        break;
      }
    }
    return defined;
  }

  optional<size_t> restDimentionsSize(vector<optional<size_t>> dimentions, size_t currentLevel = 1) {
    optional<size_t> currentDimention = dimentions[currentLevel - 1];
    optional<size_t> restSize = currentDimention;

    for(size_t i = currentLevel; i < dimentions.size(); i++) {
      size_t level = i + 1;

      if (dimentions[level - 1]) restSize = restSize.value() * dimentions[level - 1].value();
      else restSize = nullopt;
    }
    return restSize;
  }
};