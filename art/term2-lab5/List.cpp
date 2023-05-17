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

    int nok(int a, int b) {
      return (a * b) / nod(a, b);
    }

  public:
    List(int len = 5) {
      this->len = len;
    }

    void setLength(int length) {
      this->len = length;
    }

    int* getList() {
      return list;
    }

    int getMax() {
      int max = list[0];
      for (int i = 0; i < this->len; i++) {
        if (max < list[i]) max = list[i];
      }
      return max;
    }

    int operator* (List& anotherList);
};

int List::operator* (List& anotherList) {
    return List::nok(this->getMax(), anotherList.getMax());
}