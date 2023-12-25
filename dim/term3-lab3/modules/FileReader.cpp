#pragma once
#include <fstream>
#include <sstream>

class FileReader {
 public:
  static std::string tryReadFileToString(std::string filename) {
    std::ifstream file(filename);
    if (!file)
      throw std::runtime_error("Не удалось открыть файл");

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileAsString = buffer.str();
    return fileAsString;
  }
};