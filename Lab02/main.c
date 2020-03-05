#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void ex_1();
void ex_2();
void ex_3();
void tinyGrep();

int main()
{
    tinyGrep();
}

void ex_1() {
    int a[4] = {-1,2,10,7};
    int b[4];
    for(int i = 0; i < 4; i++){
        b[i] = a[3-i];
    }

    printf("%d \n", a[3]);
    printf("%d \n", b[3]);
    printf("%d \n", b[a[1]]);
}

void ex_2() {
    char *a = "abcdef";
    char b[7];
    strcpy(b, a);
    for (int i = 0; i < 3; i++)
        b[i] = b[i] + 1;
    printf("%s \n", b);
    b[3] = '\0';
    printf("%s \n", b);
    printf("a[0]: %c \n", a[0]);
    printf("b[0]: %c \n", b[0]);
    printf("b[4]: %c \n", b[4]);
    printf("Length of string a: %d \n", strlen(a));
    printf("Length of string b: %d \n", strlen(b));
    printf("String compare a and b: %d \n", strcmp(a, b));
}

void ex_3(){
    char inputStr[255];
    printf("Enter a sentence, up to 255 characters:\n");
    fgets(inputStr, 255, stdin);

    int lastStrPos = 0;

    for (int i = 0; i < strlen(inputStr); i++) {
        if (isspace(inputStr[i]) || inputStr[i] == ',') {
            for (int z = lastStrPos; z < i; z++) {
                printf("%c", inputStr[z]);
            }
            printf("\t%d", i-lastStrPos);
            lastStrPos = i+1;
            if (i != (strlen(inputStr) -1)) {
                printf("\n");
            }
        }
    }
}

void tinyGrep() {
    char inputStr[255];
    printf("Enter a sentence, up to 255 characters:\n");
    fgets(inputStr, 255, stdin);

    char searchStr[255];
    printf("Enter a search, up to 255 characters:\n");
    fgets(searchStr, 255, stdin);

    printf("Case Sensitive:\n");
    char caseOp;
    scanf("%c", &caseOp);

    strtok(inputStr, "\n");
    strtok(searchStr, "\n");

    if (caseOp == 'N') {
        for (int k = 0; k < strlen(inputStr); k++) {
            inputStr[k] = tolower(inputStr[k]);
        }
        for (int g = 0; g < strlen(searchStr); g++){
            searchStr[g] = tolower(searchStr[g]);
        }
    }

    bool isDot = true;
    bool isMatch = false;
    bool spaceMatch = false;

    int y = 0;
    int i;
    int z = 0;

    for (i = 0; i < strlen(inputStr); i++) {
        for (int x = y; x < strlen(searchStr); x++) {
            if (searchStr[x] == '_') {
                char whiteSpaces[6] = {'\n',' ','\f','\r','\t','\v'};
                for (int r = 0; r < 6; r++) {
                    searchStr[x] = whiteSpaces[r];
                    char *pos = strstr(inputStr, searchStr);
                    if (pos) {
                        isDot = false;
                        spaceMatch = true;
                        isMatch = true;
                        z = pos - inputStr;
                        goto check;
                    }
                }
            }
            if (searchStr[x] != '.') {
                isDot = false;
                if (inputStr[i] != searchStr[x]){
                    isMatch = false;
                    continue;
                } else if (inputStr[i] == searchStr[x]) {
                    isMatch = true;
                    y++;
                    break;
                }
            }
        }
        check:
        if (y == (strlen(searchStr) - 1)){
            if (i != 0) {
                i = i - 1;
            }
            z = i;
            break;
        }
        if (spaceMatch) {
            break;
        }
    }
    if (isDot == true) {
        printf("Matched at position 0");
    } else if (isDot == false) {
        if (isMatch == true) {
            printf("Matched at position %d", z);
        } else if (isMatch == false) {
            printf("No Match");
        }
    }
