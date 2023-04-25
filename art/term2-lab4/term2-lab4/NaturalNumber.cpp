#pragma once
#include <math.h>

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