#pragma once
#include <math.h>

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