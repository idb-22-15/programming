#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define nullptr NULL;

void f1() {
  FILE* stream = nullptr;
  if ((stream = fopen("1.txt", "w")) != 0) {
    for (int n = 1; n <= 100; n++)
      fprintf(stream, "%d - %d\n", n, n * n);
    fclose(stream);
  } else {
    printf("Error");
  }
}

void f2() {
  FILE* instream = nullptr;
  FILE* outstream = nullptr;

  char c, in_filename[20], out_filename[20];

  printf("Print in filename\n");
  scanf("%s", in_filename);

  printf("Print out filename\n");
  scanf("%s", out_filename);

  instream = fopen(in_filename, "r");
  if (instream == 0) {
    printf("No in file with name %s", in_filename);
    return;
  }

  outstream = fopen(out_filename, "w");
  if (out_filename == 0) {
    printf("No out file with name %s", out_filename);
    return;
  }

  while ((c = fgetc(instream)) != EOF) {
    fputc(c, outstream);
  }
  fclose(instream);
  fclose(outstream);
}

void f11() {
  FILE* instream = nullptr;
  FILE* outstream = nullptr;

  char in_filename[20], out_filename[20];

  printf("Print in filename\n");
  scanf("%s", in_filename);

  printf("Print out filename\n");
  scanf("%s", out_filename);

  instream = fopen(in_filename, "r");
  if (instream == 0) {
    printf("No in file with name %s", in_filename);
    return;
  }
  outstream = fopen(out_filename, "w");
  if (out_filename == 0) {
    printf("No out file with name %s", out_filename);
    return;
  }

  char c;
  int length = 0;
  int count = 0;
  int subcount = 0;
  while ((c = fgetc(instream)) != EOF) {
    count++;
    length++;

    if (c == '\n') {
      printf("Length: %d\n", length);

      if (length >= 9 + 2) {
        length = 0;
        subcount = 0;
        continue;
      };

      fclose(instream);
      instream = fopen(in_filename, "r");

      while ((c = fgetc(instream)) != EOF) {
        subcount++;

        if (subcount > count - length && subcount <= count) {
          // fputc(c, outstream);
          fprintf(outstream, "%c", c);
        }
        if (subcount == count)
          break;
      }

      length = 0;
      subcount = 0;
    }
  }

  fclose(instream);
  fclose(outstream);
}

int main() {
  f11();
}
