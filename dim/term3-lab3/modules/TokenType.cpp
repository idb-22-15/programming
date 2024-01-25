#pragma once

enum class TokenType {
  OpenParen,     // (
  CloseParen,    // )
  OpenSquirly,   // {
  CloseSquirly,  // }
  OpenBracket,   // [
  CloseBracket,  // ]
  Semicolon,     // ;
  Comma,         // ,
  Assign,        // =
  Int,           // int
  Ident,         // variable
  IntLiteral,    // 10,

  LineComment,
  LongComment,

  Eof,
  Illegal,
};