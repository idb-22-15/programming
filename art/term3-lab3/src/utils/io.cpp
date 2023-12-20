#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "colors.cpp"

std::string read_file(const std::string& filename) {
  std::ifstream file(filename);
  if (!file)
    throw std::runtime_error("Cannot open file");
  // std::cerr << colorized_string("error: ", Color::red) << "cannot open
  // file"
  //           << std::endl;
  // exit(1);

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string file_content = buffer.str();
  return file_content;
}