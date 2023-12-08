enum struct TokenType {
  number,
  string,
  ident,

  lparen,     // (
  rparen,     // )
  lsquirly,   // {
  rsquirly,   // }
  lsquare,    // [
  rsquare,    // ]
  slash,      // /
  linecomm,   // //
  longcomm,   // /* */ 
  asteriks,   // *
  persent,    // %
  plus,       // +
  minus,      // -
  eql,        // =
  neq,        // !=
  lss,        // <
  leq,        // <=
  gtr,        // >
  geq,        // >=
  colon,      // :
  semicolon,  // ;
  comma,      // ,
  ampersand,  // &
  arrow,      // ->
  andsym,     // &&
  orsym,      // ||
  notsym,     // !
  logicand,   // &
  logicor,    // |
  logicnot,   // ~
  logicxor,   // ^

  inttok,     // int
  floattok,   // float
  doubletok,  // double
  chartok,    // char
  booltok,    // bool
  classtok,   // class
  structtok,  // struct
  iftok,      // if
  elsetok,    // else
  dotok,      // do
  whiletok,   // while
  fortok,     // for
  consttok,   // const
  autotok,    // auto

  eof,
  illegal
};