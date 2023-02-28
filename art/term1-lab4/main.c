#include <stdio.h>
#include <locale.h>

void red44();

int main()
{
	setlocale(LC_ALL, "");

	red44();
}


void f1() {
	for (int i = 0; i < 256; i++) {
		printf("%d -> %c\n", i, i);
	}
}

void f2() {
	int c;

	while ((c = getchar()) != EOF) {
		putchar(c);
	}
}

void green10() {
	char c;
	char first = NULL;
	int isFirst = 1;
	char last = NULL;
	int result = 1;

	while ((c = getchar()) != EOF) {
		if (isFirst) {
			first = c;
		}
		isFirst = 0;
		if (c != 10 && c != 26) {
			last = c;
		}
		//printf("%d", c);
	}

	if (first == '(' && last == ')') {
		printf("Строка сответствует");
	}
	else {
		printf("Строка не сответствует");
	}


}

void red44() {
	int is_prev_onen_cav = 0;
	int is_prev_close_cav = 0;
	char c;
	char prev = NULL;
	int open_cav = 0;
	int close_cav = 0;

	int isFirst1 = 1;
	int isFirst2 = 0;

	char first1 = NULL;
	char first2 = NULL;
	char last1 = NULL;
	char last2 = NULL;

	int is_brackets = 0;

	int result = 1;


	while ((c = getchar()) != EOF) {

		if (is_prev_onen_cav == 1)  is_prev_onen_cav = 0;
		if (is_prev_close_cav == 1) is_prev_close_cav = 0;

		if (isFirst1) {
			first1 = c;
			isFirst1 = 0;
			isFirst2 = 1;
		}

		if (isFirst2) {
			first2 = c;
			isFirst2 = 0;
		}

		if (c == '(' && is_brackets == 0) is_brackets++;
		if (c == ')' && is_brackets != 0) is_brackets--;

		if (is_brackets == 0) {
			if (prev == '<' && c == '<' && is_prev_onen_cav != 1) {
				open_cav++;
				is_prev_onen_cav = 1;
			};
			if (prev == '>' && c == '>' && is_prev_close_cav != 1) {
				close_cav++;
				is_prev_close_cav = 1;
			};
		}

		if (c != 10 && c != 26) {
			last1 = prev;
			last2 = c;
		}

		prev = c;

	}

	if (first1 == '<' && first2 == '<' && last1 == '>' && last2 == '>' && open_cav == close_cav) {
		printf("Текст сответствует");
	}
	else {
		printf("Текст не сответствует");
	}
}
