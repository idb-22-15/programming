#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdio.h>

static bool is_stream_end(char c) {
  return c == '\n' || c == EOF;
}

#endif