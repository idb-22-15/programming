#include <stdio.h>
#include <math.h>

// 11
class NaturalNumber {
private:
	int number = 1;

public:
	NaturalNumber() {
	}

	NaturalNumber(int n) {
		this->number = n;
		if (!this->isNatural()) {
			throw "Number is not natural";
		}
	}

	int value() {
		return this->number;
	}

	void setValue(int number) {
		if (!this->isNatural(number)) throw "Number is not natural";
		this->number = number;
	}

	bool isNatural() {
		if (this->number <= 0) return false;
		return true;
	}

	bool isNatural(int number) {
		if (number <= 0)  return false;
		return true;
	}

	bool isPrime() {
		if (this->number <= 1) return false;

		int count = 0;
		for (int i = 1; i <= sqrt(this->number) + 1; i++) {
			if (this->number % i == 0) {
				count++;
			}
			if (count > 2) return false;
		}
		return true;
	}

	void operator=(const NaturalNumber& another) {
		this->number = another.number;
	}
};

void variant11() {
	NaturalNumber array[100];

	for (int i = 1; i < 100; i++) {
		array[i] = NaturalNumber(i);
	}

	for (int i = 1; i < 100; i++) {
		if (array[i].isPrime()) printf("%d\n", array[i].value());
	}
}


//13
class PoliNumber {
private:
	int number;

public:
	PoliNumber(int number) {
		this->number = number;
	}

	int value() {
		return this->number;
	}

	bool isPalindrome() {
		if (this->number < 0) return false;

    int reversed = 0;
		int copyNumber = this->number;

    while (copyNumber != 0) {
        int remainder = copyNumber % 10;
        reversed = reversed * 10 + remainder;
        copyNumber /= 10;
    }

    if (this->number == reversed) return true;
		return false;
	}
};


void variant13() {
	PoliNumber number = PoliNumber(989);
	printf("%d", number.isPalindrome());
}


//17
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

	int* getArray() {
		return this->array;
	}
};

void variant17() {
	int baseArray[10] = { 3, 5, 6, 7, 3, 1, 4, 8, 5, 1 };
	ShiftingArray arr = ShiftingArray(baseArray);

	for (int i = 0; i < 10; i++) {
		printf("%d\t", arr.getArray()[i]);
	}

	printf("\n");
	arr.shiftRight(2);
	for (int i = 0; i < 10; i++) {
		printf("%d\t", arr.getArray()[i]);
	}
	printf("\n\n");

	int array2d[2][10] = { {3, 5, 6, 7, 3, 1, 4, 8, 5, 1}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 0} };

	for (int i = 0; i < 2; i++) {
		ShiftingArray::shiftRight(array2d[i], 2);
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%d\t", array2d[i][j]);
		}
		printf("\n");
	}
}


//20
class StrangeNumber {
private: 
	int number;

public:
	StrangeNumber(int number) {
		this->number = number;

	}

	int value() {
		return this->number;
	}

	bool isRepresentable() {
		for (int a = 0; a <= this->number; a++) {
			for (int b = 0; b <= this->number; b++) {
				int strangeSum = pow(a, 2) + pow(b, 2);
				if (this->number == strangeSum) return true;
				
			}
		}
		return false;
	}
};

void variant20() {
	StrangeNumber array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int count = 0;
	for (int i = 0; i < 10; i++) {
		if (array[i].isRepresentable()) {
			printf("%d\t", array[i].value());
			count++;
		}
	}
	printf("\nCount: %d", count);
}

//22
class MagicNumber {
private:
	int number;

public:
	MagicNumber(int number) {
		this->number = number;
	}

	int value() {
		return this->number;
	}

	bool isPrime(int number) {
		if (number <= 1) return false;

		int count = 0;
		for (int i = 1; i <= sqrt(number) + 1; i++) {
			if (number % i == 0) {
				count++;
			}
			if (count > 2) return false;
		}
		return true;
	}

	bool isRepresentable() {
		int accumulator = this->number;
		
		for (int n = this->number; n > 0; n--) {
			if (!this->isPrime(n) || accumulator - n < 0) continue;
			accumulator -= n;
		}

		if (accumulator == 0) return true;
		return false;
	}
};

void variant22() {
	MagicNumber array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	int count = 0;
	for (int i = 0; i < 10; i++) {
		if (array[i].isRepresentable()) {
			printf("%d\t", array[i].value());
			count++;
		}
	} 

	printf("\nCount: %d", count);
}

int main() {
	// variant11();
	// variant13();
	// variant17();
	// variant20();
	// variant22();
}

