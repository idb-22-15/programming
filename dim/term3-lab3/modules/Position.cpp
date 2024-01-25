#pragma once
#include "cstddef"

class Position {
 public:
  size_t start;
  size_t end;
  size_t row;
  size_t col;

  Position(size_t start, size_t end, size_t row, size_t col)
      : start(start), end(end), row(row), col(col) {}
};