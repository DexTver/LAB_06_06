#include <stdio.h>
#include <string.h>

struct NOTE2 {
    char *Name;
    char *TELE;
    char *DATE;
};

typedef struct NOTE2 note;

int compare(const char *num1, const char *num2) {
    return (int) (num1[0] * 100 + num1[1] * 10 + num1[2]) >= (int) (num2[0] * 100 + num2[1] * 10 + num2[2]) ? 1 : 0;
}

void print_line(int x) {
    for (int i = 0; i < x; printf("-"), ++i);
    printf("+");
    for (int i = 0; i < 7; printf("-"), ++i);
    printf("+");
    for (int i = 0; i < 10; printf("-"), ++i);
    printf("\n");
}

void pprint(note *block) {
    int max_name = 0, x;
    for (int i = 0; i < 7; ++i) {
        x = strlen(block[i].Name);
        if (x > max_name) max_name = x;
    }

    print_line(max_name);

    for (int j = 0; j < 7; ++j) {
        printf("%s", block[j].Name);
        for (int i = 0; i < max_name - strlen(block[j].Name); printf(" "), ++i);
        printf("|%s|%s\n", block[j].TELE, block[j].DATE);
    }
}

int main() {
    char filename[128];
    FILE *f;
    char text[7][1024];
    int cnt;
    note user;
    note BLOCK2[7];
    char *token;
    char *str;

    printf("Please enter the file name:\n");
    scanf("%s", filename);
    f = fopen(filename, "r");
    while (f == NULL) {
        printf("Something went wrong! Perhaps such a file does not exist.\nPlease enter the file name again:\n");
        scanf("%s", filename);
        f = fopen(filename, "r");
    }

    for (int tt = 0; tt < 7; ++tt) {
        fgets(text[tt], sizeof(text[tt]), f);
        token = strtok(text[tt], ";");
        cnt = 0;
        while (token != NULL) {
            if (cnt == 0) user.Name = token;
            if (cnt == 1) user.TELE = token;
            if (cnt == 2) user.DATE = token;
            token = strtok(NULL, ";");
            ++cnt;
        }
        user.DATE[10] = '\0';
        BLOCK2[tt] = user;
    }

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (!compare(BLOCK2[i].TELE, BLOCK2[j].TELE)) {
                user = BLOCK2[i];
                BLOCK2[i] = BLOCK2[j];
                BLOCK2[j] = user;
            }
        }
    }

    getchar();
    do {
        fgets(str, 1024, stdin);
        str[strlen(str) - 1] = '\0';
        if (strcasecmp(str, "!print") == 0) {
            pprint(BLOCK2);
        } else if (strcasecmp(str, "!end") == 0) {
            printf("Goodbye!");
        } else {
            for (int i = 0; i < 8; ++i) {
                if (i == 7) printf("Not found!\n");
                if (strcasecmp(str, BLOCK2[i].Name) == 0) {
                    printf("%s\t%s\t%s\n", BLOCK2[i].Name, BLOCK2[i].TELE, BLOCK2[i].DATE);
                    i = 8;
                }
            }
        }
    } while (strcasecmp(str, "!end") != 0);
    return 0;
}