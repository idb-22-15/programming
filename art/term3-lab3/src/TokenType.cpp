#pragma once

enum struct TokenType {
  number,
  charlit,
  string,
  ident,

  lparen,     // (
  rparen,     // )
  lsquirly,   // {
  rsquirly,   // }
  lsquare,    // [
  rsquare,    // ]
  linecomm,   // //
  longcomm,   // /* */
  slash,      // /
  asteriks,   // *
  persent,    // %
  inc,        // ++
  plus,       // +
  dec,        // --
  arrow,      // ->
  minus,      // -
  eql,        // =
  neq,        // !=
  leq,        // <=
  lss,        // <
  geq,        // >=
  gtr,        // >
  colon,      // :
  semicolon,  // ;
  comma,      // ,
  logicand,   // &&
  logicor,    // ||
  logicnot,   // !
  bitcand,    // &
  bitcor,     // |
  bitnot,     // ~
  bitxor,     // ^

  voidtok,
  inttok,       // int
  floattok,     // float
  doubletok,    // double
  chartok,      // char
  booltok,      // bool
  unsignedtok,  // unsigned
  classtok,     // class
  structtok,    // struct
  iftok,        // if
  elsetok,      // else
  dotok,        // do
  whiletok,     // while
  fortok,       // for
  consttok,     // const
  autotok,      // auto

  eof,
  illegal
};