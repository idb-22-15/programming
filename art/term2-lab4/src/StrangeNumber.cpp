#include <math.h>

class StrangeNumber {
 private:
  int number;

 public:
  StrangeNumber(int number) { this->number = number; }

  int value() { return this->number; }

  bool isRepresentable() {
    for (int a = 0; a <= this->number; a++) {
      for (int b = 0; b <= this->number; b++) {
        int strangeSum = pow(a, 2) + pow(b, 2);
        if (this->number == strangeSum)
          return true;
      }
    }
    return false;
  }
};
