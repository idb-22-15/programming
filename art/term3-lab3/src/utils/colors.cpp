#pragma once
#include <string>

enum class Color {
  black = 30,
  red,
  green,
  yellow,
  blue,
  magenta,
  cyan,
  white,

  bg_black = 40,
  bg_red,
  bg_green,
  bg_yellow,
  bg_magenta,
  bg_cyan,
  bg_white,

  bright_black = 90,
  bright_red,
  bright_green,
  bright_yellow,
  bright_blue,
  bright_magenta,
  bright_cyan,
  bright_white,

  bg_bright_black = 100,
  bg_bright_red,
  bg_bright_green,
  bg_bright_yellow,
  bg_bright_blue,
  bg_bright_magenta,
  bg_bright_cyan,
  bg_bright_white
};

std::string colorized_string(const std::string& str, Color color_code) {
  std::string new_str =
      "\033[" + std::to_string(int(color_code)) + "m" + str + "\033[0m";
  return new_str;
}