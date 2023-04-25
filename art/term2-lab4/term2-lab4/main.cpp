#include <stdio.h>
#include "NaturalNumber.cpp"
#include "PoliNumber.cpp"
#include "ShiftingArray.cpp"
#include "StrangeNumber.cpp"
#include "MagicNumber.cpp"


void variant11() {
	NaturalNumber array[100];

	for (int i = 1; i < 100; i++) {
		array[i] = NaturalNumber(i);
	}

	for (int i = 1; i < 100; i++) {
		if (array[i].isPrime()) printf("%d\n", array[i].value());
	}
}

void variant13() {
	PoliNumber number = PoliNumber(989);
	printf("%d", number.isPalindrome());
}

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

