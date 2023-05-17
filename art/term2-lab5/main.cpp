#include <iostream>
#include "List.cpp"

int minOfArr(int arr[10], int length) {
  int min = arr[0];
  for (int i = 0; i < length; i++) {
    if (arr[i] < min) min = arr[i];
  }
  return min;
}

int main() {
  int rows;
  std::cout << "Enter rows count" << std::endl;
  std::cin >> rows;

  int cols;
  std::cout << "Enter columns count" << std::endl;
  std::cin >> cols;

  int matrix[10][10];

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cin >> matrix[i][j];
    }
  }

  std::cout << "=====" << std::endl;

  List arrOfListCols[10];
  for (int i = 0; i < cols; i++) arrOfListCols[i].setLength(rows);
  
  for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
      arrOfListCols[j].getList()[i] = matrix[i][j];
    }
  }

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      std::cout << arrOfListCols[i].getList()[j] << ' ';
    }
    std::cout << std::endl;
  }

  std::cout << "=====" << std::endl;

  int arrOfMaxValuesOfCols[10];
  for (int i = 0; i < cols; i++) {
    arrOfMaxValuesOfCols[i] = arrOfListCols[i].getMax();
    std::cout << arrOfMaxValuesOfCols[i] << std::endl;
  }

  std::cout << "=====" << std::endl;
  
  std::cout << minOfArr(arrOfMaxValuesOfCols, cols) << std::endl;

  std::cout << arrOfListCols[0] * arrOfListCols[1];
}