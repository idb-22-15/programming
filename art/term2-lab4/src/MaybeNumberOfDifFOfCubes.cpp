#include <cmath>

class MaybeNumberOfDifFOfCubes {
 private:
  int number;

 public:
  MaybeNumberOfDifFOfCubes(int number) { this->number = number; }

  bool isRepresentable() {
    for (int x = 1; x <= number; x++) {
      for (int y = 1; y <= number; y++) {
        int expression = (x - y) * (pow(x, 2) + x * y + pow(y, 2));
        if (number == expression)
          return true;
      }
    }
    return false;
  }

  int value() { return this->number; }
};
