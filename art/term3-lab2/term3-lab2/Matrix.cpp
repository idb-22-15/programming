 #pragma once
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>


class Matrix {
 private:
  std::vector<std::vector<double>> matrix;

  size_t computeRowWithoutZeros() {
    size_t counter = 0;

    for (int rowIndex = 0; rowIndex < this->matrix.size(); rowIndex++) {
      bool rowHaveZeros = false;

      for (int colIndex = 0; colIndex < this->matrix[0].size(); colIndex++) {
        if (matrix[rowIndex][colIndex] == 0) {
          rowHaveZeros = true;
        }
      }

      if (!rowHaveZeros)
        counter++;
    }
    return counter;
  }

   void fromFile_(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::string line;

    matrix.resize(0);
    if (!inputFile.is_open())
      throw std::runtime_error("Failed to open the file.");

    bool is_first_row = true;

    while (std::getline(inputFile, line)) {
      std::vector<double> row;
      std::istringstream iss(line);
      double num;

      if (is_first_row) {
          while (iss >> num) {
            row.push_back(num);
          }
      } else {
          for (size_t colIndex = 0; colIndex < this->getCols(); colIndex++) {
            if (iss >> num)
              row.push_back(num);
            else {
              row.push_back(0);
         /*     matrix.resize(0);
              throw std::runtime_error("Invalid matrix size");*/
            }
          }
      }
      matrix.push_back(row);
      is_first_row = false;
    }
    inputFile.close();
  }
 public:
    static Matrix* fromFile(const std::string& filename) {
      auto m = new Matrix();
      m->fromFile_(filename);
      return m;
    }


  Matrix(size_t rows = 1, size_t cols = 1) {
    this->matrix.resize(rows);
    for (size_t rowIndex = 0; rowIndex < this->matrix.size(); rowIndex++) {
      matrix[rowIndex].resize(cols);
    }

    this->clear();
  }

  void clear() {
    for (size_t rowIndex = 0; rowIndex < this->matrix.size(); rowIndex++) {
      for (size_t colIndex = 0; colIndex < this->matrix[0].size(); colIndex++) {
        matrix[rowIndex][colIndex] = 0;
      }
    }
  }

  void randomize() {
    std::srand(std::time(0));

    for (int rowIndex = 0; rowIndex < this->matrix.size(); rowIndex++) {
      for (int colIndex = 0; colIndex < this->matrix[0].size(); colIndex++) {
        if (rand() % 2 == 0)
          matrix[rowIndex][colIndex] = rand() % 100;
        else
          matrix[rowIndex][colIndex] = -1 * rand() % 100;
      }
    }
  }

  bool isNotEmpty() {
    bool notEmpty = false;

    for (int rowIndex = 0; rowIndex < this->matrix.size(); rowIndex++) {
      for (int colIndex = 0; colIndex < this->matrix[0].size(); colIndex++) {
        if (matrix[rowIndex][colIndex] != 0) {
          notEmpty = true;
          break;
        }
      }
    }

    return notEmpty;
  }

  bool isEmpty() { return !this->isNotEmpty(); }

  double getCellValue(size_t row, size_t col) { return this->matrix[row][col]; }

  void setCellValue(size_t row, size_t col, double value) {
    this->matrix[row][col] = value;
  }

  size_t getRows() { return this->matrix.size(); }

  size_t getCols() { return this->matrix[0].size(); }

  size_t rowsWithoutZeros() { return this->computeRowWithoutZeros();}
};