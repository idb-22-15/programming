#pragma once
#include <fstream>
#include <sstream>

class FileReader {
 public:
  static std::string tryReadFileToString(std::string filename) {
    std::ifstream file(filename);
    if (!file)
      throw std::runtime_error("Cannot open file");

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string file_content = buffer.str();
    return file_content;
  }
};