#pragma once
#include <string>

enum class Color {
  red = 31,
  green = 32,
  yellow = 33,
  blue = 34,
  magenta = 35,
  cyan = 36
};

std::string colorized_string(const std::string& str, Color color_code) {
  std::string new_str =
      "\033[" + std::to_string(int(color_code)) + "m" + str + "\033[0m";
  return new_str;
}