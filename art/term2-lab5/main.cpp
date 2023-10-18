#include <iostream>
#include "List.cpp"

int min_of_arr(int arr[10], int length) {
  int min = arr[0];
  for (int i = 0; i < length; i++) {
    if (arr[i] < min)
      min = arr[i];
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

  List arr_of_list_cols[10];
  for (int i = 0; i < cols; i++)
    arr_of_list_cols[i].set_length(rows);

  for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
      arr_of_list_cols[j].get_list()[i] = matrix[i][j];
    }
  }

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      std::cout << arr_of_list_cols[i].get_list()[j] << ' ';
    }
    std::cout << std::endl;
  }

  std::cout << "=====" << std::endl;

  int arr_of_max_values_of_cols[10];
  for (int i = 0; i < cols; i++) {
    arr_of_max_values_of_cols[i] = arr_of_list_cols[i].get_max();
    std::cout << arr_of_max_values_of_cols[i] << std::endl;
  }

  std::cout << "=====" << std::endl;

  std::cout << min_of_arr(arr_of_max_values_of_cols, cols) << std::endl;

  std::cout << arr_of_list_cols[0] * arr_of_list_cols[1];
}
