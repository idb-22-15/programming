/*12. Дана строка символов. Группы символов, разделенные пробелами (одним или
несколькими) и не содержащие пробелов внутри себя, будем называть словами.
Преобразовать строку, удвоив в ней самое короткое слово.*/

#include <stdio.h>


int main() {
    /*char c[82] = { 0 }; int len = 0; int i = 0; int l = 0;
    int word_len = 82; int temp_word_len = 0; char temp = 0; int end = 0;
    while ((l = getchar()) != '\n') {
        c[i] = l;
        if (c[i] != ' ') {
            temp_word_len++;
        }
        else {
            end = i;
            word_len = word_len >= temp_word_len ? temp_word_len : word_len;
            temp_word_len = 0;

        }
        len = i + 1;
        i++;
    }*/
    char a[11] = {'1','2','3','4','5', ' ', ' ', ' ', ' ', ' ', ' '};
    char temp;
    for (int i = 4; i > 5; i--) {
        a[i] = a[i - 5];
    }
    printf("%s", a);

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
