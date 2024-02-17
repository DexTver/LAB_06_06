#include <stdio.h>

struct NOTE2 {
    char *Name;
    char *TELE;
    char *DATE;
};

typedef struct NOTE2 note;

int compare(const char *num1, const char *num2) {
    return (int) (num1[0] + num1[1] + num1[2]) >= (int) (num2[0] + num2[1] + num2[2]) ? 1 : 0;
}

int main() {
//    printf("%i", compare("232242", "232222"));
    printf("%s", "Please enter file name:");
    // попытка открыть файл
    // файл открылся? - считываем все строчки и разбиваем их через ;
    // забиваем массив
    // создать команду "!print"
    // считывать фамилии
    return 0;
}
