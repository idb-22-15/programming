class List {
 private:
  int list[5];
  int len;

  int nod(int a, int b) {
    if (a % b == 0)
      return b;

    if (b % a == 0)
      return a;

    if (a > b)
      return nod(a % b, b);

    return nod(a, b % a);
  }

  int nok(int a, int b) { return (a * b) / nod(a, b); }

 public:
  List(int len = 5) { this->len = len; }

  void set_length(int length) { this->len = length; }

  int* get_list() { return list; }

  int get_max() {
    int max = list[0];
    for (int i = 0; i < this->len; i++) {
      if (max < list[i])
        max = list[i];
    }
    return max;
  }

  int operator*(List& another_list);
};

int List::operator*(List& another_list) {
  return List::nok(this->get_max(), another_list.get_max());
}
