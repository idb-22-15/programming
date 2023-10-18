class PoliNumber {
 private:
  int number;

 public:
  PoliNumber(int number) { this->number = number; }

  int value() { return this->number; }

  bool isPalindrome() {
    if (this->number < 0)
      return false;

    int reversed = 0;
    int copyNumber = this->number;

    while (copyNumber != 0) {
      int remainder = copyNumber % 10;
      reversed = reversed * 10 + remainder;
      copyNumber /= 10;
    }

    if (this->number == reversed)
      return true;
    return false;
  }
};
