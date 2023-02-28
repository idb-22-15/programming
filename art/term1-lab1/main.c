#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void n1()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);


    if (a > 7) {
        if (a < 27) {
            if (b > 7) {
                if (b < 27)
                {

                    if (a < b) {
                        if (a < c) a += 2;
                        else c += 2;
                    }
                    else if (b < c) b += 2;
                    else c += 2;


                    printf("%d %d %d", a, b, c);
                }
            }
        }
    }
    else if (a > 7) {
        if (a < 27) {
            if (c > 7) {
                if (c < 27)
                {
                    if (a < b) {
                        if (a < c) a += 2;
                        else c += 2;
                    }
                    else if (b < c) b += 2;
                    else c += 2;

                    printf("%d %d %d", a, b, c);
                }
            }
        }
    }
    else if (b > 7) {
        if (b < 27) {
            if (c > 7) {
                if (c < 27)
                {
                    if (a < b) {
                        if (a < c) a += 2;
                        else c += 2;
                    }
                    else if (b < c) b += 2;
                    else c += 2;

                    printf("%d %d %d", a, b, c);
                }
            }
        }
    }
    else {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        if (c < 0) c = -c;
        printf("%d %d %d", a, b, c);
    }
}

int main()
{
    n1();
    getch();
}
