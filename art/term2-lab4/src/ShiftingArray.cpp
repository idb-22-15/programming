class ShiftingArray {
 private:
  int array[10] = {};

 public:
  ShiftingArray(int arr[10]) {
    for (int i = 0; i < 10; i++) {
      this->array[i] = arr[i];
    }
  }

  static void shiftRight(int array[10], int steps = 2) {
    for (int step = 0; step < steps; step++) {
      int first = array[0];

      for (int i = 0; i < 10 - 1; i++) {
        array[i] = array[i + 1];
      }
      array[10 - 1] = first;
    }
  }

  void shiftRight(int steps = 2) {
    for (int step = 0; step < steps; step++) {
      int first = this->array[0];

      for (int i = 0; i < 10 - 1; i++) {
        this->array[i] = this->array[i + 1];
      }
      this->array[10 - 1] = first;
    }
  }

  int* value() { return this->array; }
};
