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

  returntok,    // return
  statictok,    // static
  consttok,     // const
  autotok,      // auto
  voidtok,      // void
  unsignedtok,  // unsigned
  inttok,       // int
  floattok,     // float
  doubletok,    // double
  chartok,      // char
  booltok,      // bool
  truetok,      // true
  falsetok,     // false
  classtok,     // class
  structtok,    // struct
  iftok,        // if
  elsetok,      // else
  dotok,        // do
  whiletok,     // while
  fortok,       // for

  publictok,     // public
  privatetok,    // private
  protectedtok,  // protected

  eof,
  illegal
};