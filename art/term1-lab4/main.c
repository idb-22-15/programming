#include <locale.h>
#include <stdio.h>

void red44();

int main() {
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
  char first = 0;
  int isFirst = 1;
  char last = 0;
  int result = 1;

  while ((c = getchar()) != EOF) {
    if (isFirst) {
      first = c;
    }
    isFirst = 0;
    if (c != 10 && c != 26) {
      last = c;
    }
    // printf("%d", c);
  }

  if (first == '(' && last == ')') {
    printf("Строка сответствует");
  } else {
    printf("Строка не сответствует");
  }
}

void red44() {
  int is_prev_onen_cav = 0;
  int is_prev_close_cav = 0;
  char c;
  char prev = 0;
  int open_cav = 0;
  int close_cav = 0;

  int is_first1 = 1;
  int is_first2 = 0;

  char first1 = 0;
  char first2 = 0;
  char last1 = 0;
  char last2 = 0;

  int is_brackets = 0;

  int result = 1;

  while ((c = getchar()) != EOF) {
    if (is_prev_onen_cav == 1)
      is_prev_onen_cav = 0;
    if (is_prev_close_cav == 1)
      is_prev_close_cav = 0;

    if (is_first1) {
      first1 = c;
      is_first1 = 0;
      is_first2 = 1;
    }

    if (is_first2) {
      first2 = c;
      is_first2 = 0;
    }

    if (c == '(' && is_brackets == 0)
      is_brackets++;
    if (c == ')' && is_brackets != 0)
      is_brackets--;

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

  if (first1 == '<' && first2 == '<' && last1 == '>' && last2 == '>' &&
      open_cav == close_cav) {
    printf("Текст сответствует");
  } else {
    printf("Текст не сответствует");
  }
}
